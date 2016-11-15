#pragma once

#include <vector>
#include "Tile.h"

class TileStack{
public:
		
	TileStack();
	~TileStack();
	
	void shuffle();
	Tile* draw();
	bool isEmpty();
	
	std::vector<Tile> tiles;
};

