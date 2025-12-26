#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::clear() {
    Node* temp = head;
    while (temp != nullptr) {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }
    head = nullptr;
}

void LinkedList::append(char value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) temp = temp->next;
    temp->next = newNode;
}

void LinkedList::print() const {
    cout << "headPtr --> ";
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " --> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

void LinkedList::remove(char value) {
    // Remove all matching head nodes
    while (head != nullptr && head->data == value) {
        Node* toDelete = head;
        head = head->next;
        cout << "Removing: " << toDelete->data << endl;
        delete toDelete;
    }

    if (head == nullptr) return;

    Node* prev = head;
    Node* curr = head->next;
    while (curr != nullptr) {
        if (curr->data == value) {
            prev->next = curr->next;
            cout << "Removing: " << curr->data << endl;
            delete curr;
            curr = prev->next;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}

void LinkedList::insert(char value, int index) {
    Node* newNode = new Node(value);
    if (index <= 0 || head == nullptr) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* prev = head;
    int i = 0;
    while (i < index - 1 && prev->next != nullptr) {
        prev = prev->next;
        ++i;
    }

    newNode->next = prev->next;
    prev->next = newNode;
}

// Move semantics
LinkedList::LinkedList(LinkedList&& other) noexcept : head(other.head) {
    other.head = nullptr;
}

LinkedList& LinkedList::operator=(LinkedList&& other) noexcept {
    if (this != &other) {
        clear();
        head = other.head;
        other.head = nullptr;
    }
    return *this;
}
