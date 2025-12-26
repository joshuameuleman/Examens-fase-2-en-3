#pragma once

#include "Animal.h"
#include <string>
using namespace std;

namespace AnimalTree
{
    class WildBird : public Animal
    {
        public:
            WildBird(const string &food, int birthDay, int birthMonth, int birthYear);
            ~WildBird();
            string getSound() const override;
            string getString() const override;

        private:
            int numberOfLegs;
            int numberOfWings;
    };
}