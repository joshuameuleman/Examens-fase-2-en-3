#include "Weapon.h"
#include <stdexcept>
#include <iostream>

Weapon::Weapon(const std::string& name , int damage) : name(name), damage(damage) 
{

    if (damage <= 0) 
    {
        throw std::invalid_argument("Damage must be greater than 0.");
    }
    
}

double Weapon:: value() const 
{
    return double (damage) * 10.0;
}

void Weapon::printInfo() const
{

    std::cout<< "Weapon Name: "<< name << ", Damage: " << damage << std::endl; 

}

bool Weapon::operator== (const Weapon& other) const
{
    return (name == other.name) && (damage == other.damage);
}