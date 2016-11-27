#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "Block.h"
#include "Tile.h"
#include <string>

class Structure {
public:
	Structure(std::string type, std::pair<int,int> blockCoords);
	Structure(std::string type);
	Structure();
	~Structure();

	void checkAnimals(Tile *tile);

	std::string type;

	// Get the lowest block coordinates within the recently placed tile where this structure begins
	std::pair<int,int> startingBlock;

	// Vector of the blocks that this structure is composed of (need to set all to unvisited after we compose structure)
	std::vector<Block> structureBlocks;
 
	// Keep variables to track the number of game animals as well as prey animals within each structure
	int boarCount;
	int deerCount;
	int buffaloCount;
	int crocodileCount;

	bool hasMeeple;

};

#endif