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
  else
  	type = "";
}

Block::Block()
{
  type = "";
}

Block::~Block()
{

}
