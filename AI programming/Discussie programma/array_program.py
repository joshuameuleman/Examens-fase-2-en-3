"""
Array demo (NumPy-only)

Dit script gebruikt NumPy om een array met gehele getallen te genereren en te tonen.
Je kunt het aantal elementen opgeven met `--count` of interactief invoeren.

Voorbeeld:
    python .\array_program.py --count 5

Benodigd: NumPy (`pip install numpy`).
"""
from __future__ import annotations
import argparse
import sys
from typing import Optional

try:
    import numpy as np
except Exception as e:  # pragma: no cover - runtime dependency
    print("Fout: NumPy is vereist voor dit script. Installeer met: python -m pip install numpy")
    raise


def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description="Array demo: bouw en print een NumPy array met integers")
    p.add_argument("--count", type=int, help="precieze aantal elementen om te maken")
    p.add_argument("--min", type=int, default=5, help="min aantal (als --count niet gebruikt)")
    p.add_argument("--max", type=int, default=12, help="max aantal (als --count niet gebruikt)")
    p.add_argument("--seed", type=int, help="optionele random seed voor reproduceerbaarheid")
    return p.parse_args()


def main() -> int:
    args = parse_args()

    # Interactieve prompt als --count niet is opgegeven
    if args.count is None:
        try:
            s = input("Aantal elementen (druk Enter voor willekeurig): ").strip()
            args.count = int(s) if s != "" else None
        except ValueError:
            print("Ongeldige invoer, gebruik willekeurig aantal.")
            args.count = None

    if args.seed is not None:
        np.random.seed(args.seed)

    n = args.count if args.count is not None else int(np.random.randint(args.min, args.max + 1))

    # Maak NumPy array direct
    arr = np.random.randint(0, 100, size=n)

    # Print overzicht
    print(f"Aantal elementen: {arr.size}")
    print(f"Dtype: {arr.dtype}")
    print("Array (NumPy):")
    # Print compacte representatie; voor langere arrays kun je np.set_printoptions wijzigen
    print(arr)

    # Voorbeeld: toon elk element met index (optioneel)
    for i, v in enumerate(arr):
        print(f"arr[{i}] = {int(v)}")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
