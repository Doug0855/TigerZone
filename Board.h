#pragma once

#include <vector>
#include "Tile.h"
#include <string>

class Board {
public:
	Board();
	~Board();

	// Displays all possible location the tile can be placed on the board in any rotation
	std::vector< std::pair<int, int> > display_positions(Tile tile);
	// helper funtion for display_positions 
	std::vector< std::pair<int, int> > checkPlacement(Tile tile, int i, int j, std::string location);
	// gets best placement and rotation for current tile
	std::pair<int, int> getOptimalPlacement(Tile& tile, std::vector< std::pair<int, int> > availableMoves);
	// places the tile on the board and connects the faces
	void place_tile(std::pair<int, int> location, Tile& tile);
	// Made m_board public to be able to access it in main.cpp
	std::vector< std::vector<Tile> > m_board;

private:

};


