# Day of the week

Refactor the following code snippet using an array of `std::string` elements and lookup the result.

```cpp
#include <iostream>

using namespace std;

int main() {

  unsigned int dayOfTheWeek = 0;
  do {
    cout << "Please enter the day of the week (1 - 7): ";
    cin >> dayOfTheWeek;
  } while (dayOfTheWeek < 1 || dayOfTheWeek > 7);
  
  switch(dayOfTheWeek) {
    case 1:
      std::cout << "Then it's Monday today" << std::endl;
      break;
    case 2:
      std::cout << "Then it's Tuesday today" << std::endl;
      break;
    case 3:
      std::cout << "Then it's Wednesday today" << std::endl;
      break;
    case 4:
      std::cout << "Then it's Thursday today" << std::endl;
      break;
    case 5:
      std::cout << "Then it's Friday today" << std::endl;
      break;
    case 6:
      std::cout << "Then it's Saturday today" << std::endl;
      break;
    case 7:
      std::cout << "Then it's Sunday today" << std::endl;
      break;
  }

  return 0;
}
```