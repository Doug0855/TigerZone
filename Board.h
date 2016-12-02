#ifndef BOARD_H
#define BOARD_H

#include "Tile_Structure/Tile.h"
#include "Tile_Structure/Structure.h"
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <queue>
#include <unordered_map>
#include <tuple>

class Board {
public:
	Board();
	~Board();

	// Made m_board public to be able to access it in main.cpp
	std::vector< std::vector<Tile*> > m_board;
	
	// Displays all possible location the tile can be placed on the board in any rotation
	std::vector< std::pair<int, int> > display_positions(Tile tile);
	
	// helper funtion for display_positions
	std::vector< std::pair<int, int> > checkPlacement(Tile tile, int i, int j, std::string location);
	
	// gets best placement and rotation for current tile
	std::pair<int, int> getOptimalPlacement(Tile &tile, std::vector< std::pair<int, int> > availableMoves);
	
	// Integer to hold posssible points if a meeple were to be placed at the i,j position within a block
	int positionPoints(int i, int j);

	// Points from an animal along a structure
	int animalPoints(int i, int j);

  void placeCroc(int i, int j);
  
	// places the tile on the board and connects the faces
	void place_tile(std::pair<int, int> location, Tile &tile);

	// Get a vector of the structures (and coordinates) within the tile where you may place a meeple
	// Pass in the coordinates of the recently placed tile to access it within the board
	std::vector<Structure> getStructures(int row, int col);
	
	// See if feature tile is being placed in has a meeple
	bool checkMeeplePlacement(Tile tile, std::pair<int, int> blockSpot);
	// Place a meeple at tile i,j in the block at pair location within the tile
	void placeMeeple(int i, int j, std::pair<int,int> location);
	// Give the AI the coordinates of our recently placed tile to analyze and determine which block to place 
	// a tiger in (if it may place one at all in the first plcae)
	void meepleAi(int i, int j);

private:

	// Helper functions for building the structures of a recently placed tile
	void buildLake(Structure* struc, Tile *tile, std::vector< std::vector<Block> >& tileBlocks, std::pair<int,int> blockSpot, std::vector<Tile*> &visitedTiles);
	void buildTrail(Structure* struc, Tile *tile, std::vector< std::vector<Block> >& tileBlocks, std::pair<int,int> blockSpot, std::vector<Tile*> &visitedTiles);
	void buildJungle(Structure* struc, Tile *tile, std::vector< std::vector<Block> >& tileBlocks, std::pair<int,int> blockSpot,  std::vector<Tile*> &visitedTiles);
	
	// Initial functions to start building a connected structure from the tile that was just placed
	Structure checkJungle(Tile *tile, std::vector< std::vector<Block> >& tileBlocks, std::pair<int, int> blockSpot);
	Structure checkLake(Tile *tile, std::vector< std::vector<Block> >& tileBlocks, std::pair<int, int> blockSpot);
	Structure checkTrail(Tile *tile, std::vector< std::vector<Block> >& tileBlocks, std::pair<int, int> blockSpot);

	void connectFaces(int row, int col);

};

#endif
