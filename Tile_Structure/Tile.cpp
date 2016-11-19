#include "Tile.h"

// Constructor to create one of the 27 different tiles
Tile::Tile(int type)
{
  Face *NULL_face = NULL;
  if (type == 1)
  {
    up = Face('j', 'j', 'j', down, right, left);
    down = Face('j', 'j', 'j', up, left, right);
    left = Face('j', 'j', 'j', right, up, down);
    right = Face('j', 'j', 'j', left, down, up);
    center = Block();
    rotation = 0;
    num = 1;
    boar = false;
    buffalo = false;
    deer = false;
    this->type = 'a';
    initialization = true;
  }
  else if (type == 2)
  {
    up = Face('j', 'j', 'j', down, right, left);
    down = Face('j', 'j', 'j', up, left, right);
    left = Face('j', 'j', 'j', right, up, down);
    right = Face('j', 'j', 'j', left, down, up);
    center = Block('d');
    rotation = 0;
    num = 2;
    boar = false;
    buffalo = false;
    deer = false;
    this->type = 'b';
    initialization = true;
  }
  else if (type == 3)
  {
    up = Face('j', 'j', 'j', *NULL_face, right, left);
    down = Face('j', 't', 'j', *NULL_face, *NULL_face, *NULL_face);
    left = Face('j', 'j', 'j', right, up, *NULL_face);
    right = Face('j', 'j', 'j', left, *NULL_face, up);
    center = Block('d');
    rotation = 0;
    num = 3;
    boar = false;
    buffalo = false;
    deer = false;
    this->type = 'c';
    initialization = true;
  }
  else if (type == 4)
  {
    up = Face('j', 't', 'j', *NULL_face, *NULL_face, *NULL_face);
    down = Face('j', 't', 'j', *NULL_face, *NULL_face, *NULL_face);
    left = Face('j', 't', 'j', *NULL_face, *NULL_face, *NULL_face);
    right = Face('j', 't', 'j', *NULL_face, *NULL_face, *NULL_face);
    center = Block();
    rotation = 0;
    num = 4;
    boar = false;
    buffalo = false;
    deer = false;
    this->type = 'd';
    initialization = true;
  }
  else if (type == 5)
  {
    up = Face('j', 't', 'j', this->down, *NULL_face, *NULL_face);
    down = Face('j', 't', 'j', this->up, *NULL_face, *NULL_face);
    left = Face('j', 'j', 'j', *NULL_face, *NULL_face, *NULL_face);
    right = Face('j', 'j', 'j', *NULL_face, *NULL_face, *NULL_face);
    center = Block();
    rotation = 0;
    num = 5;
    boar = false;
    buffalo = false;
    deer = false;
    this->type = 'e';
    initialization = true;
  }
  else if (type == 6)
  {
    up = Face('j', 't', 'j', *NULL_face, *NULL_face, left);
    down = Face('j', 'j', 'j', *NULL_face, *NULL_face, right);
    left = Face('j', 't', 'j', *NULL_face, up, *NULL_face);
    right = Face('j', 'j', 'j', *NULL_face, down, *NULL_face);
    center = Block();
    rotation = 0;
    num = 6;
    boar = false;
    buffalo = false;
    deer = false;
    this->type = 'f';
    initialization = true;
  }
  else if (type == 7)
  {
    up = Face('j', 't', 'j', *NULL_face, *NULL_face, *NULL_face);
    down = Face('j', 't', 'j', *NULL_face, *NULL_face, *NULL_face);
    left = Face('j', 't', 'j', *NULL_face, *NULL_face, *NULL_face);
    right = Face('j', 'j', 'j', *NULL_face, *NULL_face, *NULL_face);
    center = Block();
    rotation = 0;
    num = 7;
    boar = false;
    buffalo = false;
    deer = false;
    this->type = 'g';
    initialization = true;
  }
  else if (type == 8)
  {
    up = Face('l', 'l', 'l', down, right, left);
    down = Face('l', 'l', 'l', up, left, right);
    left = Face('l', 'l', 'l', right, up, down);
    right = Face('l', 'l', 'l', left, down, up);
    center = Block();
    rotation = 0;
    num = 8;
    boar = false;
    buffalo = false;
    deer = false;
    this->type = 'h';
    initialization = true;
  }
  else if (type == 9)
  {
    up = Face('j', 'j', 'j', *NULL_face, *NULL_face, *NULL_face);
    down = Face('l', 'l', 'l', *NULL_face, left, right);
    left = Face('l', 'l', 'l', right, *NULL_face, down);
    right = Face('l', 'l', 'l', left, down, *NULL_face);
    center = Block();
    rotation = 0;
    num = 9;
    boar = false;
    buffalo = false;
    deer = false;
    this->type = 'i';
    initialization = true;
  }
  else if (type == 10)
  {
    up = Face('l', 'l', 'l', *NULL_face, right, *NULL_face);
    down = Face('j', 'j', 'j', *NULL_face, left, *NULL_face);
    left = Face('j', 'j', 'j', *NULL_face, *NULL_face, down);
    right = Face('l', 'l', 'l', *NULL_face, *NULL_face, up);
    center = Block();
    rotation = 0;
    num = 10;
    boar = false;
    buffalo = false;
    deer = false;
    this->type = 'j';
    initialization = true;
  }
  else if (type == 11)
  {
    up = Face('j', 'j', 'j', *NULL_face, *NULL_face, *NULL_face);
    down = Face('j', 'j', 'j', *NULL_face, *NULL_face, *NULL_face);
    left = Face('l', 'l', 'l', right, *NULL_face, *NULL_face);
    right = Face('l', 'l', 'l', left, *NULL_face, *NULL_face);
    center = Block();
    rotation = 0;
    num = 11;
    boar = false;
    buffalo = false;
    deer = false;
    this->type = 'k';
    initialization = true;
  }
  else if (type == 12)
  {
    up = Face('l', 'l', 'l', *NULL_face, *NULL_face, *NULL_face);
    down = Face('l', 'l', 'l', *NULL_face, *NULL_face, *NULL_face);
    left = Face('j', 'j', 'j', right, *NULL_face, *NULL_face);
    right = Face('j', 'j', 'j', left, *NULL_face, *NULL_face);
    center = Block();
    rotation = 0;
    num = 12;
    boar = false;
    buffalo = false;
    deer = false;
    this->type = 'l';
    initialization = true;
  }
  else if (type == 13)
  {
    up = Face('l', 'l', 'l', *NULL_face, *NULL_face, *NULL_face);
    down = Face('j', 'j', 'j', *NULL_face, left, right);
    left = Face('j', 'j', 'j', right, *NULL_face, down);
    right = Face('j', 'j', 'j', left, down, *NULL_face);
    center = Block();
    rotation = 0;
    num = 13;
    boar = false;
    buffalo = false;
    deer = false;
    this->type = 'm';
    initialization = true;
  }
  else if (type == 14)
  {
    up = Face('j', 'j', 'j', *NULL_face, *NULL_face, left);
    down = Face('l', 'l', 'l', *NULL_face, *NULL_face, right);
    left = Face('j', 'j', 'j', *NULL_face, up, *NULL_face);
    right = Face('l', 'l', 'l', *NULL_face, down, *NULL_face);
    center = Block();
    rotation = 0;
    num = 14;
    boar = false;
    buffalo = false;
    deer = false;
    this->type = 'n';
    initialization = true;
  }
  else if (type == 15)
  {
    up = Face('j', 't', 'j', *NULL_face, *NULL_face, left);
    down = Face('j', 'j', 'j', *NULL_face, *NULL_face, *NULL_face);
    left = Face('j', 't', 'j', *NULL_face, up, *NULL_face);
    right = Face('l', 'l', 'l', *NULL_face, *NULL_face, *NULL_face);
    center = Block();
    rotation = 0;
    num = 15;
    boar = false;
    buffalo = false;
    deer = false;
    this->type = 'o';
    initialization = true;
  }
  else if (type == 16)
  {
    up = Face('j', 't', 'j', *NULL_face, *NULL_face, left);
    down = Face('j', 'j', 'j', *NULL_face, *NULL_face, *NULL_face);
    left = Face('j', 't', 'j', *NULL_face, up, *NULL_face);
    right = Face('l', 'l', 'l', *NULL_face, *NULL_face, *NULL_face);
    center = Block();
    rotation = 0;
    num = 16;
    boar = true;
    buffalo = false;
    deer = false;
    this->type = 'p';
    initialization = true;
  }
  else if (type == 17)
  {
    up = Face('j', 'j', 'j', *NULL_face, *NULL_face, *NULL_face);
    down = Face('j', 't', 'j', *NULL_face, left, *NULL_face);
    left = Face('j', 't', 'j', *NULL_face, *NULL_face, down);
    right = Face('l', 'l', 'l', *NULL_face, *NULL_face, *NULL_face);
    center = Block();
    rotation = 0;
    num = 17;
    boar = false;
    buffalo = false;
    deer = false;
    this->type = 'q';
    initialization = true;
  }
  else if (type == 18)
  {
    up = Face('j', 'j', 'j', *NULL_face, *NULL_face, *NULL_face);
    down = Face('j', 't', 'j', *NULL_face, left, *NULL_face);
    left = Face('j', 't', 'j', *NULL_face, *NULL_face, down);
    right = Face('l', 'l', 'l', *NULL_face, *NULL_face, *NULL_face);
    center = Block();
    rotation = 0;
    num = 18;
    boar = false;
    buffalo = true;
    deer = false;
    this->type = 'r';
    initialization = true;
  }
  else if (type == 19)
  {
    up = Face('j', 't', 'j', down, *NULL_face, *NULL_face);
    down = Face('j', 't', 'j', up, *NULL_face, *NULL_face);
    left = Face('j', 'j', 'j', *NULL_face, *NULL_face, *NULL_face);
    right = Face('l', 'l', 'l', *NULL_face, *NULL_face, *NULL_face);
    center = Block();
    rotation = 0;
    num = 19;
    boar = false;
    buffalo = false;
    deer = false;
    this->type = 's';
    initialization = true;
  }
  else if (type == 20)
  {
    up = Face('j', 't', 'j', down, *NULL_face, *NULL_face);
    down = Face('j', 't', 'j', up, *NULL_face, *NULL_face);
    left = Face('j', 'j', 'j', *NULL_face, *NULL_face, *NULL_face);
    right = Face('l', 'l', 'l', *NULL_face, *NULL_face, *NULL_face);
    center = Block();
    rotation = 0;
    num = 20;
    boar = false;
    buffalo = false;
    deer = true;
    this->type = 't';
    initialization = true;
  }
  else if (type == 21)
  {
    up = Face('j', 't', 'j', *NULL_face, *NULL_face, *NULL_face);
    down = Face('l', 'l', 'l', *NULL_face, left, right);
    left = Face('l', 'l', 'l', right, *NULL_face, down);
    right = Face('l', 'l', 'l', left, down, *NULL_face);
    center = Block();
    rotation = 0;
    num = 21;
    boar = false;
    buffalo = false;
    deer = false;
    this->type = 'u';
    initialization = true;
  }
  else if (type == 22)
  {
    up = Face('j', 't', 'j', *NULL_face, *NULL_face, *NULL_face);
    down = Face('j', 't', 'j', *NULL_face, *NULL_face, *NULL_face);
    left = Face('j', 't', 'j', *NULL_face, *NULL_face, *NULL_face);
    right = Face('l', 'l', 'l', *NULL_face, *NULL_face, *NULL_face);
    center = Block();
    rotation = 0;
    num = 22;
    boar = false;
    buffalo = false;
    deer = false;
    this->type = 'v';
    initialization = true;
  }
  else if (type == 23)
  {
    up = Face('j', 't', 'j', *NULL_face, *NULL_face, *NULL_face);
    down = Face('j', 't', 'j', *NULL_face, *NULL_face, *NULL_face);
    left = Face('j', 't', 'j', *NULL_face, *NULL_face, *NULL_face);
    right = Face('l', 'l', 'l', *NULL_face, *NULL_face, *NULL_face);
    center = Block();
    rotation = 0;
    num = 23;
    boar = true;
    buffalo = false;
    deer = false;
    this->type = 'w';
    initialization = true;
  }
  else if (type == 24)
  {
    up = Face('j', 't', 'j', *NULL_face, *NULL_face, left);
    down = Face('l', 'l', 'l', *NULL_face, *NULL_face, right);
    left = Face('j', 't', 'j', *NULL_face, up, *NULL_face);
    right = Face('l', 'l', 'l', *NULL_face, down, *NULL_face);
    center = Block();
    rotation = 0;
    num = 24;
    boar = false;
    buffalo = false;
    deer = false;
    this->type = 'x';
    initialization = true;
  }
  else if (type == 25)
  {
    up = Face('j', 't', 'j', *NULL_face, *NULL_face, left);
    down = Face('l', 'l', 'l', *NULL_face, *NULL_face, right);
    left = Face('j', 't', 'j', *NULL_face, up, *NULL_face);
    right = Face('l', 'l', 'l', *NULL_face, down, *NULL_face);
    center = Block();
    rotation = 0;
    num = 25;
    boar = false;
    buffalo = true;
    deer = false;
    this->type = 'y';
    initialization = true;
  }
  else if (type == 26)
  {
    up = Face('l', 'l', 'l', *NULL_face, *NULL_face, *NULL_face);
    down = Face('j', 't', 'j', *NULL_face, *NULL_face, *NULL_face);
    left = Face('j', 'j', 'j', *NULL_face, *NULL_face, *NULL_face);
    right = Face('j', 'j', 'j', *NULL_face, *NULL_face, *NULL_face);
    center = Block();
    rotation = 0;
    num = 26;
    boar = false;
    buffalo = false;
    deer = false;
    this->type = 'z';
    initialization = true;
  }
  else if (type == 27)
  {
    up = Face('l', 'l', 'l', *NULL_face, *NULL_face, *NULL_face);
    down = Face('j', 't', 'j', *NULL_face, *NULL_face, *NULL_face);
    left = Face('j', 'j', 'j', *NULL_face, *NULL_face, *NULL_face);
    right = Face('j', 'j', 'j', *NULL_face, *NULL_face, *NULL_face);
    center = Block();
    rotation = 0;
    num = 27;
    boar = false;
    buffalo = false;
    deer = true;
    this->type = '#';
    initialization = true;
  }
  else
  {
    up = Face();
    down = Face();
    left = Face();
    right = Face();
    center = Block();
    rotation = 0;
    num = 0;
    boar = false;
    buffalo = false;
    deer = false;
    type = '.';
    initialization = false;
  }
}
Tile::Tile()
{
  up = Face();
  down = Face();
  left = Face();
  right = Face();
  center = Block();
  rotation = 0;
  num = 0;
  boar = false;
  buffalo = false;
  deer = false;
  type = '.';
	initialization = false;
}
Tile::~Tile()
{

}
// Rotate a tile to the right by 90 degrees. (Ex: left face would now be top face, top face would be right, etc...)
void Tile::rotate()
{
	Face upFace = up;
	Face downFace = down;
	Face leftFace = left;
	Face rightFace = right;

	up = rightFace;
	right = downFace;
	down = leftFace;
	left = upFace;

  if (rotation < 3)
    rotation++;
  else
    rotation = 0;
}
// Method to check if tile has any open face (up, down, left, right)
bool Tile::hasOpenFace()
{
	if(!up.connected() || !down.connected() || !left.connected() || !right.connected()) return true;
	else return false;
}
// Method to obtain all the open faces of a tile. Check each face, if not connected then push to vector
std::vector<std::string> Tile::getOpenFaces()
{
	std::vector<std::string> openFaces;
	if(!up.connected())
		openFaces.push_back("up");
	if(!down.connected())
		openFaces.push_back("down");
	if(!left.connected())
		openFaces.push_back("left");
	if(!right.connected())
		openFaces.push_back("right");
	return openFaces;
}
