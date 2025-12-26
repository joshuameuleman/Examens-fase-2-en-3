#include <iostream>
using namespace std;

// markdown: What is happening here? Why is the output of this code snippet wrong?

int sum(int values[],int size) { // values is actually an int* must add size as parameter
  int result = 0;
  for(unsigned int i = 0; i < size; i++) {
    result += values[i];
  }
  return result;
}

int main() {

  int numbers[] = { 2, 8, 15 };

  cout << "Sum of numbers: "
    << sum(numbers, sizeof(numbers) / sizeof(numbers[0])) << endl;

  return 0;
}