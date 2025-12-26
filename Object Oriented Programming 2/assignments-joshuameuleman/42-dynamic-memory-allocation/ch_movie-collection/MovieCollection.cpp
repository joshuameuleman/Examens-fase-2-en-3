#include "MovieCollection.h"
#include <iostream>

MovieCollection::MovieCollection(const std::string& name_)
    : name(name_), head(nullptr), current(nullptr) {}

MovieCollection::~MovieCollection() {
    clearMovies();
}

void MovieCollection::addMovie(const std::string& director, const std::string& title, const std::string& genre, int duration) {
    Movie* node = new Movie(director, title, genre, duration);
    if (!head) {
        head = node;
        return;
    }
    Movie* p = head;
    while (p->next) p = p->next;
    p->next = node;
}

bool MovieCollection::removeMovie(const std::string& director, const std::string& title) {
    if (!head) return false;
    Movie* p = head;
    Movie* prev = nullptr;
    while (p) {
        if (p->director == director && p->title == title) {
            if (prev) prev->next = p->next;
            else head = p->next;
            if (current == p) current = p->next;
            delete p;
            return true;
        }
        prev = p;
        p = p->next;
    }
    return false;
}

void MovieCollection::showFirstMovie() {
    if (!head) {
        std::cout << "Collection is empty.\n";
        current = nullptr;
        return;
    }
    current = head;
    current->print();
}

void MovieCollection::showNextMovie() {
    if (!current) {
        std::cout << "No current movie. Call showFirstMovie() first.\n";
        return;
    }
    if (!current->next) {
        std::cout << "Already at the last movie.\n";
        return;
    }
    current = current->next;
    current->print();
}

void MovieCollection::showMovies() const {
    if (!head) {
        std::cout << "Collection is empty.\n";
        return;
    }
    Movie* p = head;
    int idx = 1;
    while (p) {
        std::cout << "[" << idx++ << "]\n";
        p->print();
        std::cout << "---\n";
        p = p->next;
    }
}

void MovieCollection::clearMovies() {
    Movie* p = head;
    while (p) {
        Movie* next = p->next;
        delete p;
        p = next;
    }
    head = nullptr;
    current = nullptr;
}
