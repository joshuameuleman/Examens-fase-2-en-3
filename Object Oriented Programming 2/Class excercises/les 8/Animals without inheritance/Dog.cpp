#include "Dog.h"
#include <sstream>
#include <iostream>

using namespace AnimalTree;

Dog::Dog(const string &name, const string &food, int birthDay, int birthMonth, int birthYear) : name(name),
                                                                                                food(food),
                                                                                                birthdate(birthDay, birthMonth, birthYear),
                                                                                                numberOfLegs(4)
{
    // cout << "Dog constructor" << endl;
}

Dog::~Dog()
{
    // cout << "Dog destructor" << endl;
}

string Dog::getSound() const
{
    return "Sound: Woof!!!";
}

string Dog::getString() const
{
    stringstream ss;
    ss << "Name: " << name << ", ";
    ss << "birthdate: " << birthdate.getString() << ", ";
    ss << "food: " << food << ", ";
    ss << "number of legs: " << numberOfLegs;
    return ss.str();
}