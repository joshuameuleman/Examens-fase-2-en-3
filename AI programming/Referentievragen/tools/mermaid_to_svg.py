import re
import subprocess
from dataclasses import dataclass
from pathlib import Path
import shutil


@dataclass
class MermaidBlock:
    start: int
    end: int
    code: str


MERMAID_FENCE_RE = re.compile(
    r"^[ \t]*```mermaid\s*\r?\n(?P<code>.*?)\r?\n^[ \t]*```\s*$",
    re.DOTALL | re.IGNORECASE | re.MULTILINE,
)


def find_mermaid_blocks(text: str) -> list[MermaidBlock]:
    blocks: list[MermaidBlock] = []
    for match in MERMAID_FENCE_RE.finditer(text):
        blocks.append(
            MermaidBlock(
                start=match.start(),
                end=match.end(),
                code=match.group("code").strip("\r\n"),
            )
        )
    return blocks


def ensure_dir(path: Path) -> None:
    path.mkdir(parents=True, exist_ok=True)


def run_mmdc(input_file: Path, output_file: Path) -> None:
    # Uses npx so the user doesn't need global installs.
    # Mermaid CLI uses Puppeteer; first run can take a bit.
    npx = shutil.which("npx") or shutil.which("npx.cmd")
    if not npx:
        raise SystemExit("Could not find 'npx' on PATH. Ensure Node.js is installed and restart VS Code.")
    cmd = [
        npx,
        "-y",
        "@mermaid-js/mermaid-cli",
        "-i",
        str(input_file),
        "-o",
        str(output_file),
        "--backgroundColor",
        "transparent",
    ]
    subprocess.run(cmd, check=True)


def main() -> None:
    workspace_dir = Path(__file__).resolve().parents[1]
    md_path = workspace_dir / "Referentievragen.md"

    if not md_path.exists():
        raise SystemExit(f"Markdown file not found: {md_path}")

    text = md_path.read_text(encoding="utf-8")
    blocks = find_mermaid_blocks(text)

    if not blocks:
        print("No Mermaid blocks found; nothing to do.")
        return

    src_dir = workspace_dir / "assets" / "mermaid-src"
    out_dir = workspace_dir / "assets" / "diagrams"
    ensure_dir(src_dir)
    ensure_dir(out_dir)

    # Replace from the end to keep indices stable.
    new_text = text

    for i, block in enumerate(reversed(blocks), start=1):
        diagram_index = len(blocks) - i + 1
        base_name = f"diagram-{diagram_index:02d}"

        src_file = src_dir / f"{base_name}.mmd"
        out_file = out_dir / f"{base_name}.svg"

        src_file.write_text(block.code + "\n", encoding="utf-8")

        try:
            run_mmdc(src_file, out_file)
        except subprocess.CalledProcessError as exc:
            raise SystemExit(
                "Failed to render Mermaid to SVG. "
                "If this is the first run, you may need to allow Puppeteer to download Chromium.\n"
                f"Command failed: {exc}"
            )

        replacement = f"![{base_name}](assets/diagrams/{base_name}.svg)"
        new_text = new_text[: block.start] + replacement + new_text[block.end :]

    md_path.write_text(new_text, encoding="utf-8")
    print(f"Rendered {len(blocks)} Mermaid diagrams to SVG and updated {md_path.name}.")


if __name__ == "__main__":
    main()
