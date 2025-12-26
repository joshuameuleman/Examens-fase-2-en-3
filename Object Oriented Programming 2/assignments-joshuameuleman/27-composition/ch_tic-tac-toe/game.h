// game.h - Tic-Tac-Toe Game class
#pragma once

#include "board.h"
#include "player.h"
#include <string>

class Game {
public:
    Game(const std::string& player1, const std::string& player2, int size = 3);
    void run();

private:
    Board board_;
    Player p1_;
    Player p2_;
    Player* current_;
    char currentMark_;

    bool promptPosition(int& outRow, int& outCol) const;
    bool checkWin(char mark) const;
};
 