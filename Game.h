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
	std::string makeMove(Tile);
	std::string meepleAi(int i, int j);
	void updateBoard();
	void printToTextFile(Board);
	
	Board gameboard;
private:
	int structurePoints(Structure structure);
	
  int numMeeples = 7;
	std::string gameId;
	Player player1;
	Player player2;
	TileStack tileStack;
	Tile* currentTile;
};

#endif
