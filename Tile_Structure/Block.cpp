#include "Block.h"

Block::Block(char c)
{
  if (c == Jungle)
  	type = "jungle";
  else if (c == Lake)
  	type = "lake";
  else if (c == Trail)
  	type = "trail";
  else if (c == Den)
	  type = "den";
  else if (c == Mixed)
	  type = "mixed";
  else
  	type = "";
  visited = false;
  meeple = false;
}

Block::Block()
{
	meeple = false;
  type = "";
}

Block::~Block()
{

}

void Block::setType(char c) {
  if (c == Jungle)
    type = "jungle";
  else if (c == Lake)
    type = "lake";
  else if (c == Trail)
    type = "trail";
  else if (c == Den)
    type = "den";
  else if (c == Mixed)
	  type = "mixed";
}

void Block::placeMeeple() {
  meeple = true;
}
