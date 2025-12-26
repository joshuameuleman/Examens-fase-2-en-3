#pragma once

#include "Pet.h"
#include <string>
using namespace std;

namespace AnimalTree
{
    class Cat : public Pet
    {
        public:
            Cat(const string &name, const string &food, int birthDay, int birthMonth, int birthYear);
            ~Cat();
            string getSound() const override;
            string getString() const override;

        private:
            int numberOfLegs;
    };
}