#IFNDEF BOARD_H
#DEFINE BOARD_H

#include <vector>
#include "Tile.h"
#include <string>

class Board {
private:
	std::vector<std::vector<Tile>> board;
public:
	Board();
	~Board();
	string to_string(void);
	vector<int> display_positions(Tile);
	bool place_tile(int,Tile);
	
	
}



#ENDIF

