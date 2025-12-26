// player.h
#pragma once

#include <string>
#include <iostream>

class Player {
public:
    // Construct a player with an optional name (score starts at 0)
    explicit Player(const std::string& name = ""); //explicit to prevent implicit conversions 

    // Accessors
    const std::string& getName() const;
    int getScore() const;

    // Modifiers
    void incrementScore();
    void resetScore();

private:
    std::string name_;
    int score_;
};

// Convenience printer
std::ostream& operator<<(std::ostream& os, const Player& p);





