#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Board.h"
#include "Tile_Structure/TileStack.h"

class Game{

public:
	Game(std::string gameId, Player player1, Player player2, TileStack t,  Tile startingTile, std::pair<int,int> startingCoordinates);
	~Game();

	void play();
	void makeMove(Tile);
	void meepleAi(int i, int j);
	void updateBoard();
	void switchPlayer();
	void printToTextFile(Board);


	Board gameboard;
private:
	int structurePoints(Structure structure);

	std::string gameId;
	Player player1;
	Player player2;
	TileStack tileStack;
	Tile* currentTile;
};

#endif
