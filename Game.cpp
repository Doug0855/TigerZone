#include "Game.h"
#include "Board.h"
#include "Adapter.h"
#include "Tile_Structure/Structure.h"
#include <fstream>
#include <iostream>

// Pass in the gameId, both players, the tileStack, starting tile & it's coordinates to initialize a game (starting coords may be 0,0)?
Game::Game(std::string gameId, Player p1, Player p2, TileStack t, Tile startingTile, std::pair<int,int> startingCoordinates)
{
	Tile *startTile = new Tile(startingTile.getNum());
	gameboard.place_tile(startingCoordinates, *startTile);

	numMeeples = 7;
	player1 = p1;
	player2 = p2;
	this->gameId = gameId;
	tileStack = t;
}

Game::~Game()
{

}

//debugging section for playing a game and testing ai not used by the server
void Game::play() {
	for(int i = 0; i <  tileStack.tiles.size(); i++) {
		Tile currentTile = tileStack.tiles[i];
		if(i % 2 == 0) {

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

//function for the other player making a move
void Game::enemyMove(Tile tile, int i, int j, int orientation, bool tiger, bool croc, std::pair<int,int> tigerSpot)
{
	//create a tile to place
  Tile *tmpTile = new Tile(tile.getNum());
  //set the proper orientation for the tile
  for(int k = 0; k< orientation; k++)
  {
    tmpTile->rotate();
  }
	std::pair<int, int> optimalLocation(i,j);
	//place the tile at the location specified 
  gameboard.place_tile(optimalLocation, *tmpTile);
  // if there is a tiger place it 
  if(tiger) gameboard.placeMeeple(i, j, tigerSpot);
  // if there is a croc place it
  if(croc) gameboard.placeCroc(i ,j);
}

// returns the move string for the server
std::string Game::makeMove(Tile tile, std::string moveNumber) {
  std::string placement;
  std::string tiger = " NONE";
  Adapter adapter;

	// get all location the tile can be placed at
	std::vector<std::pair<int,int> > availableLocations = gameboard.display_positions(tile);
	// check if there are any available moves. If so then place at the optimal spot.
	if(availableLocations.size() > 0) {
		Tile *tmpTile = new Tile(tile.getNum());
		// get best place out of the available location according to our ai
		std::pair<int, int> optimalLocation = gameboard.getOptimalPlacement(*tmpTile, availableLocations);
		//place the tile
		gameboard.place_tile(optimalLocation, *tmpTile);
		// if we have tiger run the tiger ai
		if(numMeeples > 0)
		{
			// try to place a tiger
		  	tiger = meepleAi(optimalLocation.first, optimalLocation.second);
			// if we placed a tiger subtract from the number of tigers we have
			if (tiger != " NONE") numMeeples--;
		}

		std::pair<int,int> convertCoordinates = adapter.convertCoordinates(optimalLocation);
		//debugging std::cout << "DEBUG: Optimal location first: " << optimalLocation.first << std::endl;
		//debugging std::cout << "DEBUG: Optimal location second: " << optimalLocation.second << std::endl;
		placement = "GAME " + gameId + " MOVE " + moveNumber + " PLACE " + adapter.tileToExpr(tmpTile->getNum()) +" AT " + std::to_string(convertCoordinates.first) + " " + std::to_string(convertCoordinates.second)  + " " + std::to_string(tmpTile->getRotations() * 90);

		return placement + tiger + "\r\n";
	}
	else {
		return "GAME " + gameId + " MOVE " + moveNumber + " TILE " + adapter.tileToExpr(tile.getNum()) +" UNPLACEABLE PASS\r\n";
	}

}

// Hueristic to have an ai that can place down meeples in correct spots and values some more than others
std::string Game::meepleAi(int i, int j)
{
  Adapter adapter;
  std::string tiger;
	// always place at a den if you can
	if (gameboard.m_board[i][j]->getCenter().getType() == "den")
	{
		gameboard.placeMeeple(i, j, std::pair<int,int> (1,1));
		tiger = " TIGER 5";
		return tiger;
	}
	// if there wasn't a den in the middle then get all the structures in the current tile
	std::vector<Structure> structures = gameboard.getStructures(i, j);
	// if you found structures
	if (structures.size() > 0)
	{
		int mostPoints = 0;
		int bestStruct = structures.size();
		// find the first structure that doesn't have a meeple
		for (size_t ii = 0; ii < structures.size(); ii++)
		{
			if (!structures[ii].hasMeeple)
			{
				bestStruct = ii;
				break;
			}
		}
		// for all the strucutres that don't have meeples count up the point values
		for (size_t ii = bestStruct; ii < structures.size(); ii++)
		{
			if (!structures[ii].hasMeeple)
			{
				int points = structurePoints(structures[ii]);
				// select the one with the highest point values
				if (points > mostPoints)
				{
					mostPoints = points;
					bestStruct = ii;
				}
			}
		}
		// as long as you found a stucutre without a meeple place the meele at the one with the highest points
		if (bestStruct != structures.size())
		{
		  gameboard.placeMeeple(i, j, structures[bestStruct].startingBlock);
		  std::string temp = std::to_string(adapter.convertZone(structures[bestStruct].startingBlock));
		  tiger = " TIGER " + temp;
		  return tiger;
		}
	}
	tiger = " NONE";
	return tiger;
}

// add points according to values for different kind of features
int Game::structurePoints(Structure structure)
{
	int points = 0;
	const int SIZE_POINTS = 1;
	const int JUNGLE_POINTS = 1;
	const int LAKE_POINTS = 3;
	const int TRAIL_POINTS = 2;
	const int PREY_POINTS = 1;
	const int CROC_POINTS = -2;
	/*
	This entire thing is just checking the type of the structure and anything 
	it has and adding points to a specific location to find the "best one"
	*/
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
