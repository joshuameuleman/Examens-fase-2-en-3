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