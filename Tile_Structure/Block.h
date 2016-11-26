#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <string>
//#include "Meeple.h"

#define    Jungle    	'j'
#define    Lake      	'l'
#define    Trail     	't'
#define    Den	      'd'
#define		 Mixed			'm'

class Block {
public:
	Block(char c);
	Block();
	~Block();

	std::string getType() { return this->type; }
	void setType(char type);
	void placeMeeple();
	bool hasMeeple() { return meeple; }
	void visit() { this->visited = true; }
	bool hasBeenVisited() { return visited; }


private:
	bool meeple, visited;
	std::string type;

};

#endif
