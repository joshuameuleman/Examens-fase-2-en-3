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
            virtual ~Pet();
            virtual string getSound() const override;
            virtual string getString() const override;

        private:
            string name;
    };
}