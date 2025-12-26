#pragma once 

#include "Item.h"
#include <string>

class Potion : public Item
{
    private:
        std::string name;
        int restore;
    public:
        Potion(const std::string& name, int restore);
        ~Potion() override = default;
        
        double value() const override;
        void printInfo() const override;

        // overload equality operator (==)
        bool operator==(const Potion& other) const;

        const std::string& getName() const {return name;}
        
        int getRestore() const {return restore;}

};