#include <iostream>

using namespace std;

int main() {

  unsigned int dayOfTheWeek = 0;
  string daysOfTheWeek[] ={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
  do {
    cout << "Please enter the day of the week (1 - 7): ";
    cin >> dayOfTheWeek;
  } while (dayOfTheWeek < 1 || dayOfTheWeek > 7);
  
  switch(dayOfTheWeek) {
    case 1:
      cout << "Then it's " << daysOfTheWeek[0] << " today" << endl;
      break;
    case 2:
      cout << "Then it's " << daysOfTheWeek[1] << " today" << endl;
      break;
    case 3:
      cout << "Then it's " << daysOfTheWeek[2] << " today" << endl;
      break;
    case 4:
      cout << "Then it's " << daysOfTheWeek[3] << " today" << endl;
      break;
    case 5:
      cout << "Then it's " << daysOfTheWeek[4] << " today" << endl;
      break;
    case 6:
      cout << "Then it's " << daysOfTheWeek[5] << " today" << endl;
      break;
    case 7:
      cout << "Then it's " << daysOfTheWeek[6] << " today" << endl;
      break;
  }

  return 0;
}