#pragma once

#include "Date.h"
#include <string>
using namespace std;
using namespace DateLib;

namespace AnimalTree
{
    class WildBird
    {
        public:
            WildBird(const string &food, int birthDay, int birthMonth, int birthYear);
            ~WildBird();
            string getSound() const;
            string getString() const;

        private:
            string food;
            Date birthdate;
            int numberOfLegs;
            int numberOfWings;
    };
}