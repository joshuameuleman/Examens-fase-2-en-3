# Output hexadecimal value

Can you alter the next code snippet so the number is outputted in hexadecimal format, with a leading `0x` and a width of 4 hexadecimal digits? Note that this will require the `iomanip` library to be included (already done for you).

```cpp
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
  int number = 23;
  cout << "Number in hex format: " << number << endl;

  return 0;
}
```

The expected output is:

```text
Number in hex format: 0x0017
```

**answer**