/*
    Potion.cpp - korte uitleg:
    - net als Weapon gebruikt Potion een constructor met member initializer list.
    - `value()` berekent een numerieke waarde; hier is dat restore * 4.0.
    - `operator==` vergelijkt naam en restore-waarde.
*/

#include "Potion.h"
#include <stdexcept>
#include <iostream>
Potion::Potion(const std::string& name, int restore) : name(name), restore(restore)
{

    // Validate constructor arguments: restore amount must be positive.
    if (restore <= 0) throw std::invalid_argument("Restore must be greater than zero");

}

double Potion::value() const{
    // Example value calculation: restoration scaled by a factor.
    return restore *4.0;
}

void Potion::printInfo() const{
    // Print a readable description of this potion.
    std::cout << "Potion: " << name << " (restore=  " << restore << ")\n";
}

bool Potion::operator==(const Potion& other) const{

    // Two potions are equal when both name and restore amount match.
    return (name == other.name) && (restore == other.restore);
}


