// Die.cpp
#include "Die.h"
#include <random>
#include <stdexcept>

Die::Die(int sides) : sides_(sides), engine_(), dist_(1, sides_) {
    if (sides_ < 2) {
        throw std::invalid_argument("A die must have at least two sides.");
    }
    std::random_device rd;
    engine_.seed(rd());
}

int Die::roll() {
    return dist_(engine_);
  
}
