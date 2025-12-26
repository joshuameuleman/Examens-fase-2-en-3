#include "Animal.h"
#include <sstream>
#include <iostream>

using namespace std;
using namespace DateLib;
using namespace AnimalTree;

Animal::Animal(const string &food, int birthDay, int birthMonth, int birthYear) : food(food),
                                                                                  birthdate(birthDay, birthMonth, birthYear)
{
    // cout << "Animal constructor" << endl;
}

Animal::~Animal()
{
    // cout << "Animal destructor" << endl;
}

/*
string Animal::getSound() const
{
    return "Sound: ?";
}
*/

string Animal::getString() const
{
    stringstream ss;
    ss << "birthdate: " << birthdate.getString() << ", ";
    ss << "food: " << food;
    return ss.str();
}