#include "TileStack.h"

TileStack::TileStack()
{
	for (int i = 1; i < 28; i++)
	{	
		Tile tile(i);
		if (i == 1 || i == 4 || i == 8 || i == 15 || i == 22 || i == 17 || i == 26)
			this->tiles.insert(1,tile);
		if (i == 3 || i == 14 || i == 16 || i == 18 || i == 19 || i == 20 || i == 23 || i == 25 || i == 27)
			this->tiles.insert(2,tile);
		if (i == 11 || i == 12 || i == 21 || i == 24)
			this->tiles.insert(3,tile);
		if (i == 2 || i == 7 || i == 9)
			this->tiles.insert(4,tile);
		if (i == 10 || i == 13)
			this->tiles.insert(5,tile);
		if (i == 5)
			this->tiles.insert(8,tile);
		if (i == 6)
			this->tiles.insert(9,tile);
	}
}

TileStack::~TileStack()
{
		
}
	
void TileStack::shuffle()
{
	std::random_shuffle(this->tiles.begin(), this->tiles.end());
}

Tile* TileStack::draw()
{
	Tile* tile = new Tile;
	return tile;
}

bool TileStack::isEmpty() {
	return true;
}
