// Point.h
#pragma once

namespace Geometry {

  class Point {

    // Methods
    public:
      void moveTo(double x, double y);
      void moveBy(double deltaX, double deltaY);

    // Attributes (instance variables)
    private:
      double x = 0;
      double y = 0;

  };

};