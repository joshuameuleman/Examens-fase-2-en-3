#pragma once

#include "Item.h"
#include <string>

class Inventory
{
    private:
    /* data */
        Item* items[100];
        int itemCount;
    

    public:
        Inventory();

        ~Inventory();

        void addItem(Item* newItem);
        void printAll() const;
        bool compare(int i, int j) const;
        void saveToFile(const std::string& filename) const;
        void loadFromFile(const std::string& filename);
        int getItemCount() const{return itemCount;} ;

};

