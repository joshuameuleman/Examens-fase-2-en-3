#include "Bird.h"
#include <sstream>
#include <iostream>

using namespace std;
using namespace DateLib;
using namespace AnimalTree;

Bird::Bird(const string &name, const string &food, int birthDay, int birthMonth, int birthYear) : name(name),
                                                                                                  food(food),
                                                                                                  birthdate(birthDay, birthMonth, birthYear),
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
    ss << "Name: " << name << ", ";
    ss << "birthdate: " << birthdate.getString() << ", ";
    ss << "food: " << food << ", ";
    ss << "number of legs: " << numberOfLegs << ", ";
    ss << "number of wings: " << numberOfWings;
    return ss.str();
}