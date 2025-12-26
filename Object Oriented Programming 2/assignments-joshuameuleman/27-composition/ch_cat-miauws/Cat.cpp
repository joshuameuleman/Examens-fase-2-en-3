#include "Cat.h"
#include "Date.h"
#include <iostream>
#include <string>
using namespace DateLib;
using namespace AnimalTree;


namespace AnimalTree{
    
    Cat::Cat(Date birthDate, std::string food, std::string name)
    
    {
        this->birthDate = birthDate;
        this->food = food;
        this->name = name;
        this->numberOfLegs = 4; // default 4 legs

        std:: cout << "Name:" << this->name << ", Birthdate:" << this->birthDate.getString() << ", number of legs:" << this->numberOfLegs << ", food:"<< this->food << std::endl;
    }

    Cat::Cat(int birthDay, int birthMonth, int birthYear, std::string food, std::string name)
    
    {
        
        this->food = food;
        this->name = name;
        this->numberOfLegs = 4; // default 4 legs

        std:: cout << "Name:" << this->name << ", Birthdate: " << birthDay << "/" << birthMonth << "/" << birthYear << ", number of legs:" << this->numberOfLegs << ", food:"<< this->food << std::endl;
    }

    Cat::~Cat()
    {

        std::cout <<"destructor called for Cat: "<<this->name<< std::endl;
    }

    std::string Cat:: getSound() const
    {

        return "Sound: Miauw!!!";
    }
    std::string Cat:: getString() const
    {

        return " ";
    }
}


