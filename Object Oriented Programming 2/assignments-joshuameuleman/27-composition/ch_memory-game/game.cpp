// game.cpp
#include "game.h"
#include <iostream>
#include <sstream> // for istringstream
#include <limits>
#include <string>

Game::Game(const std::string& player1, const std::string& player2,
           int rows, int cols, bool debugMode)
    : board_(rows, cols, debugMode), p1_(player1), p2_(player2), current_(&p1_), debugMode_(debugMode) {}

void Game::run() {
    bool keepPlaying = true;
    while (keepPlaying) {
        // reset board and players
        board_.init();
        p1_.resetScore();
        p2_.resetScore();
        current_ = &p1_;

        while (!board_.allMatched()) {
            std::cout << "\n*** Memory Game ***\n";
            showScores();
            board_.display(std::cout);

            std::cout << "\n" << current_->getName() << ", it's your turn!\n";

            int r1, c1;
            // first selection
            while (true) {
                std::cout << "Select your first card (row column): ";
                if (!promptPosition(r1, c1)) { std::cout << "Invalid input. Try again.\n"; continue; }
                if (!board_.isValidPosition(r1, c1)) { std::cout << "Position out of bounds. Try again.\n"; continue; }
                if (board_.isMatchedAt(r1, c1)) { std::cout << "Card already matched. Choose another.\n"; continue; }
                break;
            }

            char s1 = board_.revealAt(r1, c1);
            board_.display(std::cout);

            int r2, c2;
            // second selection
            while (true) {
                std::cout << "Select your second card (row column): ";
                if (!promptPosition(r2, c2)) { std::cout << "Invalid input. Try again.\n"; continue; }
                if (!board_.isValidPosition(r2, c2)) { std::cout << "Position out of bounds. Try again.\n"; continue; }
                if (board_.isMatchedAt(r2, c2)) { std::cout << "Card already matched. Choose another.\n"; continue; }
                if (r1 == r2 && c1 == c2) { std::cout << "You selected the same card twice. Choose a different card.\n"; continue; }
                break;
            }

            char s2 = board_.revealAt(r2, c2);
            board_.display(std::cout);

            if (s1 != '\0' && s1 == s2) {
                std::cout << "\nCongratulations " << current_->getName() << "! You found a pair!\n";
                board_.setMatchedAt(r1, c1, true);
                board_.setMatchedAt(r2, c2, true);
                current_->incrementScore();
                // same player gets another turn
            } else {
                std::cout << "\nSorry, the cards do not match.\n";
                // pause so the player sees the revealed cards
                std::cout << "Press Enter to continue...";
                std::string _pause;
                std::getline(std::cin, _pause);
                board_.hideAt(r1, c1);
                board_.hideAt(r2, c2);
                switchTurn();
            }
        }

        // Game over
        std::cout << "\n*** End of Game ***\nFinal Score:\n";
        showScores();
        if (p1_.getScore() > p2_.getScore())
            std::cout << "\nCongratulations " << p1_.getName() << "! You have won the game with " << p1_.getScore() << " pairs!\n";
        else if (p2_.getScore() > p1_.getScore())
            std::cout << "\nCongratulations " << p2_.getName() << "! You have won the game with " << p2_.getScore() << " pairs!\n";
        else
            std::cout << "\nIt's a tie! Well played both!\n";

        // ask to restart
        std::cout << "\nWould you like to play again? (y/n): ";
        std::string ans;
        std::getline(std::cin, ans);
        if (ans.empty()) std::getline(std::cin, ans);
        if (ans.size() > 0 && (ans[0] == 'y' || ans[0] == 'Y')) {
            keepPlaying = true;
        } else {
            keepPlaying = false;
        }
    }
}

void Game::switchTurn() {
    if (current_ == &p1_) current_ = &p2_;
    else current_ = &p1_;
}

void Game::showScores() const {
    std::cout << "Score:\n";
    std::cout << p1_.getName() << ": " << p1_.getScore() << " pairs\n";
    std::cout << p2_.getName() << ": " << p2_.getScore() << " pairs\n";
}

bool Game::promptPosition(int& outRow, int& outCol) const {
    // read two ints from a single line
    std::string line;
    if (!std::getline(std::cin, line)) return false;
    if (line.empty()) return false;
    std::istringstream iss(line);
    if (!(iss >> outRow >> outCol)) return false;
    return true;
}

int Game::readInt() const {
    int v = 0;
    std::cin >> v;
    // clear rest of line
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return v;
}

