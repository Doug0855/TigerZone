#pragma once

#include "Face.h"
#include <string>
#include "Block.h"

class Tile{
public:
	Tile();
	Tile(int tileType);
	~Tile();


	std::string to_string();
	void rotate();
	bool hasOpenFace();
	std::vector<std::string> getOpenFaces();

	// Boolean to tell us if the tile in the matrix hasn't been initialized to a real tile yet;
	bool hasInit;

	Face up, down, left, right;

	Face getUpFace(){ return up; }
	Face getDownFace(){ return down; }
	Face getLeftFace(){ return left; }
	Face getRightFace(){ return right; }

	void connectInnerFaces();
	
private:
	Block center;
	bool shield;
};

