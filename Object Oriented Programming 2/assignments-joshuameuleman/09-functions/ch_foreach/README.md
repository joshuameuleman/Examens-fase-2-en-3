# Foreach

What is wrong with the code below?

```cpp
#include <iostream>
using namespace std;

int sum(int values[]) {
  int result = 0;
  for(auto value : values) {
    result += value;
  }
  return result;
}

int main() {

  int numbers[] = { 2, 8, 15 };

  cout << "Sum of numbers: "
    << sum(numbers) << endl;

  return 0;
}
```

**answer**


you can't pass a array to a functions this will turn into a pointer to it's element

inside sum the parameter values is not een arry but an int* (pointer)

