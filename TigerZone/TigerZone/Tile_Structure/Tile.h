#ifndef TILE_H
#define TILE_H

#include "Block.h"
#include "Face.h"
#include <string>
#include <iostream>

class Tile {
public:
	Tile(int num);
	Tile();
	~Tile();

	// Set a row of blocks for a tile
	void setRow(int row, char type1, char type2, char type3);

	// Rotate the tile and set all of the faces to the face that was -90 degrees of it.
	void rotate();
	// Function to check if a tile is connected on all 4 sides
	bool hasOpenFace();
	// Function to return a vector of all the open faces for a tile. Ex ["up","left"]
	std::vector<std::string> getOpenFaces();

	// Checks for whether or not the tile has a prey animal
	bool hasBoar() { return boar; }
	bool hasBuffalo() { return buffalo; }
	bool hasDeer() { return deer; }
	bool hasCrocodile() { return crocodile; }
	void setCrocodile() { this->crocodile = true; }
	bool hasInit() { return initialization; }

	// Get the type of a face
  	std::string getUpFaceType() { return up.getType(); }
  	std::string getDownFaceType() { return down.getType(); }
  	std::string getLeftFaceType() { return left.getType(); }
  	std::string getRightFaceType() { return right.getType(); }

  	// Get the faces
  	Face* getUpFace() { return &up; }
  	Face* getDownFace() { return &down; }
  	Face* getLeftFace() { return &left; }
  	Face* getRightFace() { return &right; }

	Block getCenter() { return innerBlocks[1][1]; }

  	// Set the types of the 4 faces after matrix has been initialized
  	void setFaceTypes();

  	// Variables for the GUI
	char getType() { return type; }
	int getNum() { return num; }
	int getRotations() { return rotation; }

private:
  	// The number of times we've rotated the tile in order to make it placeable on the board
  	int rotation, num;
	char type;
	bool boar, buffalo, deer, crocodile;
  	// Attribute to tell us if the tile is a skeleton board tile or an initialized game tile
  	bool initialization;
  	// The four faces of the tile which will contain all the types
  	Face up, down, left, right;
  	// 3x3 matrix of blocks in the tile
  	std::vector< std::vector<Block> > innerBlocks;

};

#endif
