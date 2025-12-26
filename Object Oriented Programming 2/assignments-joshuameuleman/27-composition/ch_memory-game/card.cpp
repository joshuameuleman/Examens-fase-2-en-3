// card.cpp
#include "card.h"

Card::Card(char symbol)
	: symbol_(symbol), revealed_(false), matched_(false) {}

char Card::getSymbol() const { return symbol_; }
bool Card::isRevealed() const { return revealed_; }
bool Card::isMatched() const { return matched_; }

void Card::reveal() { revealed_ = true; }
void Card::hide() { if(!matched_) revealed_ = false; }
void Card::setMatched(bool matched) { matched_ = matched; if(matched_) revealed_ = true; }

std::ostream& operator<<(std::ostream& os, const Card& c) {
	if (c.isRevealed() || c.isMatched())
		os << c.getSymbol();
	else
		os << ' ';
	return os;
}

