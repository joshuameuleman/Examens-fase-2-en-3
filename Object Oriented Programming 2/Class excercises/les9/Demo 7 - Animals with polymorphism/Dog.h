#pragma once

#include "Pet.h"
#include <string>
using namespace std;

namespace AnimalTree
{
    class Dog : public Pet
    {
        public:
            Dog(const string &name, const string &food, int birthDay, int birthMonth, int birthYear);
            ~Dog();
            string getSound() const override;
            string getString() const override;

        private:
            int numberOfLegs;
    };
}