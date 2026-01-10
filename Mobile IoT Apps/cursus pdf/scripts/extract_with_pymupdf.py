from __future__ import annotations

import re
from pathlib import Path

import fitz  # pymupdf


def normalize(text: str) -> str:
    # Some PDFs (especially those with embedded fonts/ligatures) can yield
    # NUL/control characters; strip them so the output is plain-text friendly.
    text = text.replace("\x00", "")
    text = text.replace("\u00a0", " ")
    text = re.sub(r"[\x01-\x08\x0b\x0c\x0e-\x1f]", "", text)
    text = re.sub(r"[ \t]+", " ", text)
    text = re.sub(r"\n{3,}", "\n\n", text)
    return text.strip()


def main() -> None:
    base_dir = Path(__file__).resolve().parents[1]
    pdf_path = base_dir / "Modern Frontend Build Pipeline.pdf"
    if not pdf_path.exists():
        raise SystemExit(f"Not found: {pdf_path}")

    out_dir = base_dir / "_extracted"
    out_dir.mkdir(parents=True, exist_ok=True)
    out_txt = out_dir / "Modern Frontend Build Pipeline.pymupdf.txt"

    doc = fitz.open(str(pdf_path))
    parts: list[str] = []
    parts.append(f"# Extract (PyMuPDF): {pdf_path.name}")
    parts.append(f"# Pages: {doc.page_count}")
    parts.append("")

    for i in range(doc.page_count):
        page = doc.load_page(i)
        text = page.get_text("text")
        text = normalize(text)
        parts.append(f"\n\n===== PAGE {i+1} =====\n")
        parts.append(text)

    out_txt.write_text("\n".join(parts), encoding="utf-8")
    print(f"Wrote: {out_txt}")


if __name__ == "__main__":
    main()
