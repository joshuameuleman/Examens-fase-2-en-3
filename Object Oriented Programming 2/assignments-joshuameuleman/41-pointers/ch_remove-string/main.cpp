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