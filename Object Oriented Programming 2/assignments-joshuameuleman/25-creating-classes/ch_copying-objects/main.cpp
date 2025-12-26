#include <iostream>
#include "Point.h"

using namespace std;

int main() {
  Geometry::Point first;
  first.moveTo(10, 20);
  cout << "First is at ["
    << first.getX() << ", " << first.getY() << "]" << endl;

  // Initialize second point with first
  Geometry::Point second = first;

  cout << "Second is at ["
    << second.getX() << ", " << second.getY() << "]" << endl;

  cout << "Moving first point to 103, 1234" << endl;
  first.moveTo(103, 1234);

  cout << "First is at ["
    << first.getX() << ", " << first.getY() << "]" << endl;

  cout << "Second is at ["
    << second.getX() << ", " << second.getY() << "]" << endl;

  return 0;
}