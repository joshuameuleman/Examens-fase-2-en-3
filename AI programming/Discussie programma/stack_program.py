"""
Stack demo (NumPy-generated values)

Gebruikt NumPy om de waarden te genereren en behandelt een stack via Python list operaties.
"""
from __future__ import annotations
import argparse
from typing import List, Optional

try:
    import numpy as np
except Exception:  # pragma: no cover - runtime dependency
    print("Fout: NumPy is vereist. Installeer met: python -m pip install numpy")
    raise


def build_random_stack(min_items: int = 5, max_items: int = 12, count: Optional[int] = None) -> List[int]:
    stack: List[int] = []
    n = int(count) if count is not None else int(np.random.randint(min_items, max_items + 1))
    values = np.random.randint(0, 100, size=n)
    for v in values:
        stack.append(int(v))
    return stack


def drain_stack(stack: List[int]) -> List[int]:
    result: List[int] = []
    while stack:
        result.append(stack.pop())
    return result


def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description="Stack demo: bouw en drain een stack met integers (NumPy-generated)")
    p.add_argument("--count", type=int, help="precieze aantal elementen om te maken")
    p.add_argument("--min", type=int, default=5, help="min aantal (als --count niet gebruikt)")
    p.add_argument("--max", type=int, default=12, help="max aantal (als --count niet gebruikt)")
    p.add_argument("--seed", type=int, help="optionele random seed voor reproduceerbaarheid")
    return p.parse_args()


if __name__ == "__main__":
    args = parse_args()
    if args.seed is not None:
        np.random.seed(args.seed)

    if args.count is None:
        try:
            s = input("Aantal elementen (druk Enter voor willekeurig): ").strip()
            args.count = int(s) if s != "" else None
        except ValueError:
            print("Ongeldige invoer, gebruik willekeurig aantal.")
            args.count = None

    stack = build_random_stack(min_items=args.min, max_items=args.max, count=args.count)
    print(f"Aantal elementen in stack (voor): {len(stack)}")

    items = drain_stack(stack)

    print("Elementen uit de stack (LIFO):")
    for i, value in enumerate(items):
        print(f"{i+1}. {value}")

    print(f"Aantal elementen in stack (na): {len(stack)}")
