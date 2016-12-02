#ifndef TILESTACK_H
#define TILESTACK_H

#include "Tile.h"
#include <vector>
#include <algorithm>

class TileStack{
public:

	TileStack();
	TileStack(std::vector<int> tileVector);
	~TileStack();

	// shuffle the tilestack
	void shuffle();
	// draw from the top of the tile stack
	Tile draw();
	// ignore this
	bool isEmpty();

	std::vector<Tile> tiles;
};

#endif
