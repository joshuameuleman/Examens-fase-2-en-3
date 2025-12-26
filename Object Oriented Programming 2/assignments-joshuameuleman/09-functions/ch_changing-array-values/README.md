# Changing array values

What is going on here? Why can the `messItUp` function change the values of the passed array?

```cpp
#include <iostream>
using namespace std;

void messItUp(int numbers[], size_t size) {
  for (unsigned int i = 0; i < size; i++) {
    numbers[i] = numbers[i] * 1337;
  }
}

int main() {

  int numbers[] = { 2, 8, 15 };

  messItUp(numbers, sizeof(numbers)/sizeof(numbers[0]));

  for (unsigned int i = 0; i < sizeof(numbers)/sizeof(numbers[0]); i++) {
    cout << numbers[i] << " ";
  }
  cout << endl;

  return 0;
}
```
**answer**

because you call in the function messItUp in your main this means he will do the function 

the function needs some input ( int array and a size (how many bits) )

you declare a int array named number and  initialize with the appropriate values

then you call in the function and give the information through  this will change the array of integers 

