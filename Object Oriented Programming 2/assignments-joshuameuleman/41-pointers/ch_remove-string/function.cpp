#include "functions.h"
#include <string>

// & means "address of", so we use pointers to manipulate the array
// * means "value at address", so we dereference pointers to get/set values
//

void removeString(const std::string& target, std::string array[], int size) {
    std::string* readPtr = array;
    std::string* writePtr = array;
    std::string* endPtr = array + size;

    while (readPtr < endPtr) {
        if (*readPtr != target) {
            *writePtr = *readPtr;
            ++writePtr;
        }
        ++readPtr;
    }

    // fill trailing slots with dots
    while (writePtr < endPtr) {
        *writePtr = ".";
        ++writePtr;
    }
}

std::string getString(std::string array[], int size) {
    std::string result;
    std::string* ptr = array;
    std::string* endPtr = array + size;
    bool first = true;
    while (ptr < endPtr) {
        if (!first) result += ' ';
        result += *ptr;
        first = false;
        ++ptr;
    }
    return result;
}
