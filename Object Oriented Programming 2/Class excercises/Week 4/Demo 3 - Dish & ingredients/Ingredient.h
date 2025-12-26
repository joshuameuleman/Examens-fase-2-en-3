#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient {
    private:
        std::string name;
        int calories;

    public:
        Ingredient(std::string name, int calories);

        void display() const;
        int getCalories() const;
        std::string getName() const;
};

#endif
