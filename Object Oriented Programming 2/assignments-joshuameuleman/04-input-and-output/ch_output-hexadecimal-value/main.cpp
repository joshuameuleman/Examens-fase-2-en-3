#include <iostream>
#include <iomanip>

using namespace std;

int main() {
  int number = 23;
  cout << "Number in hex format: " <<hex<<showbase<<internal<<setw(6)<<setfill('0')<< number << endl;

  return 0;
}