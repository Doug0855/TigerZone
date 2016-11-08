#include "Tile.h"

Tile::Tile()
{

}
Tile::~Tile()
{

}

std::string Tile::to_string()
{
	return "empty";
}

// Rotate a tile to the right by 90 degrees. (Ex: left face would now be top face, top face would be right, etc...)
void Tile::rotate()
{
	Face upFace = this->up;
	Face downFace = this->down;
	Face leftFace = this->left;
	Face rightFace = this->right;

	this->up = leftFace;
	this->right = upFace;
	this->down = rightFace;
	this->left = downFace;
	
	
}

bool Tile::hasOpenFace()
{
	if(!up.connected() || !down.connected() || !left.connected() || !right.connected()) return true;
	else return false;
}

// Method to obtain all the open faces of a tile. Check each face, if not connected then push to vector
std::vector<std::string> Tile::getOpenFaces()
{
	std::vector<std::string> openFaces;
	if(!up.connected())
		openFaces.push_back("up");
	if(!down.connected())
		openFaces.push_back("down");
	if(!left.connected())
		openFaces.push_back("left");
	if(!right.connected())
		openFaces.push_back("right");

	return openFaces;
}
