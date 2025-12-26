# Move by delta

Extend the `Point` class with a method `moveBy(double deltaX, double deltaY)` that allows the user of a `Point` object to move the point using delta-coordinates.

```cpp
// Point.h
#pragma once

namespace Geometry {

  class Point {

    // Methods
    public:
      void moveTo(double x, double y);

    // Attributes (instance variables)
    private:
      double x = 0;
      double y = 0;

  };

};
```

```cpp
// Point.cpp
#include "Point.h"

namespace Geometry {

  void Point::moveTo(double x, double y) {
    this->x = x;
    this->y = y;
  }

};
```

Basically the delta is added to the current coordinates making it move by delta.