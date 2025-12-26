// main.cpp - thin launcher for Game
#include "game.h"
#include <iostream>
#include <string>

int main() {
    std::cout << "*** Tic-Tac-Toe ***\n";
    std::string n1, n2;
    std::cout << "Enter name of player 1 (X): ";
    std::getline(std::cin, n1);
    if (n1.empty()) std::getline(std::cin, n1);
    std::cout << "Enter name of player 2 (O): ";
    std::getline(std::cin, n2);
    if (n2.empty()) std::getline(std::cin, n2);

    Game game(n1, n2, 3);
    game.run();
    return 0;
}
