#include "Date.h"
#include <iostream>
#include <string>

using namespace std;
using namespace DateLib;

#include "Date.h"
#include "Cat.h"
#include <iostream>
#include <string>

using namespace std;
using namespace DateLib;
using namespace AnimalTree;

int main(int argc, char const *argv[])
{
    try
    {
        Date date1;
        cout << date1.getString() << endl;

        Date date2(16, 10, 2024);
        cout << date2.getString() << endl;

        Cat cat1(date2, "fish", "Mousti");                   // aggregation
        Cat cat2(16, 10, 2024, "fish", "Garfield");          // composition

        cout << cat1.getSound() << endl;
        cout << cat2.getSound() << endl;

        cout << cat1.getString() << endl;
        cout << cat2.getString() << endl;
    }
    catch (const invalid_argument &e)
    {
        cerr << e.what() << '\n';
    }

    return 0;
}