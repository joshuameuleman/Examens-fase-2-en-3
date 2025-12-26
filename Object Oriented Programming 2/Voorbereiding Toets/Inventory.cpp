#include "Inventory.h"
#include <stdexcept>
#include <iostream>
#include "Weapon.h"
#include "Potion.h"
#include <fstream>
#include <sstream>



Inventory::Inventory(): itemCount(0) 
{
    for (int i = 0; i < 100; ++i) *(items+i) = nullptr;
    
}

Inventory::~Inventory()
{
    for (int i =0; i < itemCount; ++i)
    {
        delete items[i];
        items[i] = nullptr;
    }

}

void Inventory::addItem(Item* newItem)
{
    if (itemCount >=100)
    {
        throw std::runtime_error("Inventory is full, cannot add more items.");
    }        
    items[itemCount]= newItem;
        itemCount++;
}
void Inventory::printAll() const
{
    for (int i = 0; i < itemCount; ++i)
    {
        std:: cout <<i+1<<" : ";
        items [i]->printInfo();

    }
}

bool Inventory::compare(int i, int j) const
//with dynamic cast
{
   if (i < 0 || j <0 || i >= itemCount || j >= itemCount)
   {
        throw std::out_of_range ("Index out of range in compare function.");
   }

    if( auto w1 = dynamic_cast<Weapon*>(items[i]))
    {
            if (auto w2 = dynamic_cast<Weapon*>(items[j]))
            {
                return (*w1 == *w2);
            }
            else
            {
                throw std::runtime_error("Items are of different types, cannot compare.");
            }
        
    }
    if (auto p1 = dynamic_cast<Potion*>(items[i]))
    {
            if (auto p2 = dynamic_cast<Potion*>(items[j]))
            {
                return (*p1 == *p2);
            }

            else
            {
                throw std::runtime_error("Items are of different types, cannot compare.");
            }
        
    }
    throw std::runtime_error("Unknown item types, cannot compare.");
}

void Inventory::saveToFile(const std::string& filename)const
{
    std::ofstream file;

    file.open (filename,std::ios::trunc);


    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file for writing.");
    }

   for (int i = 0; i< itemCount; ++i)
   {
        if (auto w = dynamic_cast<Weapon*>(items[i]))
        {
            file << "WEAPON " << w->getName() << " " << w->getDamage() << "\n";
        }
        else if (auto p = dynamic_cast<Potion*>(items[i]))
        {
            file << "POTION " << p->getName() << " " << p->getRestore() << "\n";
        }
   }
   file.close();
   
}

void Inventory::loadFromFile(const std::string& filename)
{
    std::ifstream file;
    file.open (filename);

    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file for reading.");
    }

    // Clear existing items
    for (int i =0; i < itemCount; ++i)
    {
        delete items[i];
        items[i] = nullptr;
    }
    itemCount =0;

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        std::istringstream iss (line);
        std::string type;
        iss >> type;

        if (type == "WEAPON")
        {
            std::string name;
            int damage;
            iss >> name >> damage;
            addItem(new Weapon(name, damage));
        }
        else if (type == "POTION")
        {
            std::string name;
            int restore;
            iss >> name >> restore;
            addItem(new Potion(name, restore));
        }
        else
        {
            throw std::runtime_error("Unknown item type in file.");
        }
    }
    
    file.close();
}