#ifndef TILE_H
#define TILE_H

#include "Block.h"
#include "Face.h"
#include <string>
#include <iostream>

class Tile{
public:
	Tile(int type);
	Tile();
	~Tile();

	// The four faces of the tile which will contain all the types
	Face up, down, left, right;
	// Attribute to tell us if the tile is a skeleton board tile or an initialized game tile
	bool hasInit;

	std::string to_string();
	
	// Rotate the tile and set all of the faces to the face that was -90 degrees of it.
	void rotate();
	
	// Function to check if a tile is connected on all 4 sides
	bool hasOpenFace();
	
	// Function to return a vector of all the open faces for a tile. Ex ["up","left"]
	std::vector<std::string> getOpenFaces();
	
	int getRotations(){ return rotation; }
	
	// Getters and setters for the tile type. USED ONLY FOR GUI
	void setType(char type) { this->type = type; }
	char getType() { return type; }

	// Connect each face of a tile to the other 3 faces within the tile. Used for mapping structures
	void connectInnerFaces();

	// Get the center of a block, lets us know if there is a den or a meeple
	Block getCenter() { return center; }

	// Checks for whether or not the tile has a prey animal
	bool hasBoar() {return boar; }
	bool hasBuffalo() {return buffalo; }
	bool hasDeer() { return deer; }



	// The number of times we've rotated the tile in order to make it placeable on the board
	int rotation = 0;
private:
	
	char type = '.';
	Block center;
	bool boar;
	bool buffalo;
	bool deer;
};

#endif
