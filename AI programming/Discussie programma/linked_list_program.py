"""
Linked List demo (NumPy-generated values)

Dit script bouwt een eenvoudige singly-linked list, maar gebruikt NumPy
om de waarden te genereren. Je kunt `--count` opgeven of interactief invoeren.
"""
from __future__ import annotations
import argparse
from dataclasses import dataclass
from typing import Optional, Iterator

try:
    import numpy as np
except Exception:  # pragma: no cover - runtime dependency
    print("Fout: NumPy is vereist. Installeer met: python -m pip install numpy")
    raise


@dataclass
class Node:
    value: int
    next: Optional["Node"] = None


class LinkedList:
    def __init__(self) -> None:
        self.head: Optional[Node] = None
        self.tail: Optional[Node] = None
        self._size: int = 0

    def append(self, value: int) -> None:
        new_node = Node(int(value))
        if self.tail is None:
            self.head = self.tail = new_node
        else:
            assert self.tail is not None
            self.tail.next = new_node
            self.tail = new_node
        self._size += 1

    def __iter__(self) -> Iterator[int]:
        current = self.head
        while current is not None:
            yield current.value
            current = current.next

    def __len__(self) -> int:
        return self._size


def build_random_linked_list(min_items: int = 5, max_items: int = 12, count: Optional[int] = None) -> LinkedList:
    ll = LinkedList()
    n = int(count) if count is not None else int(np.random.randint(min_items, max_items + 1))
    values = np.random.randint(0, 100, size=n)
    for v in values:
        ll.append(int(v))
    return ll


def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description="Linked list demo: bouw en print linked list met integers (NumPy-generated)")
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

    linked = build_random_linked_list(min_items=args.min, max_items=args.max, count=args.count)
    print(f"Aantal elementen in linked list: {len(linked)}")
    print("Elementen in volgorde:")
    for i, value in enumerate(linked):
        print(f"{i+1}. {value}")
