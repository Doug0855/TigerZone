#include "Game.h"
#include "Board.h"
#include "Tile_Structure/Structure.h"
#include <fstream>
#include <iostream>

// Pass in the gameId, both players, the tileStack, starting tile & it's coordinates to initialize a game (starting coords may be 0,0)?
Game::Game(std::string gameId, Player p1, Player p2, TileStack t, Tile startingTile, std::pair<int,int> startingCoordinates)
{
	Tile *startTile = new Tile(startingTile.getNum());
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
	for(int i = 0; i <  tileStack.tiles.size(); i++) {
		Tile currentTile = tileStack.tiles[i];
		if(i % 2 == 99) {
			// player1 turn
			std::cout<<"It's your turn with tile of type "<<currentTile.getType()<<std::endl;
			std::vector<std::pair<int,int> > availableLocations = gameboard.display_positions(currentTile);
			std::cout<<"There are "<<availableLocations.size()<<" available locations for this tile"<<std::endl;
			for(int k = 0; k < availableLocations.size(); k++) {
				std::cout<<k<<") "<<availableLocations[k].first<<' '<<availableLocations[k].second<<std::endl;
			}
			// Take in where the user would like to place the tile
			int placementSelection;
			std::cin >> placementSelection;
			std::cout<<"Select option "<<placementSelection<<std::endl;
			// Create vector of that pair to pass to optimalLocation(), need to keep as param vector bc this is specific scenario where we know exact coordinates
			std::vector< std::pair<int,int> > placementLocation;
			placementLocation.push_back(availableLocations[placementSelection]);
			// Create a new pointer to a new tile of the same type as the currentTile
			Tile *tmpTile = new Tile(currentTile.getNum());
			// Properly rotate the tile so it may be placed
			std::pair<int, int> optimalLocation = gameboard.getOptimalPlacement(*tmpTile, placementLocation);
			// Place the new tile
			gameboard.place_tile(optimalLocation, *tmpTile);

			// printToTextFile(gameboard);
			std::cout<<std::endl;
		} 
		else {
			std::cout<<"COMPUTER TURN"<<std::endl;
			// computer turn for solo play, player2 turn for tournament play
			std::vector<std::pair<int,int> > availableLocations = gameboard.display_positions(currentTile);
			Tile *tmpTile = new Tile(currentTile.getNum());
			if(availableLocations.size() > 0) {
				std::pair<int, int> optimalLocation = gameboard.getOptimalPlacement(*tmpTile, availableLocations);
				gameboard.place_tile(optimalLocation, *tmpTile);
				std::cout<<"Computer placed tile of type "<<currentTile.getType()<<" at location "<<optimalLocation.first<<' '<<optimalLocation.second<<std::endl;
			}
			else {
				// Need to implement the 3 functions for unplayable tiles
				std::cout<<"Unplayable tile. You may PASS, PICK UP A TIGER, OR PLACE A TIGER"<<std::endl;
			}

			// printToTextFile(gameboard);
		}
	}
	printToTextFile(gameboard);
}

void Game::makeMove(Tile tile) {
	std::vector<std::pair<int,int> > availableLocations = gameboard.display_positions(tile);
	// check if there are any available moves. If so then place at the optimal spot.
	if(availableLocations.size() > 0) {
		Tile *tmpTile = new Tile(tile.getNum());
		std::pair<int, int> optimalLocation = gameboard.getOptimalPlacement(*tmpTile, availableLocations);
		gameboard.place_tile(optimalLocation, *tmpTile);
	}
	else {
		std::cout << "TILE " << tile.getType() << " CANNOT BE PLACED" << std::endl;
	}
}

void Game::meepleAi(int i, int j)
{
	if (gameboard.m_board[i][j]->getCenter().getType() == "den")
	{
		gameboard.placeMeeple(i, j, std::pair<int,int> (1,1));
		return;
	}
	std::vector<Structure> structures = gameboard.getStructures(i, j);
	if (structures.size() > 0 && !structures[0].hasMeeple)
	{
		int mostPoints = 0;
		int bestStruct = 0;
		for (size_t ii = 0; ii < structures.size(); ii++)
		{
			if (!structures[ii].hasMeeple)
			{
				int points = structurePoints(structures[ii]);
				if (points > mostPoints)
				{
					mostPoints = points;
					bestStruct = ii;
				}
			}
		}
		gameboard.placeMeeple(i, j, structures[bestStruct].startingBlock);
	}
}

int Game::structurePoints(Structure structure)
{
	int points = 0;
	const int SIZE_POINTS = 1;
	const int JUNGLE_POINTS = 3;
	const int LAKE_POINTS = 2;
	const int TRAIL_POINTS = 1;
	const int PREY_POINTS = 1;
	const int CROC_POINTS = -2;
	
	for (size_t i = 0; i < structure.structureBlocks.size(); i++)
	{
		points += SIZE_POINTS;
	}
	if (structure.type == "jungle")
	{
		points += JUNGLE_POINTS;
	}
	if (structure.type == "lake")
	{
		points += LAKE_POINTS;
	}
	if (structure.type == "trail")
	{
		points += TRAIL_POINTS;
	}
	for (int i = 0; i < structure.boarCount; i++)
	{
		points += PREY_POINTS;
	}
	for (int i = 0; i < structure.deerCount; i++)
	{
		points += PREY_POINTS;
	}
	for (int i = 0; i < structure.buffaloCount; i++)
	{
		points += PREY_POINTS;
	}
	for (int i = 0; i < structure.crocodileCount; i++)
	{
		points += CROC_POINTS;
	}
}

// function to update the gameboard when input from an opponent move is received
void Game::updateBoard(){
	return;
}

// Print to the GUI text file after each move so we can see if the game works
void Game::printToTextFile(Board gameboard)
{
	std::ofstream out_data("Levels/level.txt");
	out_data << "Level:" << std::endl;
	for (auto& inner : gameboard.m_board)
	{
		for (auto& item : inner)
		{
			if (item != NULL)
				out_data << item->getRotations() << item->getType();
			else
				out_data << '0' << '.';
			
		}
		out_data << std::endl;
	}
	out_data.close();
}

// void Game::switchPlayer() {
// 	if (currentPlayer == &player1) {
// 		currentPlayer = &player2;
// 	} else {
// 		currentPlayer = &player1;
// 	}
// }
