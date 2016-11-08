#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Tile.h"
#include <string>

class Board {
private:
	std::vector<std::vector<Tile>> m_board;
public:
	Board();
	~Board();
	std::string to_string(void);
	std::vector<std::pair<int, int>> display_positions(Tile tile);
	void place_tile(std::pair<int, int> location, Tile tile);
	std::vector<std::pair<int, int>> checkPlacement(Tile* tile, int i, int j, std::string location);

};



#endif

