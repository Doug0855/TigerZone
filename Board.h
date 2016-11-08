#IFNDEF BOARD_H
#DEFINE BOARD_H

#include <vector>
#include "Tile.h"
#include <string>

class Board {
private:
	std::vector<std::vector<Tile>> m_board;
public:
	Board();
	~Board();
	string to_string(void);
	vector<int> display_positions(Tile tile);
	void place_tile(int location, Tile tile);
	vector<int> checkPlacement(Tile tile, int i, int j, std::string location);
	
}



#ENDIF

