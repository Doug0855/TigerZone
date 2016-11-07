#IFNDEF TILE_H
#DEFINE TILE_H

#include "Face.h"
#include <string>
#include "Block.h"

class Tile{
	Tile();
	~Tile();

	string to_string();
	void rotate(int rotations);
	bool hasOpenFace();
	bool shield;	
		
	Face getUpFace{ return up; }
	Face getDownFace{ return down; }
	Face getLeftFace{ return left; }
	Face getRightFace{ return right; }
	
private:
	Face up, down, left, right;
	Block center;
}

#ENDIF
