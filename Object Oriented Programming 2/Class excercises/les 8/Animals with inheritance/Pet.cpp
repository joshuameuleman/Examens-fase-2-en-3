#include "Pet.h"
#include <sstream>
#include <iostream>

using namespace std;
using namespace AnimalTree;

Pet::Pet(const string &name, const string &food, int birthDay, int birthMonth, int birthYear) : Animal(food, birthDay, birthMonth, birthYear),
                                                                                                name(name)
{
    // cout << "Pet constructor" << endl;
}

Pet::~Pet()
{
    // cout << "Pet destructor" << endl;
}

string Pet::getSound() const
{
    return "Sound: ?";
}

string Pet::getString() const
{
    stringstream ss;
    ss << "Name: " << name << ", ";
    ss << Animal::getString();
    return ss.str();
}