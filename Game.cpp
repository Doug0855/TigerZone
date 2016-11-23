#include "Game.h"
#include "Board.h"
#include <iostream>

// Pass in the gameId, both players, the tileStack, starting tile & it's coordinates to initialize a game (starting coords may be 0,0)?
Game::Game(std::string gameId, Player p1, Player p2, TileStack t, Tile startingTile, std::pair<int,int> startingCoordinates)
{
	Tile *startTile = new Tile(startingTile.getType());
	gameboard.place_tile(startingCoordinates, *startTile);

	player1 = p1;
	player2 = p2;
	gameId = gameId;
	tileStack = t;
}

Game::~Game()
{

}

void Game::play() {
	for(int i = 0; i <  1; i++) {
		Tile currentTile = tileStack.tiles[i];
		if(i % 2 == 0) {
			// player1 turn
			std::cout<<"It's your turn with tile of type "<<currentTile.getType()<<std::endl;
			std::vector<std::pair<int,int> > availableLocations = gameboard.display_positions(currentTile);
			std::cout<<"There are "<<availableLocations.size()<<" available locations for this tile"<<std::endl;
			for(int k = 0; k < availableLocations.size(); k++) {
				std::cout<<k<<") "<<availableLocations[k].first<<' '<<availableLocations[k].second<<std::endl;
			}

		} 
		else {
			// computer turn for solo play, player2 turn for tournament play
		}
	}
}

void Game::makeMove(Tile tile) {
	std::vector<std::pair<int,int> > availableLocations = gameboard.display_positions(tile);
	// check if there are any available moves. If so then place at the optimal spot.
	if(availableLocations.size() > 0) {
		Tile *tmpTile = new Tile(tile.getNum());
		std::pair<int,int> optimalLocation = gameboard.getOptimalPlacement(*tmpTile, availableLocations);
		gameboard.place_tile(optimalLocation, *tmpTile);
	}
	else {
		std::cout << "TILE " << tile.getType() << " CANNOT BE PLACED" << std::endl;
	}
}

// function to update the gameboard when input from an opponent move is received
void Game::updateBoard(){
	return;
}

// void Game::switchPlayer() {
// 	if (currentPlayer == &player1) {
// 		currentPlayer = &player2;
// 	} else {
// 		currentPlayer = &player1;
// 	}
// }
