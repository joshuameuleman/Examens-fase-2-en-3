# Remove string

## Objective

Write a function `removeString` that removes all occurrences of a specific string from an array of strings. Remaining elements in the array should be shifted to the left to fill the empty spots, and the trailing elements must be replaced with dots (`"."`).

Also, implement the `getString` function, which concatenates all elements in the array into a single space-separated string. There should be no space after the last element.

### Constraints

* You **must not** use the array subscript operator (`[]`). Only pointer notation is allowed.
* The functions must be implemented in **separate files** from the main program.
* Do **not** change the provided `main()` function.

## Provided Test Program

Save the following code in a file called `main.cpp`:

```cpp
// make no changes to this file!
#include "functions.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
    const int MAX_NUMBER = 9;
    string array[MAX_NUMBER] = { "apple", "banana", "grape", "orange", "apple", "peach", "banana", "banana", "kiwi" };

    printf("Original array: ");
    cout << getString(array, MAX_NUMBER) << endl;
    assert(getString(array, MAX_NUMBER) == "apple banana grape orange apple peach banana banana kiwi");

    removeString("banana", array, MAX_NUMBER); // remove all occurrences of "banana"
    removeString("pear", array, MAX_NUMBER);   // nothing happens

    printf("Manipulated array: ");
    cout << getString(array, MAX_NUMBER) << endl;
    assert(getString(array, MAX_NUMBER) == "apple grape orange apple peach kiwi . . .");

    return 0;
}
```

## Expected Output

```
Original array: apple banana grape orange apple peach banana banana kiwi
Manipulated array: apple grape orange apple peach kiwi . . .
```

## Implementation Details

* `removeString`: This function removes all elements equal to a target string. Use **two pointer variables**: one for reading (`readPtr`) and one for writing (`writePtr`).

  The write pointer overwrites only the elements that should remain, and at the end of the loop, the remaining elements (from `writePtr` to end) should be set to `"."`.

* `getString`: This function concatenates the strings in the array using a space `" "` as delimiter. Ensure there is **no trailing space** at the end.

## File Structure

Create the following files:
```text
main.cpp
functions.h
function.cpp
```

## Tip

Draw a diagram of how the `readPtr` and `writePtr` traverse the array. This helps understand the shifting logic and where to place the dots (`"."`).

