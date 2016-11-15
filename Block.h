#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <string>
//#include "Meeple.h"

#define    Jungle    	'j'
#define    Lake      	'l'
#define    Trail     	't'
#define    Den	        'd'

class Block{
public:
	Block(char c);
	Block();
	~Block();
	
	bool closed(); ///< if it completes city/field/etc
	bool connected(); ///< if the block is connected to any other blocks returns false if not conncted
	std::string getType() { return type; }
	
private:
//	Meeple meeple;
	std::vector<Block*> ConnectedBlocks;
	std::string type;
};

#endif


