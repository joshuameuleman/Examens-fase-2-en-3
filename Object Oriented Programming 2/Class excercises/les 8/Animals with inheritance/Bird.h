#pragma once

#include "Pet.h"
#include <string>
using namespace std;

namespace AnimalTree
{
    class Bird : public Pet
    {
        public:
            Bird(const string &name, const string &food, int birthDay, int birthMonth, int birthYear);
            ~Bird();
            string getSound() const;
            string getString() const;

        private:
            int numberOfLegs;
            int numberOfWings;
    };
}