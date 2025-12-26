// board.h
#pragma once

#include "card.h"
#include <vector>
#include <iostream>

class Board {
public:
	// rows x cols board. Both should produce an even number of cells.
	Board(int rows = 4, int cols = 4, bool debugMode = false);

	// Initialize (shuffle pairs)
	void init();

	// Display board to the given stream
	void display(std::ostream& os = std::cout) const;

	// Public helpers use 1-based coordinates (row, col)
	bool isValidPosition(int row, int col) const; //help to check valid position

	// Reveal a card and return its symbol; returns '\0' on invalid pos
	char revealAt(int row, int col);
	void hideAt(int row, int col);

	bool isMatchedAt(int row, int col) const;
	void setMatchedAt(int row, int col, bool matched = true);

	bool allMatched() const;

	int rows() const { return rows_; }
	int cols() const { return cols_; }

private:
	int rows_;
	int cols_;
	bool debugMode_;
	std::vector<std::vector<Card>> grid_;

	// helper to produce symbol list for pairs
	std::vector<char> makeSymbols() const;
};

