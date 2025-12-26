/*
    Weapon.cpp - uitleg:
    - Member initializer list: `Weapon::Weapon(...) : name(name), damage(damage) {}`
        initialiseert leden direct, wat vaak efficiënter is dan toewijzen in de constructor body.
    - `throw std::invalid_argument(...)` gooit een uitzondering bij ongeldige argumenten.
    - `std::cout << ...` gebruikt stream-operatoren voor output.
*/

#include "Weapon.h"
#include <stdexcept>
#include <iostream>
Weapon::Weapon(const std::string& name, int damage) : name(name), damage(damage)
{

    // Member initializer list (the part after `:`) initializes members `name` and `damage` directly.
    // This is more efficient for members like std::string than assigning in the constructor body.
    // Validate constructor arguments: damage must be positive.
    if (damage <= 0) throw std::invalid_argument("Damage must be greater than zero");

}

double Weapon::value() const{
    // Example value calculation: damage scaled by a factor.
    return damage *10.0;
}

void Weapon::printInfo() const{
    // Print a readable description of this weapon.
    // `<<` streams data into stdout. `\n` adds a newline.
    std::cout << "Weapon: " << name << " (damage=  " << damage << ")\n";
}

bool Weapon::operator==(const Weapon& other) const{

    // Two weapons are considered equal when both name and damage match.
    return (name == other.name) && (damage == other.damage);
}