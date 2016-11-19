#ifndef TILE_H
#define TILE_H

#include "Block.h"
#include "Face.h"
#include <string>
#include <iostream>

class Tile {
public:
	Tile(int type);
	Tile();
	~Tile();

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
	bool hasInit() { return initialization; }

  Face* getUpFace() { return &up; }
  Face* getDownFace() { return &down; }
  Face* getLeftFace() { return &left; }
  Face* getRightFace() { return &right; }
	// Get the center of a block, lets us know if there is a den or a meeple
	Block* getCenter() { return &center; }
	char getType() { return type; }
	int getNum() { return num; }
	int getRotations() { return rotation; }

private:
  // The number of times we've rotated the tile in order to make it placeable on the board
  int rotation, num;
	char type;
	bool boar, buffalo, deer;
  // Attribute to tell us if the tile is a skeleton board tile or an initialized game tile
  bool initialization;
  Block center;
  // The four faces of the tile which will contain all the types
  Face up, down, left, right;

};

#endif
