#include <iostream>
#include "Ingredient.h"
#include "Dish.h"

int main() {
    Ingredient tomato("Tomato", 22);
    Dish salad("Tomato Salad", tomato);

    salad.display();

    return 0;
}
