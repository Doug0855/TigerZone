#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Board.h"
#include "Tile_Structure/TileStack.h"

class Game{

public:
	Game(std::string gameId, TileStack t, Board b);
	~Game();

	void init();
	void play();
	void switchPlayer();

private:
	std::string gameId;
	Board gameBoard;
	TileStack tileStack;
	Tile* currentTile;
};

#endif
