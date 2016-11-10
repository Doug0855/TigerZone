#pragma once

#include <vector>
#include "Tile.h"
#include <string>

class Board {
private:
public:
	// Made m_board public to be able to access it in main.cpp
	std::vector< std::vector<Tile> > m_board;
	Board();
	~Board();
	std::string to_string(void);
	std::vector< std::pair<int, int> > display_positions(Tile* tile);
	void place_tile(std::pair<int, int> location, Tile& tile);
	std::vector< std::pair<int, int> > checkPlacement(Tile* tile, int i, int j, std::string location);
	std::pair<int, int> getOptimalPlacement(Tile* tile, std::vector< std::pair<int, int> > availableMoves);

};


