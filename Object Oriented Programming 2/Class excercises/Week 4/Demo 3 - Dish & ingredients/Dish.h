#ifndef DISH_H
#define DISH_H

#include <string>
#include "Ingredient.h"

class Dish {
    private:
        std::string dishName;
        Ingredient mainIngredient;

    public:
        Dish(std::string dishName, Ingredient ingredient);
        void display() const;
};

#endif
