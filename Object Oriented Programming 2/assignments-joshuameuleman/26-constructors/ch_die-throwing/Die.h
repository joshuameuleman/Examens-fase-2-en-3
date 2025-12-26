// Die.h
#pragma once

#include <random>

class Die {
public:
  // Construct a die with given number of sides (default 6)
  explicit Die(int sides = 6); //explicit to prevent implicit conversions

  // Roll the die and return a value in [1, sides]
  int roll();

private:
  int sides_;
  std::mt19937 engine_; // Mersenne Twister random number engine zorgt voor goede willekeurigheid
  std::uniform_int_distribution<int> dist_; // Uniform distribution for die rolls zorgt zodat de kans op elke zijde gelijk is
};



