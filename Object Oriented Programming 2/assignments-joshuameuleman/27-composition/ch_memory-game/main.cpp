// main.cpp
#include "game.h"
#include <iostream>
#include <string>

int main() {
    std::cout << "*** Memory Game ***\n";
    std::string name1, name2;
    std::cout << "Enter name of player 1: ";
    std::getline(std::cin, name1);
    if (name1.empty()) std::getline(std::cin, name1);
    std::cout << "Enter name of player 2: ";
    std::getline(std::cin, name2);
    if (name2.empty()) std::getline(std::cin, name2);

    int rows = 4, cols = 4;
    std::cout << "Enter board rows (even*): ";
    std::string line;
    std::getline(std::cin, line);
    if (!line.empty()) rows = std::stoi(line);
    std::cout << "Enter board cols (even*): ";
    std::getline(std::cin, line);
    if (!line.empty()) cols = std::stoi(line);

    std::cout << "Enable DEBUG mode (show all cards)? (y/n): ";
    std::string dbg;
    std::getline(std::cin, dbg);
    bool debug = (!dbg.empty() && (dbg[0] == 'y' || dbg[0] == 'Y'));

    try {
        Game game(name1, name2, rows, cols, debug);
        game.run();
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}
