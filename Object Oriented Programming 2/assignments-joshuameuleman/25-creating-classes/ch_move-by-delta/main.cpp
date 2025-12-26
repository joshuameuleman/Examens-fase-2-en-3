// main.cpp
#include <iostream>
#include "Point.h"

int main() {
  Geometry::Point p;
  p.moveTo(1.0, 2.0);
  p.moveBy(3.0, -1.0);
  std::cout << "moveTo + moveBy aangeroepen (controleer gedrag in debugger of voeg getters toe)\n";
  return 0;
}