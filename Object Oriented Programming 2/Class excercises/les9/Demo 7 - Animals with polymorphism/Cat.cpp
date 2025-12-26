#include "Cat.h"
#include <sstream>
#include <iostream>

using namespace AnimalTree;

Cat::Cat(const string &name, const string &food, int birthDay, int birthMonth, int birthYear) : Pet(name, food, birthDay, birthMonth, birthYear),
                                                                                                numberOfLegs(4)
{
    // cout << "Cat constructor" << endl;
}

Cat::~Cat()
{
    // cout << "Cat destructor" << endl;
}

string Cat::getSound() const
{
    return "Sound: Miauw!!!";
}

string Cat::getString() const
{
    stringstream ss;
    ss << Pet::getString() << ", ";
    ss << "number of legs: " << numberOfLegs;
    return ss.str();
}