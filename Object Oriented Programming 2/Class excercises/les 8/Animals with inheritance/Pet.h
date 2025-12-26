#pragma once

#include "Animal.h"
#include <string>
using namespace std;

namespace AnimalTree
{
    class Pet : public Animal
    {
        public:
            Pet(const string &name, const string &food, int birthDay, int birthMonth, int birthYear);
            ~Pet();
            string getSound() const;
            string getString() const;

        private:
            string name;
    };
}