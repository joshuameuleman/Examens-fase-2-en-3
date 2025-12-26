#include "Bird.h"
#include <sstream>
#include <iostream>

using namespace std;
using namespace AnimalTree;

Bird::Bird(const string &name, const string &food, int birthDay, int birthMonth, int birthYear) : Pet(name, food, birthDay, birthMonth, birthYear),
                                                                                                  numberOfLegs(2),
                                                                                                  numberOfWings(2)
{
    // cout << "Bird constructor" << endl;
}

Bird::~Bird()
{
    // cout << "Bird destructor" << endl;
}

string Bird::getSound() const
{
    return "Sound: Tjilp!!!";
}

string Bird::getString() const
{
    stringstream ss;
    ss << Pet::getString() << ", ";
    ss << "number of legs: " << numberOfLegs << ", ";
    ss << "number of wings: " << numberOfWings;
    return ss.str();
}