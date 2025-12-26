#pragma once
#include <string>

// Removes all occurrences of 'target' from the array of strings.
// Remaining entries should be shifted left and trailing elements set to ".".
// Implementation must use pointer notation (no [] operator).
void removeString(const std::string& target, std::string array[], int size);

// Concatenates all elements into a single space-separated string (no trailing space).
// Implementation must use pointer notation (no [] operator).
std::string getString(std::string array[], int size);
