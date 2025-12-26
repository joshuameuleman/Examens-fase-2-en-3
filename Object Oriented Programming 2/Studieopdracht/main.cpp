/*
    Korte C++ I/O en syntax cheatsheet (gebruikt in dit bestand):
    - std::cin >> x;   // leest het volgende token (gescheiden door whitespace)
    - std::getline(std::cin, s); // leest de hele regel tot newline
    - Mixing: na '>>' blijft vaak een '\n' in de buffer; de volgende getline leest dan een lege regel.
        Oplossingen: gebruik std::cin.ignore(...) of std::getline(std::cin >> std::ws, s);
    - std::ws is een manipulator die leading whitespace (inclusief newline) consumeert.
    - std::cin.clear() reset de foutstatus van de stream (bijv. als invoer geen integer was).
    - Gebruik std::numeric_limits<std::streamsize>::max() samen met ignore om tot het einde van de regel te negeren.
    - Belangrijk keywords in dit project: pointer `*`, reference `&`, `const`, `virtual`, `override`.
*/

#include "Inventory.h"
#include "Weapon.h"
#include "Potion.h"
#include <iostream>
#include <limits>
//helper 
#include "Inventory.h"
#include "Weapon.h"
#include "Potion.h"
#include <iostream>
// For stream limits when ignoring bad input
#include <limits>

//helper 

int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if(std::cin>> value){
            // After a formatted extraction with >>, there may be a leftover '\n' in the stream.
            // We consume the rest of the line so subsequent getline calls behave as expected.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        } else {
            std::cout << "Invalid input. Please enter an integer." << std::endl;
            std::cin.clear(); // clear error flag
            // Remove the invalid token from the stream so we don't loop forever.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
std::string readString(const std::string& prompt) {
    
    std::cout << prompt;
    std::string value;
    // Detailed explanation:
    // - `std::getline(stream, value)` reads a whole line until a newline and stores it in `value`.
    // - Problem: mixing `operator>>` (formatted extraction) with `getline` can leave a '\n' in the
    //   input buffer. The next `getline` will then read that empty line and return an empty string.
    // - Fix: `std::ws` is a manipulator that consumes leading whitespace (including a leftover '\n').
    //   By doing `std::cin >> std::ws` we eat up whitespace before calling getline.
    // - Alternative: after `operator>>` call `std::cin.ignore(...)` (done in `readInt`).
    std::getline(std::cin >> std::ws, value);
    return value;
}

int main()
{
    Inventory inv;
    while (true)
    {
        //display menu
        std::cout << "\nMenu:\n"
                  << "1. Add Weapon\n"
                  << "2. Add Potion\n"
                  << "3. Print All Items\n"
                  << "4. Compare Items\n"
                  << "5. Save Inventory to File\n"
                  <<"6. Load Inventory from File\n"
                  << "7.Exit\n";
        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter an integer." << std::endl;
            std::cin.clear(); // clear error flag
            continue;
        }
        try{
        switch (choice)
        {
            case 1: {
                std::string name = readString("Enter weapon name: ");
                int damage = readInt("Enter weapon damage: ");
                inv.add(new Weapon(name, damage));
                break;
            }
            case 2: {
                std::string name = readString("Enter potion name: ");
                int restore = readInt("Enter potion restore amount: ");
                inv.add(new Potion(name, restore));
                break;
            }
            case 3:
                inv.printAll();
                break;
            case 4: {
                int i = readInt("Enter index of first item to compare (1-based): ") - 1;
                int j = readInt("Enter index of second item to compare (1-based): ") - 1;
                bool result = inv.compare(i, j);
                std::cout << "Items are " << (result ? "equal." : "not equal.") << std::endl;
                break;
            }
            case 5: {
                std::string filename = readString("Enter filename to save inventory: ");
                inv.saveToFile(filename);
                std::cout << "Inventory saved to " << filename << std::endl;
                break;
            }
            case 6: {
                std::string filename = readString("Enter filename to load inventory: ");
                inv.loadFromFile(filename);
                std::cout << "Inventory loaded from " << filename << std::endl;
                break;
            }
            case 7:
                std::cout << "Exiting program." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
        } catch (const std::exception& e){
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    
    return 0;
}
