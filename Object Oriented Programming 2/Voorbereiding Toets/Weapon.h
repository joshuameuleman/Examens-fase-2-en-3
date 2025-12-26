#pragma once 

#include "Item.h"
#include <string>
class Weapon : public Item
{
    private:
        std::string name;
        int damage;
    public:
        Weapon(const std::string& name, int damage);
        ~Weapon() override = default;
        
        double value() const override;
        void printInfo() const override;

        // overload equality operator (==)
        bool operator==(const Weapon& other) const;
        const std::string& getName() const {return name;}
        int getDamage() const {return damage;}


};