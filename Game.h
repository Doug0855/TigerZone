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
	void setID(std::string identification) { gameId = identification; }
	std::string getID() { return gameId; }
	void enemyMove(Tile tile, int i, int j, int orientation, bool tiger, bool croc, std::pair<int,int> tigerSpot);

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
