#pragma once

#include "Item.h"
#include <string>
/*
    Potion.h - belangrijke syntaxpunten:
    - `int restore;` is een integer lidvariabele.
    - `Potion(const std::string& name, int restore);` : const reference parameter, voorkomt kopieën.
    - `bool operator==(const Potion& other) const;` : vergelijkings-operator, `const` garandeert geen wijziging.
*/

class Potion : public Item{

private:
 std::string name;
 int restore;

public:
    
    // Constructor: name and restore amount.
    // Use `const std::string&` to avoid copying when passing string literals or variables.
    // See `Weapon.h` comments for details about `&` and `const`.
    Potion(const std::string& name, int restore);

    ~Potion()override= default;

    double value() const override;
    void printInfo() const override;

    bool operator==(const Potion& other) const;

    //getters for name and damage
    // Return the potion's name.
    std::string getName() const {return name;}
    // Return the amount this potion restores.
    int getRestore() const{return restore;}

    
    
};    
