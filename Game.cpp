#include "Game.h"

Game::Game(std::string gameId, TileStack t, Board b)
{
	// player1 = p1;
	// player2 = p2;
	gameId = gameId;
	tileStack = t;
	gameBoard = b;
}

Game::~Game()
{

}

void Game::init() {
	// currentPlayer = &player1;
	// tileStack.shuffle();
}

void Game::play() {
	while(!tileStack.isEmpty()) {
		
	}
}

// void Game::switchPlayer() {
// 	if (currentPlayer == &player1) {
// 		currentPlayer = &player2;
// 	} else {
// 		currentPlayer = &player1;
// 	}
// }
