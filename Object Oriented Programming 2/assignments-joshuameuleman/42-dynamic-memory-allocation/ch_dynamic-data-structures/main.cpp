#include "LinkedList.h"

int main() {
    LinkedList list;

    // initial nodes
    list.append('A');
    list.append('B');
    list.append('C');

    list.print();

    // Add more nodes, including duplicates
    list.append('D');
    list.append('E');
    list.append('F');
    list.append('B'); // duplicate

    list.print();

    // Remove all 'B' nodes
    list.remove('B');
    list.print();

    // Insert nodes at various positions
    list.insert('X', 0); // at head
    list.insert('Y', 2); // somewhere in middle
    list.insert('Z', 100); // index past end -> append
    list.print();

    // destructor will clean up remaining nodes automatically

    return 0;
}
