#include "TileStack.h"

// init the tile stack to the proper number of each type of tile
TileStack::TileStack()
{
	for (int i = 1; i < 29; i++)
	{
		Tile tile(i);
		if (i == 1 || i == 4 || i == 8 || i == 15 || i == 22 || i == 17 || i == 21 || i == 26)
		{
			for(int k = 0; k < 1; k++) { tiles.push_back(tile); }
		}
		if (i == 3 || i == 14 || i == 16 || i == 18 || i == 19 || i == 20 || i == 23 || i == 25 || i == 27 || i == 28)
		{
			for(int k = 0; k < 2; k++) { tiles.push_back(tile); }
		}
		if (i == 11 || i == 12 || i == 24)
		{
			for(int k = 0; k < 3; k++) { tiles.push_back(tile); }
		}
		if (i == 2 || i == 7 || i == 9)
		{
			for(int k = 0; k < 4; k++) { tiles.push_back(tile); }
		}
		if (i == 10 || i == 13)
		{
			for(int k = 0; k < 5; k++) { tiles.push_back(tile); }
		}
		if (i == 5)
		{
			for(int k = 0; k < 8; k++) { tiles.push_back(tile); }
		}
		if (i == 6)
		{
			for(int k = 0; k < 9; k++) { tiles.push_back(tile); }
		}
	}
}

// init the tile stack based on a different tilestack
TileStack::TileStack(std::vector<int> tileVectors) {
	for(int i = 0; i < tileVectors.size(); i++) {
		Tile tile(i);
		tiles.push_back(i);
	}
}

TileStack::~TileStack()
{

}

// shuffle the tilestack
void TileStack::shuffle()
{
	std::random_shuffle(this->tiles.begin(), this->tiles.end());
}

// draw from the top of the tile stack
Tile TileStack::draw()
{
	Tile tile = tiles.front();
  	tiles.pop_back();
	return tile;
}

// ignore this
bool TileStack::isEmpty() {
	return true;
}
