#include "Game.h"

Game::Game(Player p1, Player p2, TileStack t, Board b)
{
	player1 = p1;
	player2 = p2;
	tileStack = t;
	gameBoard = b;
}

Game::~Game()
{
	
}

void Game::init() {
	currentPlayer = &player1;
	tileStack.shuffle(); 
}

void Game::play() {
	while(!tileStack.isEmpty()) {
		currentTile = tileStack.draw(); 
		//Player places tile
		//update player score
		Game::switchPlayer(); 
	}
}

void Game::switchPlayer() {
	if (currentPlayer == &player1) {
		currentPlayer = &player2;
	} else {
		currentPlayer = &player1; 
	}
}