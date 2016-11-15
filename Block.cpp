#include "Block.h"

Block::Block(char c)
{
	if (c == Jungle)
		this->type = "jungle";
	else if (c == Lake)
		this->type = "lake";
	else if (c == Trail)
		this->type = "trail";
	else if (c == Den)
		this->type = "den";
	else
		this->type = "";
}

Block::Block()
{
	this->type = "";
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
	if(ConnectedBlocks.size() == 0) return false;
	return true;
}
