#pragma once

#include "Item.h"
#include <string>
/*
    Weapon.h - korte syntaxuitleg relevant voor deze header:
    - Constructor parameter `const std::string& name`: dit is een const reference.
        - `&` betekent reference (geen kopie), `const` betekent dat de functie `name` niet wijzigt.
    - Lidvariabele `std::string name;` is een objectlid dat de naam bewaart.
    - `std::string getName() const` : `const` na de methode zegt dat deze methode het object niet wijzigt.
    - `bool operator==(const Weapon& other) const;` : vergelijkingsoperator; het returntype is `bool`.
*/

class Weapon : public Item{

private:
 std::string name;
 int damage;

public:
    
    // Constructor: takes the weapon name and damage amount.
    // `const std::string& name` means the parameter is a reference (`&`) to an existing
    // string and marked `const` to promise it won't be modified. This avoids an extra copy
    // compared to passing `std::string` by value.
    //
    // Syntax notes:
    // - `T*` denotes a pointer to type T (e.g. `Item*`). A pointer stores an address.
    // - `T&` denotes a reference to type T. References are aliases and must be bound at initialization.
    Weapon(const std::string& name, int damage);

    ~Weapon()override= default;

    double value() const override;
    void printInfo() const override;

    bool operator==(const Weapon& other) const;

    //getters for name and damage
    // Return the stored name of the weapon (returns a copy of `name`).
    // `const` after the method means it does not modify the object.
    std::string getName() const {return name;}
    // Return the damage value (primitive type returned by value).
    int getDamage() const{return damage;}

};    