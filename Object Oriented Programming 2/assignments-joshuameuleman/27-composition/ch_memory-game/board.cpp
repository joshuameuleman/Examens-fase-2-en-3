// board.cpp
#include "board.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip>

Board::Board(int rows, int cols, bool debugMode)
	: rows_(rows), cols_(cols), debugMode_(debugMode), grid_(rows, std::vector<Card>(cols)) {
	init();
}

void Board::init() {
	// ensure even number of cells
	int cells = rows_ * cols_;
	if (cells % 2 != 0) {
		throw std::runtime_error("Board must have an even number of cells (pairs)");
	}

	std::vector<char> symbols = makeSymbols();

	// fill grid with symbols in row-major order then shuffle
	std::vector<Card> flat;
	flat.reserve(cells);
	for (char s : symbols) flat.emplace_back(s);

	// shuffle
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(flat.begin(), flat.end(), g);

	// move into grid
	auto it = flat.begin();
	for (int r = 0; r < rows_; ++r) {
		for (int c = 0; c < cols_; ++c) {
			grid_[r][c] = *it++;
		}
	}

	// if debug mode, reveal all
	if (debugMode_) {
		for (auto& row : grid_)
			for (auto& card : row)
				card.reveal();
	}
}

std::vector<char> Board::makeSymbols() const {
	int pairs = (rows_ * cols_) / 2;
	std::vector<char> symbols;
	symbols.reserve(pairs * 2);

	// use uppercase letters then lowercase letters then digits if needed
	std::string pool;
	for (char c = 'A'; c <= 'Z'; ++c) pool.push_back(c);
	for (char c = 'a'; c <= 'z'; ++c) pool.push_back(c);
	for (char c = '0'; c <= '9'; ++c) pool.push_back(c);

	if (pairs > static_cast<int>(pool.size()))
		throw std::runtime_error("Board too large for available symbols");

	for (int i = 0; i < pairs; ++i) {
		char s = pool[i];
		symbols.push_back(s);
		symbols.push_back(s);
	}
	return symbols;
}

void Board::display(std::ostream& os) const {
	// header (column numbers)
	os << "   ";
	for (int c = 1; c <= cols_; ++c) os << std::setw(3) << c;
	os << '\n';

	for (int r = 0; r < rows_; ++r) {
		// row number
		os << std::setw(2) << (r + 1) << ' ';
		for (int c = 0; c < cols_; ++c) {
			const Card& card = grid_[r][c];
			if (card.isRevealed() || card.isMatched() || debugMode_)
				os << ' ' << '[' << card.getSymbol() << ']';
			else
				os << ' ' << "[]";
		}
		os << '\n';
	}
}

bool Board::isValidPosition(int row, int col) const {
	return row >= 1 && row <= rows_ && col >= 1 && col <= cols_;
}

char Board::revealAt(int row, int col) {
	if (!isValidPosition(row, col)) return '\0';
	Card& card = grid_[row - 1][col - 1];
	card.reveal();
	return card.getSymbol();
}

void Board::hideAt(int row, int col) {
	if (!isValidPosition(row, col)) return;
	grid_[row - 1][col - 1].hide();
}

bool Board::isMatchedAt(int row, int col) const {
	if (!isValidPosition(row, col)) return false;
	return grid_[row - 1][col - 1].isMatched();
}

void Board::setMatchedAt(int row, int col, bool matched) {
	if (!isValidPosition(row, col)) return;
	grid_[row - 1][col - 1].setMatched(matched);
}

bool Board::allMatched() const {
	for (const auto& row : grid_)
		for (const auto& card : row)
			if (!card.isMatched()) return false;
	return true;
}

