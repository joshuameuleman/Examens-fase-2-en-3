#pragma once

#include "Date.h"
#include <string>
using namespace std;
using namespace DateLib;

namespace AnimalTree
{
    class Bird
    {
        public:
            Bird(const string &name, const string &food, int birthDay, int birthMonth, int birthYear);
            ~Bird();
            string getSound() const;
            string getString() const;

        private:
            string name;
            string food;
            Date birthdate;
            int numberOfLegs;
            int numberOfWings;
    };
}