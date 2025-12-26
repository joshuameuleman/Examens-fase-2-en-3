// game.cpp
#include "game.h"
#include <iostream>
#include <sstream>

Game::Game(const std::string& player1, const std::string& player2, int size)
    : board_(size, size), p1_(player1.empty() ? "Player1" : player1), p2_(player2.empty() ? "Player2" : player2) {
    current_ = &p1_;
    currentMark_ = 'X';
}

void Game::run() {
    bool keepPlaying = true;
    while (keepPlaying) {
        board_.init();
        current_ = &p1_;
        currentMark_ = 'X';

        bool finished = false;
        while (!finished) {
            std::cout << "\n";
            board_.display(std::cout);
            std::cout << "\n" << current_->getName() << " (" << currentMark_ << ") - enter row and column: ";

            int r, c;
            if (!promptPosition(r, c)) {
                std::cout << "Invalid input. Please enter two numbers separated by space.\n";
                continue;
            }
            if (!board_.isValidPosition(r, c)) {
                std::cout << "Position out of bounds. Try again.\n";
                continue;
            }
            if (!board_.setCell(r, c, currentMark_)) {
                std::cout << "Cell already occupied. Choose another.\n";
                continue;
            }

            // show board
            board_.display(std::cout);

            // check win
            if (checkWin(currentMark_)) {
                std::cout << "\n" << current_->getName() << " wins!" << std::endl;
                current_->incrementScore();
                finished = true;
                break;
            }

            if (board_.isFull()) {
                std::cout << "\nIt's a draw!" << std::endl;
                finished = true;
                break;
            }

            // switch
            if (current_ == &p1_) { current_ = &p2_; currentMark_ = 'O'; }
            else { current_ = &p1_; currentMark_ = 'X'; }
        }

        // show scores
        std::cout << "\nScore:\n";
        std::cout << p1_.getName() << ": " << p1_.getScore() << "\n";
        std::cout << p2_.getName() << ": " << p2_.getScore() << "\n";

        std::cout << "Play again? (y/n): ";
        std::string ans;
        std::getline(std::cin, ans);
        if (ans.empty()) std::getline(std::cin, ans);
        if (!ans.empty() && (ans[0] == 'y' || ans[0] == 'Y')) keepPlaying = true; else keepPlaying = false;
    }
}

bool Game::promptPosition(int& outRow, int& outCol) const {
    std::string line;
    if (!std::getline(std::cin, line)) return false;
    if (line.empty()) return false;
    std::istringstream iss(line);
    if (!(iss >> outRow >> outCol)) return false;
    return true;
}

bool Game::checkWin(char mark) const {
    int n = board_.rows();
    // rows
    for (int r = 1; r <= n; ++r) {
        bool all = true;
        for (int c = 1; c <= n; ++c) {
            if (board_.getCell(r, c) != mark) { all = false; break; }
        }
        if (all) return true;
    }
    // cols
    for (int c = 1; c <= n; ++c) {
        bool all = true;
        for (int r = 1; r <= n; ++r) {
            if (board_.getCell(r, c) != mark) { all = false; break; }
        }
        if (all) return true;
    }
    // diag
    bool all = true;
    for (int i = 1; i <= n; ++i) if (board_.getCell(i, i) != mark) { all = false; break; }
    if (all) return true;
    all = true;
    for (int i = 1; i <= n; ++i) if (board_.getCell(i, n - i + 1) != mark) { all = false; break; }
    if (all) return true;
    return false;
}
