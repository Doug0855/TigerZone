#include "Structure.h"

#include <string>

// init the structure
Structure::Structure(std::string type, std::pair<int,int> blockCoords) {
	this->type = type;
	this->startingBlock = blockCoords;
	this->boarCount = 0;
	this->deerCount = 0;
	this->buffaloCount = 0;
	this->crocodileCount = 0;
	this->hasMeeple = false;
}

Structure::Structure(std::string type) {
	this->type = type;
	this->boarCount = 0;
	this->deerCount = 0;
	this->buffaloCount = 0;
	this->crocodileCount = 0;
	this->hasMeeple = false;
}

Structure::Structure() {
	this->hasMeeple = false;
}

Structure::~Structure() {

}

// add animals to the structure as necessary according to the current tile
void Structure::checkAnimals(Tile *tile) {
	if(tile->hasCrocodile())
		this->crocodileCount++;
	if(tile->hasDeer())
		this->deerCount++;
	if(tile->hasBoar())
		this->boarCount++;
	if(tile->hasBuffalo())
		this->buffaloCount++;
}
