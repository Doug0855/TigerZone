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

	Face getUpFace(){ return up; }
	Face getDownFace(){ return down; }
	Face getLeftFace(){ return left; }
	Face getRightFace(){ return right; }
	Block getCenter() { return center; }
	bool hasBoar() {return boar; }
	bool hasBuffalo() {return buffalo; }
	bool hasDeer() { return deer; }

private:
	Face up, down, left, right;
	Block center;
	bool boar;
	bool buffalo;
	bool deer;
};

#endif
