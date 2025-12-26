// game.h
#pragma once

#include "board.h"
#include "player.h"
#include <string>

class Game {
public:
	// Create a game with two player names, board size, and optional debug mode
	Game(const std::string& player1, const std::string& player2,
		 int rows = 4, int cols = 4, bool debugMode = false);

	// Run the main game loop; returns when the player chooses not to restart
	void run();

private:
	Board board_;
	Player p1_;
	Player p2_;
	Player* current_;

	bool debugMode_;

	void switchTurn();
	void showScores() const;
	bool promptPosition(int& outRow, int& outCol) const;
	int readInt() const;
};

//header for game class
