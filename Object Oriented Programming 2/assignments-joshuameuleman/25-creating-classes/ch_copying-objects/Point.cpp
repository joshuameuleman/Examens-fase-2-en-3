// Point.cpp
#include "Point.h"

namespace Geometry {

  void Point::moveTo(double x, double y) {
    this->x = x;
    this->y = y;
  }

  void Point::moveBy(double deltaX, double deltaY) {
    this->x += deltaX;
    this->y += deltaY;
  }
  double Point::getX() const {
    return this->x;
  }

  double Point::getY() const {
    return this->y;
  }

};
