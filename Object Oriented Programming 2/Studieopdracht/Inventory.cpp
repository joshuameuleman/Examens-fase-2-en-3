/*
    Inventory.cpp - uitleg en voorbeelden in context:
    - `nullptr` is de veilige null-pointer constante (gebruik in plaats van 0 of NULL).
    - `delete ptr;` geeft geheugen vrij dat eerder door `new` is verkregen.
    - `dynamic_cast<T*>(p)` controleert runtime of `p` het type heeft dat je verwacht (werkt op polymorfe types).
    - Best practice: vermijd raw `new`/`delete` en gebruik smart pointers (`unique_ptr`) en containers (`vector`).
*/

#include "Inventory.h"
#include "Weapon.h"
#include "Potion.h"

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>

Inventory::Inventory() : itemCount(0) {
    // Initialize item pointers to nullptr
    // Use array indexing for clarity: set every slot to nullptr initially.
    // `nullptr` is the modern null pointer constant (safer than 0 or NULL).
    for (int i = 0; i < 100; ++i) items[i] = nullptr;

}

Inventory::~Inventory() {
    // Clean up allocated items
    for (int i = 0; i < itemCount; i++) {
        // `delete` releases memory allocated with `new`.
        // Because this class stores raw `Item*` pointers and owns them, we must `delete` them.
        // After deleting, set the pointer to nullptr to avoid dangling pointers.
        delete items[i];
        items[i] = nullptr;
    }
}

void Inventory::add(Item* item){
    if (itemCount >= 100) {
        throw std::runtime_error("Inventory is full");
    }

    // The caller typically passes a pointer obtained from `new` (e.g. `new Weapon(...)`).
    // Responsibility: Inventory takes ownership of the pointer and will delete it in the destructor.
    items[itemCount++] = item;
}

void Inventory::printAll() const{
    for (int i = 0; i < itemCount; i++) {
        std::cout << i+1 << " : ";
    
        items[i]->printInfo();
    }
}

bool Inventory::compare( int i, int j) const{
    if (i < 0 || i >= itemCount || j < 0 || j >= itemCount) {
        throw std::out_of_range("Index out of range");
    }


    // `dynamic_cast<T*>(ptr)` attempts a safe downcast at runtime (requires RTTI).
    // If `items[i]` actually points to a Weapon, the result is a non-null pointer.
    // If not, it returns nullptr. This is why we can use it to check runtime type.
    if (Weapon* w1 = dynamic_cast<Weapon*>(items[i])) {
        if (Weapon* w2 = dynamic_cast<Weapon*>(items[j])) {
            return *w1 == *w2; // operator== compares name and damage
        } else {
            throw std::runtime_error("Different item types cannot be compared");
        }
    }

    // Try to dynamic_cast to Potion
    if (Potion* p1 = dynamic_cast<Potion*>(items[i])) {
        if (Potion* p2 = dynamic_cast<Potion*>(items[j])) {
            return *p1 == *p2; // operator== compares name and restore value
        } else {
            throw std::runtime_error("Different item types cannot be compared");
        }
    }

    throw std::runtime_error("Unknown item types cannot be compared");
}

void Inventory::saveToFile(const std::string& filename) const{
   // open file for writing
   std::ofstream file;
   file.open(filename,std::ios::trunc);
    if (!file.is_open()) {
         throw std::runtime_error("Could not open file for writing");
    }
    //write items to file
    for (int i = 0; i < itemCount; i++){
        if (auto w1 = dynamic_cast<Weapon*>(items[i])) {
            file << "WEAPON," << w1->getName() << "," << w1->getDamage() << "\n";
        } else if (auto p1 = dynamic_cast<Potion*>(items[i])) {
            file << "POTION," << p1->getName() << "," << p1->getRestore() << "\n";
        }
    }
    file.close();
}

void Inventory::loadFromFile(const std::string& filename){
    //open file for reading
    std::ifstream file;
    file.open(filename);
    if (!file.is_open()) {
         throw std::runtime_error("Could not open file for reading");
    }

    //clear current inventory
    for (int i = 0; i < itemCount; i++) {
        delete items[i];
        items[i] = nullptr;
    }
    itemCount = 0;

    //read items from file
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string type, name, valueStr;

        if (!std::getline(ss, type, ',' ) || !std::getline(ss, name, ',') || !std::getline(ss, valueStr)) {
            throw std::runtime_error("Malformed line in file: " + line);
        }

        int value = std::stoi(valueStr);

        if (type == "WEAPON") {
            add(new Weapon(name, value));
        } else if (type == "POTION") {
            add(new Potion(name, value));
        } else {
            throw std::runtime_error("Unknown item type in file: " + type);
        }
    }

    file.close();

    
}

