#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <string>
//#include "Meeple.h"

#define    Jungle    	'j'
#define    Lake      	'l'
#define    Trail     	't'
#define    Den	      'd'
#define	   Mixed      'm'

class Block {
public:
	// Instantiate a block from a character, character will define it's type to one of the types defined above
	Block(char c);
	Block();
	~Block();

	// Visting methods for within the block.
	bool isVisited() { return visited; }
	void visit() { visited = true; }
	void unVisit() { visited = false; }

	// Get and set type of block
	std::string getType() { return type; }
	void setType(char type);

	// Place a meeple in the block and check if it has one
	void placeMeeple();
	bool hasMeeple() { return meeple; }

private:
	bool meeple, visited;
	std::string type;

};

#endif
