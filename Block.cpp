#include "Block.h"

Block::Block()
{
	
}

Block::~Block()
{
	
}
	
bool Block::closed()
{
	return false;
}

bool Block::connected()
{
	if(stuffconnected.size() == 0) return false;
	return true;
}

void Block::setType(std::string type){
	this->type = type;
}
