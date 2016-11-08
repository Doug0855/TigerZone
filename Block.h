#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

#include "Meeple.h"

class Block{
public:
	Block();
	~Block();
	
	bool closed(); ///< if it completes city/field/etc
	bool connected(); ///< if the block is connected to any other blocks returns false if not conncted
	std::string getType() { return type; }
	
private:
	Meeple meeple;
	std::vector<Block*> stuffconnected;
	std::string type;
};

#endif