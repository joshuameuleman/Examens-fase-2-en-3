// board.h - Tic-Tac-Toe board (3x3 by default)
#pragma once

#include <vector>
#include <iostream>

class Board {
public:
    // default 3x3 board
    Board(int rows = 3, int cols = 3);

    void init(); // clear board
    void display(std::ostream& os = std::cout) const;

    // 1-based coordinates
    bool isValidPosition(int row, int col) const;
    char getCell(int row, int col) const;
    // returns true if successfully set (cell was empty)
    bool setCell(int row, int col, char mark);

    bool isFull() const;
    void reset();

    int rows() const { return rows_; }
    int cols() const { return cols_; }

private:
    int rows_;
    int cols_;
    std::vector<std::vector<char>> grid_;
};
