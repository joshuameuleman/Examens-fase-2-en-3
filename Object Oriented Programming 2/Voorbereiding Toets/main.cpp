#include <iostream>
#include "Inventory.h"
#include "Weapon.h"
#include "Potion.h"

int readInt(const std::string& prompt)
{
    int value;
    while (true)
    {
        std::cout << prompt;
        if (std::cin >> value)
        {
            return value;
        }
        else
        {
            std::cin.clear(); // clear error flag
            std::cout << "Invalid input. Please enter an integer.\n";
        }
    }
}
std::string readString(const std::string& prompt)
{
    std::string value;
    std::cout << prompt;
    std::cin >> value;
    return value;
}

int main(int argc, char const *argv[])
{
    Inventory inv;
    
    while(true)
    {
        std::cout <<  "1. Add Weapon\n"
                      "2. Add Potion\n"
                      "3. Show All Items\n"
                      "4. Compare two Items\n"
                      "5. Save to File\n"
                      "6. Load from File\n"
                      "7. Exit\n"
                      "Choose an option: ";
        int choice;
        if (!(std::cin >> choice))
        {
            std::cin.clear(); // clear error flag
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        
        try{
            switch (choice)
            {
                case 1:
                {
                    std::string name= readString("Enter weapon name: ");
                    int damage= readInt("Enter weapon damage: ");
                    inv.addItem(new Weapon(name, damage));
                    break;
                }
                case 2:
                {
                    std::string name= readString("Enter potion name: ");
                    int restore= readInt("Enter potion restore amount: ");
                    inv.addItem(new Potion(name, restore));
                    break;
                }
                case 3:
                {
                    inv.printAll();
                    break;
                }
                case 4:
                {
                    int i =readInt("index i: ");
                    int j =readInt("index j: ");
                    bool equal = inv.compare(i, j);
                    std::cout << (equal ? "Equal\n" : "Not Equal\n");
                    
                }
                case 5:
                {
                    
                    std::string filename= readString("Enter filename to save: ");
                    inv.saveToFile(filename);
                    std::cout << "Saved\n";
                    break;
                }
                case 6:
                {
                    std::string filename= readString("Enter filename to load: ");
                    
                    inv.loadFromFile(filename);
                    std::cout << "Loaded\n";
                    break;
                   
                }
                case 7:
                {
                    std::cout << "Exiting...\n";
                    return 0;
                }
                default:
                    std::cout << "Invalid choice. Try again.\n";
            }
        }
    
        catch (const std::exception& e)
        {
            std::cout << "Error: " << e.what() << "\n";
        }

    return 0;
    }
}
