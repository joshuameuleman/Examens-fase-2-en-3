# Namespace std

Alter the hello world application by removing the statement `using namespace std;`. Fix the statements that fail by prefixing the required components with `std::`. Try to get the application to compile and run.

```cpp
#include <iostream>

using namespace std;

int main() {
  // Display Hello world! in the terminal
  cout << "Hello world!" << endl;

  return 0;
}
```