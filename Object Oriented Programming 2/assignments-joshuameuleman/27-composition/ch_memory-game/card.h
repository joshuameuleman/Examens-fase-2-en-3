// card.h
#pragma once

#include <iostream>

class Card {
public:
	explicit Card(char symbol = ' ');

	char getSymbol() const;
	bool isRevealed() const;
	bool isMatched() const;

	void reveal();
	void hide();
	void setMatched(bool matched = true);

private:
	char symbol_;
	bool revealed_;
	bool matched_;
};

std::ostream& operator<<(std::ostream& os, const Card& c);

