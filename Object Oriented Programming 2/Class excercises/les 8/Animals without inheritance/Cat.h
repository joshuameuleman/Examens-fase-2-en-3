#pragma once

#include "Date.h"
#include <string>
using namespace std;
using namespace DateLib;

namespace AnimalTree
{
    class Cat
    {
        public:
            Cat(const string &name, const string &food, int birthDay, int birthMonth, int birthYear);
            ~Cat();
            string getSound() const;
            string getString() const;

        private:
            string name;
            string food;
            Date birthdate;
            int numberOfLegs;
    };
}