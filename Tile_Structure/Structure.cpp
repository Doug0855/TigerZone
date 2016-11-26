#include "Structure.h"

#include <string>

Structure::Structure(std::string type, std::pair<int,int> blockCoords) {
	this->type = type;
	this->startingBlock = blockCoords;
}

Structure::Structure(std::string type) {
	this->type = type;
}

Structure::Structure() {

}

Structure::~Structure() {

}