#include "Dish.h"
#include <iostream>

Dish::Dish(std::string dishName, Ingredient ingredient)
    : dishName(dishName), mainIngredient(ingredient) {}

void Dish::display() const {
    std::cout << "Dish: " << dishName << std::endl;
    std::cout << "--- Main Ingredient ---" << std::endl;
    mainIngredient.display();
}
