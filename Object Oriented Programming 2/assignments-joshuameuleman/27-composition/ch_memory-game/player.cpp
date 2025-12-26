// player.cpp
#include "player.h"

Player::Player(const std::string& name)
	: name_(name), score_(0) {}

const std::string& Player::getName() const { return name_; }
int Player::getScore() const { return score_; }
void Player::incrementScore() { ++score_; }
void Player::resetScore() { score_ = 0; }

std::ostream& operator<<(std::ostream& os, const Player& p) {
	os << p.getName() << ": " << p.getScore() << " pairs";
	return os;
}

