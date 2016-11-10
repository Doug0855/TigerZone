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
	currentPlayer = 0;
	tileStack.shuffle(); 
}

void Game::play() {
}