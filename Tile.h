#IFNDEF TILE_H
#DEFINE TILE_H

#include "Face.h"
#include <string>
#include "Block.h"

class Tile{
	Tile();
	~Tile();
	
	Face up, down, left, right;
	string to_string();
	void rotate(int rotations);
	bool shield;
	Block center;
		
	
	
}

#ENDIF