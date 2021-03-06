#include "TileStack.h"

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

TileStack::~TileStack()
{

}

void TileStack::shuffle()
{
	std::random_shuffle(this->tiles.begin(), this->tiles.end());
}

Tile TileStack::draw()
{
	Tile tile = tiles.front();
  	tiles.pop_back();
	return tile;
}

bool TileStack::isEmpty() {
	return true;
}
