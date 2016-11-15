#pragma once

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
	bool hasInit;
	void setType(char type) { this->type = type; }
	Face up, down, left, right;

	int getRotations(){ return rotation; }
	char getType() { return type; }
	Face getUpFace(){ return up; }
	Face getDownFace(){ return down; }
	Face getLeftFace(){ return left; }
	Face getRightFace(){ return right; }
	
private:
	int rotation = 0;
	char type = '.';
	Block center;
	bool shield;
};

