#include <iostream>

using namespace std;

int main() {




//it would trigger the failbit of cin.
//the variable "number" will still be undefined.


    cout << "Please enter a number: ";
    int number;
    cin >> number;

    if (cin.fail()) {
        cout << "Invalid input!" << endl;
    }
}