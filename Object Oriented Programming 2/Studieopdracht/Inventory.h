#pragma once

#include "Item.h"
#include <string>

/*
    Inventory.h - uitleg over pointers en ownership in deze file:
    - `Item* items[100];` is een array van 100 pointers naar Item.
        - `Item*` geeft aan dat elk element een adres opslaat van een Item-of-afgeleid-object.
        - Raw pointers hier betekenen dat `Inventory` verantwoordelijk is voor `delete`.
    - Overweeg `std::vector<std::unique_ptr<Item>>` voor veiliger geheugenbeheer.
*/

class Inventory {
    private:
    // Fixed-size container holding pointers to Item objects.
    // For simplicity this example uses a static array; in production prefer std::vector<std::unique_ptr<Item>>.
    // `Item* items[100]` declares an array of 100 pointers to Item.
    // - `Item*` is a pointer type: it stores the address of an Item-derived object.
    // - Using raw pointers here means this class owns the pointed objects and must delete them.
    // - Alternative (safer): use `std::vector<std::unique_ptr<Item>>` to manage ownership automatically.
    Item* items[100];
    // Number of items currently stored (0..100)
    int itemCount;

    public:
    Inventory();
    ~Inventory();

    //methodes
    void add(Item* item);
    void printAll() const;
    bool compare(int i, int j) const;

    //saving and loading file

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    int getItemCount() const { return itemCount; }

};