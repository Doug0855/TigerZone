#ifndef TILE_H
#define TILE_H

#include "Face.h"
#include <string>
#include "Block.h"

class Tile{
public:
	Tile();
	~Tile();

	std::string to_string();
	void rotate();
	bool hasOpenFace();
	std::vector<std::string> getOpenFaces();
	Face up, down, left, right;
	bool hasInit = false;

	Face getUpFace(){ return up; }
	Face getDownFace(){ return down; }
	Face getLeftFace(){ return left; }
	Face getRightFace(){ return right; }
	
private:
	Block center;
	bool shield;
};

#endif