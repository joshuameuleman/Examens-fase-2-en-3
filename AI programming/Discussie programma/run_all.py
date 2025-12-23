"""Run alle demo scripts achter elkaar en print duidelijke headers.

Gebruik: python run_all.py
"""
from __future__ import annotations
import subprocess
import sys
from pathlib import Path


SCRIPTS = [
    "array_program.py",
    "linked_list_program.py",
    "queue_program.py",
    "stack_program.py",
]


def run_script(script: str) -> int:
    print("=" * 60)
    print(f"Running: {script}")
    print("=" * 60)
    # use same python executable
    result = subprocess.run([sys.executable, script], check=False)
    print(f"Exit code: {result.returncode}\n")
    return result.returncode


def main() -> int:
    cwd = Path(__file__).parent
    codes = []
    for s in SCRIPTS:
        path = cwd / s
        if not path.exists():
            print(f"Script not found: {s}")
            codes.append(1)
            continue
        codes.append(run_script(str(path)))
    # non-zero if any script failed
    return 0 if all(c == 0 for c in codes) else 1


if __name__ == "__main__":
    raise SystemExit(main())
