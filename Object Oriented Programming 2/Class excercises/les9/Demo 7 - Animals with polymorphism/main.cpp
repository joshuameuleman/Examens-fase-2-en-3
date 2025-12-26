#include "Cat.h"
#include "Dog.h"
#include "Bird.h"
#include "WildBird.h"
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
    Cat cat("Garfield", "fish", 16, 10, 2024);
    Dog dog("Pluto", "meat", 13, 5, 2020);
    Bird bird("Tweety", "seeds", 18, 6, 2022);
    WildBird wildBird("seeds and nuts", 10, 5, 2023);
    Animal animal("grass", 1, 1, 2023);    // a cow, goat, ...
    Pet pet("Blub", "flakes", 1, 1, 2023); // a (gold) fish, ...

    cout << "--- Iterate array with pointers to objects:" << endl;
    Animal *animals[] = {&cat, &dog, &bird, &wildBird, &animal, &pet};
    for (int i = 0; i < 6; i++)
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

    cout << "--- Object in stack (start):" << endl;
    {
        Bird bird2("Coco", "nuts", 8, 8, 2024);
        cout << bird2.getSound() << endl;
        cout << bird2.getString() << endl;
    }
    cout << "--- Object in stack (end)" << endl << endl;

    cout << "--- Object in heap (start):" << endl;
    Animal *animal3 = new Bird("Coco", "nuts", 8, 8, 2024);
    cout << animal3->getSound() << endl;
    cout << animal3->getString() << endl;
    // print(animal3);
    delete animal3;
    cout << "--- Object in heap (end)" << endl << endl;

    return 0;
}
