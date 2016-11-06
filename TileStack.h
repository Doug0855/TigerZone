#ifndef TILESTACK_H
#define TILESTACK_H

#include <vector>

class Tile;

class TileStack{
public:
		
	TileStack();
	~TileStack();
	
	void shuffle();
	Tile draw();
	
private:
	std::vector<Tile> tiles;
};

#endif
