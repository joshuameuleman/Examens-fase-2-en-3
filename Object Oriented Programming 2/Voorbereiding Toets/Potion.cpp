#include "Potion.h"
#include <stdexcept>
#include <iostream>

Potion::Potion(const std::string& name , int restore) : name(name), restore(restore) 
{

    if (restore <= 0) 
    {
        throw std::invalid_argument("Restore must be greater than 0.");
    }
    
}

double Potion:: value() const 
{
    return double (restore) * 4.0;
}

void Potion::printInfo() const
{

    std::cout<< "Potion Name: "<< name << ", Restore: " << restore << std::endl; 

}

bool Potion::operator== (const Potion& other) const
{
    return (name == other.name) && (restore == other.restore);
}