// ...
#include "Bird.h"
#include "Animal.h"
#include "Pet.h"
#include <iostream>
#include <string>

using namespace std;
using namespace AnimalTree;

void print(Animal *animal)
{
    cout << animal->getString() << endl;
}

int main()
{
    Bird bird("Tweety", "seeds", 18, 6, 2022);
    //...

    // no longer possible to create an instance of a class with pure virtual method(s):
    // Animal animal("grass", 1, 1, 2023);    // a cow, goat, ...
    // Pet pet("Blub", "flakes", 1, 1, 2023); // a (gold) fish, ...

    cout << "--- Iterate array with pointers to objects:" << endl;
    Animal *animals[] = { &bird };
    for (int i = 0; i < 1; i++)
    {
        cout << animals[i]->getSound() << endl;
        cout << animals[i]->getString() << endl;
        cout << endl;
    }

    cout << "--- Pointer to an object:" << endl;
    Animal *animal2 = &bird;
    cout << animal2->getSound() << endl;
    cout << animal2->getString() << endl;
    cout << endl;
    // print(animal2);
    // cout << endl;

    // ...

    return 0;
}
