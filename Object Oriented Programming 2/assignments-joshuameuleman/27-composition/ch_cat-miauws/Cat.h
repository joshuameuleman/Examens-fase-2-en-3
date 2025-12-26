#pragma once
#include <string>
#include "Date.h"

using namespace DateLib;

namespace AnimalTree
{


    class Cat
    {
    private:
        /* data */
      std::string name;
      std::string food;
      Date birthDate;
      int numberOfLegs;
      
    public:
        Cat(Date birthDate, std::string food, std::string name);
        Cat(int birthDay, int birthMonth, int birthYear, std::string name, std::string food);
        ~Cat();
        //methods
        std::string getSound() const;
        std::string getString() const;

    };


}
