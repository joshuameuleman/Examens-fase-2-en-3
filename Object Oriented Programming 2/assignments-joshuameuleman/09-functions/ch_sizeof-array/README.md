# Sizeof array

What is happening here? Why is the output of this code snippet wrong?

```cpp
#include <iostream>
using namespace std;

int sum(int values[]) {
  int result = 0;
  for(unsigned int i = 0; i < sizeof(values); i++) {
    result += values[i];
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
 
 values is declared as int values[]. In function parameters, this is actually treated as int* values, i.e., a pointer to the first element of the array.

sizeof(values) now does not give the size of the array in bytes; it gives the size of a pointer (usually 4 or 8 bytes depending on the system), not the number of elements in the array.

So your loop iterates 4 or 8 times (pointer size), not 3 times (the actual number of elements). Accessing values[3] or beyond is undefined behavior, which can crash your program or give garbage values.



