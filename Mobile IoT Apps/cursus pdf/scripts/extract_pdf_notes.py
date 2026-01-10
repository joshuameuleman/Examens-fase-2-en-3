from __future__ import annotations

import json
import re
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable

from pypdf import PdfReader


BULLET_PREFIXES = ("•", "-", "–", "—", "*", "·")


def _normalize_line(line: str) -> str:
    line = line.replace("\u00a0", " ")
    line = re.sub(r"\s+", " ", line).strip()
    return line


def _iter_lines(text: str) -> Iterable[str]:
    for raw in text.splitlines():
        line = _normalize_line(raw)
        if line:
            yield line


def _looks_like_heading(line: str) -> bool:
    if len(line) < 3:
        return False
    if len(line) > 90:
        return False
    if any(line.startswith(p) for p in BULLET_PREFIXES):
        return False
    # Avoid URLs
    if "http://" in line.lower() or "https://" in line.lower():
        return False
    # Heuristic: short-ish, not ending with punctuation typical for sentences
    if line.endswith((".", ";", ",", ":")):
        return False
    words = line.split(" ")
    if len(words) > 12:
        return False
    # Headings often have Title Case or ALL CAPS
    alpha = re.sub(r"[^A-Za-z]", "", line)
    if not alpha:
        return False
    if line.isupper():
        return True
    # Title-ish: at least 2 words and many capitalized words
    caps = sum(1 for w in words if w and w[0].isupper())
    return len(words) >= 2 and caps >= max(2, len(words) // 2)


@dataclass
class PageNotes:
    page_index: int
    title: str | None
    bullets: list[str]
    other: list[str]


def extract_notes_from_pdf(pdf_path: Path) -> tuple[dict, list[PageNotes]]:
    reader = PdfReader(str(pdf_path))
    page_count = len(reader.pages)

    outline = []
    try:
        raw_outline = getattr(reader, "outline", None)
        if raw_outline:
            # Outline is nested; we best-effort stringify titles.
            def flatten(items):
                for it in items:
                    if isinstance(it, list):
                        yield from flatten(it)
                    else:
                        title = getattr(it, "title", None)
                        if title:
                            yield str(title)

            outline = list(dict.fromkeys(flatten(raw_outline)))
    except Exception:
        outline = []

    pages: list[PageNotes] = []
    total_chars = 0

    for i, page in enumerate(reader.pages):
        try:
            text = page.extract_text() or ""
        except Exception:
            text = ""
        total_chars += len(text)

        lines = list(_iter_lines(text))
        title = None
        bullets: list[str] = []
        other: list[str] = []

        # pick first heading-like line as title; fallback to first non-bullet short line
        for line in lines[:30]:
            if _looks_like_heading(line):
                title = line
                break
        if title is None:
            for line in lines[:30]:
                if not any(line.startswith(p) for p in BULLET_PREFIXES) and len(line) <= 80:
                    title = line
                    break

        for line in lines:
            if any(line.startswith(p) for p in BULLET_PREFIXES):
                bullet = _normalize_line(line.lstrip("".join(BULLET_PREFIXES)).lstrip())
                if bullet:
                    bullets.append(bullet)
            else:
                # Keep short, non-noisy lines as “other” (e.g., code identifiers)
                if 3 <= len(line) <= 120:
                    other.append(line)

        # de-dup while preserving order
        def dedup(seq: list[str]) -> list[str]:
            seen = set()
            out = []
            for s in seq:
                if s not in seen:
                    seen.add(s)
                    out.append(s)
            return out

        pages.append(PageNotes(i, title, dedup(bullets), dedup(other)))

    meta = {
        "file": pdf_path.name,
        "page_count": page_count,
        "outline_titles": outline,
        "approx_total_chars": total_chars,
    }
    return meta, pages


def write_notes_markdown(out_path: Path, meta: dict, pages: list[PageNotes]) -> None:
    lines: list[str] = []
    lines.append(f"# Notes extract: {meta['file']}")
    lines.append("")
    lines.append(f"- Pages: {meta['page_count']}")
    lines.append(f"- Approx characters extracted: {meta['approx_total_chars']}")
    if meta.get("outline_titles"):
        lines.append(f"- Outline items: {len(meta['outline_titles'])}")
    lines.append("")

    if meta.get("outline_titles"):
        lines.append("## Outline (best effort)")
        for t in meta["outline_titles"][:80]:
            lines.append(f"- {t}")
        if len(meta["outline_titles"]) > 80:
            lines.append(f"- … ({len(meta['outline_titles']) - 80} more)")
        lines.append("")

    lines.append("## Per page")
    lines.append("")

    for p in pages:
        title = p.title or "(no title detected)"
        lines.append(f"### Page {p.page_index + 1}: {title}")
        if p.bullets:
            for b in p.bullets[:25]:
                lines.append(f"- {b}")
            if len(p.bullets) > 25:
                lines.append(f"- … ({len(p.bullets) - 25} more bullets)")
        else:
            # If no bullets, keep a small sample of other lines.
            sample = p.other[:12]
            for s in sample:
                lines.append(f"- {s}")
        lines.append("")

    out_path.write_text("\n".join(lines), encoding="utf-8")


def main() -> None:
    base_dir = Path(__file__).resolve().parents[1]
    pdf_dir = base_dir
    out_dir = base_dir / "_extracted"
    out_dir.mkdir(parents=True, exist_ok=True)

    pdfs = sorted(pdf_dir.glob("*.pdf"))
    if not pdfs:
        raise SystemExit(f"No PDFs found in: {pdf_dir}")

    index = []
    for pdf in pdfs:
        meta, pages = extract_notes_from_pdf(pdf)
        index.append(meta)
        (out_dir / f"{pdf.stem}.meta.json").write_text(json.dumps(meta, indent=2, ensure_ascii=False), encoding="utf-8")
        write_notes_markdown(out_dir / f"{pdf.stem}.notes.md", meta, pages)
        print(f"OK: {pdf.name} ({meta['page_count']} pages)")

    (out_dir / "index.json").write_text(json.dumps(index, indent=2, ensure_ascii=False), encoding="utf-8")
    print(f"\nWrote extracts to: {out_dir}")


if __name__ == "__main__":
    main()
