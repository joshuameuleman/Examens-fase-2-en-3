#pragma once

#include "Date.h"
#include <string>
using namespace std;
using namespace DateLib;

namespace AnimalTree
{
    class Animal
    {
        public:
            Animal(const string &food, int birthDay, int birthMonth, int birthYear);
            ~Animal();
            string getSound() const;
            string getString() const;

        private:
            string food;
            Date birthdate;
    };
}