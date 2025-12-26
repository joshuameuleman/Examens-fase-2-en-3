#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

class LinkedList {
private:
    struct Node {
        char data;
        Node* next;
        Node(char c) : data(c), next(nullptr) {}
    };

    Node* head;

public:
    LinkedList();
    ~LinkedList();

    void append(char value);
    void insert(char value, int index);
    void remove(char value);
    void print() const;
    void clear();

    // Disable copy to avoid accidental shallow copies
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    // Allow move semantics
    LinkedList(LinkedList&& other) noexcept;
    LinkedList& operator=(LinkedList&& other) noexcept;
};

#endif // LINKEDLIST_H
