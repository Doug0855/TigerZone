#pragma once
#include "Player.h"
#include "Board.h"
#include "TileStack.h"

class Game{
	
public:
	Game(Player p1, Player p2, TileStack t, Board b);
	~Game();
	void init(); 
	void play(); 
	void switchPlayer(); 
private:
	Board gameBoard; 
	Player player1, player2;
	Player* currentPlayer; 
	TileStack tileStack; 
	Tile* currentTile;
};


