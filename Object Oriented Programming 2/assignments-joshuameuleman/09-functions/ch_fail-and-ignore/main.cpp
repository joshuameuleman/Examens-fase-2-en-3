#include <iostream>

using namespace std;

int main() {

  int number = 0;
  do {
    cout << "Please enter a number between 1 and 10: ";
    cin >> number;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000,'\n'); //ignore bad input
        cout << "invalid input, try again"<<endl;
    }
  } while (number < 1 || number > 10);

  return 0;
}