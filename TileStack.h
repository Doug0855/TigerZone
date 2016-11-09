#pragma once

#include <vector>
#include "Tile.h"

class TileStack{
public:
		
	TileStack();
	~TileStack();
	
	void shuffle();
	Tile draw();
	
private:
	std::vector<Tile> tiles;
};

