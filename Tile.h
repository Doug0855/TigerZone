#ifndef TILE_H
#define TILE_H

#include "Block.h"
#include "Face.h"
#include <string>

class Tile{
public:
	Tile(int type);
	Tile();
	~Tile();

	std::string to_string();
	void rotate();
	bool hasOpenFace();
	bool hasInit;
	std::vector<std::string> getOpenFaces();
	void setType(char type) { this->type = type; }

	int getRotations(){ return rotation; }
	char getType() { return type; }
	// Face getUpFace(){ return up; }
	// Face getDownFace(){ return down; }
	// Face getLeftFace(){ return left; }
	// Face getRightFace(){ return right; }
	Block getCenter() { return center; }
	bool hasBoar() {return boar; }
	bool hasBuffalo() {return buffalo; }
	bool hasDeer() { return deer; }

	Face up, down, left, right;
private:
	int rotation = 0;
	char type = '.';
	Block center;
	bool boar;
	bool buffalo;
	bool deer;
};

#endif
