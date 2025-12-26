// board.cpp - Tic-Tac-Toe board implementation
#include "board.h"
#include <iostream>
#include <iomanip>

Board::Board(int rows, int cols)
    : rows_(rows), cols_(cols), grid_(rows, std::vector<char>(cols, ' ')) {
}

void Board::init() {
    for (auto& row : grid_) for (auto& cell : row) cell = ' ';
}

void Board::reset() { init(); }

void Board::display(std::ostream& os) const {
    // header
    os << "   ";
    for (int c = 1; c <= cols_; ++c) os << std::setw(3) << c;
    os << '\n';

    for (int r = 0; r < rows_; ++r) {
        os << std::setw(2) << (r + 1) << ' ';
        for (int c = 0; c < cols_; ++c) {
            char ch = grid_[r][c];
            if (ch == ' ') os << ' ' << "[]"; else os << ' ' << '[' << ch << ']';
        }
        os << '\n';
    }
}

bool Board::isValidPosition(int row, int col) const {
    return row >= 1 && row <= rows_ && col >= 1 && col <= cols_;
}

char Board::getCell(int row, int col) const {
    if (!isValidPosition(row, col)) return '\0';
    return grid_[row-1][col-1];
}

bool Board::setCell(int row, int col, char mark) {
    if (!isValidPosition(row, col)) return false;
    char& cell = grid_[row-1][col-1];
    if (cell != ' ') return false;
    cell = mark;
    return true;
}

bool Board::isFull() const {
    for (const auto& row : grid_)
        for (char c : row) if (c == ' ') return false;
    return true;
}
