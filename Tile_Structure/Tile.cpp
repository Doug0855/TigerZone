#include "Tile.h"

// Constructor to create one of the 27 different tiles
Tile::Tile(int type)
{
  // Initialize the tile's block matrix to null blocks
  for(int i = 0; i < 3; i++) {
    innerBlocks.push_back(std::vector<Block>(3));
  }
  Face *NULL_face = NULL;
  if (type == 1)
  {
    setRow(0,'j','j','j');
    setRow(1,'j','j','j');
    setRow(2,'j','j','j');
    setFaceTypes();
    rotation = 0;
    num = 1;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 'a';
    initialization = true;
  }
  else if (type == 2)
  {
    setRow(0,'j','j','j');
    setRow(1,'j','d','j');
    setRow(2,'j','j','j');
    setFaceTypes();
    rotation = 0;
    num = 2;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 'b';
    initialization = true;
  }
  else if (type == 3)
  {
    setRow(0,'j','j','j');
    setRow(1,'j','d','j');
    setRow(2,'j','t','j');
    setFaceTypes();
    rotation = 0;
    num = 3;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 'c';
    initialization = true;
  }
  else if (type == 4)
  {
    setRow(0,'j','t','j');
    setRow(1,'t','t','t');
    setRow(2,'j','t','j');
    setFaceTypes();
    rotation = 0;
    num = 4;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 'd';
    initialization = true;
  }
  else if (type == 5)
  {
    setRow(0,'j','t','j');
    setRow(1,'j','t','j');
    setRow(2,'j','t','j');
    setFaceTypes();
    rotation = 0;
    num = 5;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 'e';
    initialization = true;
  }
  else if (type == 6)
  {
    setRow(0,'j','t','j');
    setRow(1,'t','t','j');
    setRow(2,'j','j','j');
    setFaceTypes();
    rotation = 0;
    num = 6;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 'f';
    initialization = true;
  }
  else if (type == 7)
  {
   setRow(0,'j','t','j');
    setRow(1,'t','t','j');
    setRow(2,'j','t','j');
    setFaceTypes();
    rotation = 0;
    num = 7;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 'g';
    initialization = true;
  }
  else if (type == 8)
  {
    setRow(0,'l','l','l');
    setRow(1,'l','l','l');
    setRow(2,'l','l','l');
    setFaceTypes();
    rotation = 0;
    num = 8;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 'h';
    initialization = true;
  }
  else if (type == 9)
  {
    setRow(0,'m','j','m');
    setRow(1,'l','j','l');
    setRow(2,'l','l','l');
    setFaceTypes();
    rotation = 0;
    num = 9;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 'i';
    initialization = true;
  }
  else if (type == 10)
  {
    setRow(0,'m','l','l');
    setRow(1,'j','j','l');
    setRow(2,'j','j','m');
    setFaceTypes();
    rotation = 0;
    num = 10;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 'j';
    initialization = true;
  }
  else if (type == 11)
  {
    setRow(0,'m','j','m');
    setRow(1,'l','l','l');
    setRow(2,'m','j','m');
    setFaceTypes();
    rotation = 0;
    num = 11;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 'k';
    initialization = true;
  }
  else if (type == 12)
  {
    setRow(0,'m','l','m');
    setRow(1,'j','j','j');
    setRow(2,'m','l','m');
    setFaceTypes();
    rotation = 0;
    num = 12;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 'l';
    initialization = true;
  }
  else if (type == 13)
  {
    setRow(0,'m','l','m');
    setRow(1,'j','j','j');
    setRow(2,'j','j','j');
    setFaceTypes();
    rotation = 0;
    num = 13;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 'm';
    initialization = true;
  }
  else if (type == 14)
  {
    setRow(0,'j','j','m');
    setRow(1,'j','j','l');
    setRow(2,'m','l','m');
    setFaceTypes();
    rotation = 0;
    num = 14;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 'n';
    initialization = true;
  }
  else if (type == 15)
  {
    setRow(0,'j','t','m');
    setRow(1,'t','t','l');
    setRow(2,'j','j','m');
    setFaceTypes();
    rotation = 0;
    num = 15;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 'o';
    initialization = true;
  }
  else if (type == 16)
  {
    setRow(0,'j','t','m');
    setRow(1,'t','t','l');
    setRow(2,'j','j','m');
    setFaceTypes();
    rotation = 0;
    num = 16;
    boar = true;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 'p';
    initialization = true;
  }
  else if (type == 17)
  {
    setRow(0,'j','j','m');
    setRow(1,'t','t','l');
    setRow(2,'j','t','m');
    setFaceTypes();
    rotation = 0;
    num = 17;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 'q';
    initialization = true;
  }
  else if (type == 18)
  {
    setRow(0,'j','j','m');
    setRow(1,'t','t','l');
    setRow(2,'j','t','m');
    setFaceTypes();
    rotation = 0;
    num = 18;
    boar = false;
    buffalo = true;
    deer = false;
    crocodile = false;
    this->type = 'r';
    initialization = true;
  }
  else if (type == 19)
  {
    setRow(0,'j','t','m');
    setRow(1,'j','t','l');
    setRow(2,'j','t','m');
    setFaceTypes();
    rotation = 0;
    num = 19;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 's';
    initialization = true;
  }
  else if (type == 20)
  {
    setRow(0,'j','t','m');
    setRow(1,'j','t','l');
    setRow(2,'j','t','m');
    setFaceTypes();
    rotation = 0;
    num = 20;
    boar = false;
    buffalo = false;
    deer = true;
    crocodile = false;
    this->type = 't';
    initialization = true;
  }
  else if (type == 21)
  {
    setRow(0,'m','t','m');
    setRow(1,'l','l','l');
    setRow(2,'l','l','l');
    setFaceTypes();
    rotation = 0;
    num = 21;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 'u';
    initialization = true;
  }
  else if (type == 22)
  {
    setRow(0,'j','t','m');
    setRow(1,'t','t','l');
    setRow(2,'j','t','m');
    setFaceTypes();
    rotation = 0;
    num = 22;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 'v';
    initialization = true;
  }
  else if (type == 23)
  {
    setRow(0,'j','t','m');
    setRow(1,'t','t','l');
    setRow(2,'j','t','m');
    setFaceTypes();
    rotation = 0;
    num = 23;
    boar = true;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 'w';
    initialization = true;
  }
  else if (type == 24)
  {
    setRow(0,'j','t','m');
    setRow(1,'t','t','l');
    setRow(2,'m','l','l');
    setFaceTypes();
    rotation = 0;
    num = 24;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 'x';
    initialization = true;
  }
  else if (type == 25)
  {
    setRow(0,'j','t','m');
    setRow(1,'t','t','l');
    setRow(2,'m','l','l');
    setFaceTypes();
    rotation = 0;
    num = 25;
    boar = false;
    buffalo = true;
    deer = false;
    crocodile = false;
    this->type = 'y';
    initialization = true;
  }
  else if (type == 26)
  {
    setRow(0,'m','l','m');
    setRow(1,'j','t','j');
    setRow(2,'j','t','j');
    setFaceTypes();
    rotation = 0;
    num = 26;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = 'z';
    initialization = true;
  }
  else if (type == 27)
  {
    setRow(0,'m','l','m');
    setRow(1,'j','t','j');
    setRow(2,'j','t','j');
    setFaceTypes();
    rotation = 0;
    num = 27;
    boar = false;
    buffalo = false;
    deer = true;
    crocodile = false;
    this->type = '#';
    initialization = true;
  }
  else if (type == 28)
  {
    setRow(0,'m','t','m');
    setRow(1,'l','l','l');
    setRow(2,'l','l','l');
    setFaceTypes();
    rotation = 0;
    num = 28;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = true;
    this->type = '!';
    initialization = true;
  }
  else
  {
    rotation = 0;
    num = 0;
    boar = false;
    buffalo = false;
    deer = false;
    crocodile = false;
    this->type = '.';
    initialization = false;
  }
}
Tile::Tile()
{
  rotation = 0;
  num = 0;
  boar = false;
  buffalo = false;
  deer = false;
  crocodile = false;
  type = '.';
	initialization = false;
}
Tile::~Tile()
{

}

void Tile::setFaceTypes() {
  upFace.setType(innerBlocks[0][1].getType());
  downFace.setType(innerBlocks[2][1].getType());
  leftFace.setType(innerBlocks[1][0].getType());
  rightFace.setType(innerBlocks[1][2].getType());
}

void Tile::setRow(int row, char type1, char type2, char type3) {
  innerBlocks[row][0] = Block(type1);
  innerBlocks[row][1] = Block(type2);
  innerBlocks[row][2] = Block(type3);
}
// Rotate a tile to the left by 90 degrees. (Ex: left face would now be down face, top face would be left, etc...)
void Tile::rotate()
{
	std::vector<std::vector<Block> > unrotated = innerBlocks;

  // Top row
  innerBlocks[0][0] = Block(unrotated[0][2]);
  innerBlocks[0][1] = Block(unrotated[1][2]);
  innerBlocks[0][2] = Block(unrotated[2][2]);

  this->upFace.setType(innerBlocks[0][1].getType());

  // Middle row except center block (doesn't rotate)
  innerBlocks[1][0] = Block(unrotated[0][1]);
  innerBlocks[1][2] = Block(unrotated[2][1]);

  this->leftFace.setType(innerBlocks[1][0].getType());
  this->rightFace.setType(innerBlocks[1][2].getType());

  // Bottom row
  innerBlocks[2][0] = Block(unrotated[0][0]);
  innerBlocks[2][1] = Block(unrotated[1][0]);
  innerBlocks[2][2] = Block(unrotated[2][0]);

  this->downFace.setType(innerBlocks[2][1].getType());

  if (rotation < 3)
    rotation++;
  else
    rotation = 0;
}

void Tile::setNeighborUpTile(Tile &tile) {
  upTile = &tile;
}
void Tile::setNeighborDownTile(Tile &tile) {
  downTile = &tile;
}
void Tile::setNeighborLeftTile(Tile &tile) {
  leftTile = &tile;
}
void Tile::setNeighborRightTile(Tile &tile) {
  rightTile = &tile;
}

// Method to check if tile has any open face (up, down, left, right)
bool Tile::hasOpenFace()
{
	if(!upFace.connected() || !downFace.connected() || !leftFace.connected() || !rightFace.connected())
    return true;
	else
    return false;
}
// Method to obtain all the open faces of a tile. Check each face, if not connected then push to vector
std::vector<std::string> Tile::getOpenFaces()
{
	std::vector<std::string> openFaces;
	if(!upFace.connected())
		openFaces.push_back("up");
	if(!downFace.connected())
		openFaces.push_back("down");
	if(!leftFace.connected())
		openFaces.push_back("left");
	if(!rightFace.connected())
		openFaces.push_back("right");
	return openFaces;
}

void Tile::placeMeeple(std::pair<int, int> location)
{
	innerBlocks[location.first][location.second].placeMeeple();
}
