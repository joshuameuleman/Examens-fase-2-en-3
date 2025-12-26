#include "Ingredient.h"
#include <iostream>

Ingredient::Ingredient(std::string name, int calories)
    : name(name), calories(calories) {}

void Ingredient::display() const {
    std::cout << "Ingredient: " << name << ", Calories: " << calories << " kcal" << std::endl;
}

int Ingredient::getCalories() const {
    return calories;
}

std::string Ingredient::getName() const {
    return name;
}
