#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <string>
//#include "Meeple.h"

#define    Jungle    	'j'
#define    Lake      	'l'
#define    Trail     	't'
#define    Den	      'd'

class Block {
public:
	Block(char c);
	Block();
	~Block();

	std::string getType() { return type; }

private:
	std::string type;
	
};

#endif
