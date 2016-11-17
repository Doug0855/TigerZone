#include "Tile.h"

Tile::Tile()
{
	hasInit = false;
}
Tile::~Tile()
{
	hasInit = false;
}

std::string Tile::to_string()
{
	return "empty";
}

// Rotate a tile to the right by 90 degrees. (Ex: left face would now be top face, top face would be right, etc...)
void Tile::rotate()
{
	Face upFace = this->up;
	Face downFace = this->down;
	Face leftFace = this->left;
	Face rightFace = this->right;

	this->up = leftFace;
	this->right = upFace;
	this->down = rightFace;
	this->left = downFace;
	
	
}

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

Tile::Tile(int type)
{
	if (type == 1)
	{
		this->up = Face('j', 'j', 'j');
		this->down = Face('j', 'j', 'j');
		this->left = Face('j', 'j', 'j');
		this->right = Face('j', 'j', 'j');
		this->boar = false;
		this->buffalo = false;
		this->deer = false;
		this->type = 'a';
		
		this->up.inwardAcrossFace = &this->down;
		this->up.inwardLeftFace = &this->right;
		this->up.inwardRightFace = &this->left;

		this->down.inwardAcrossFace = &this->up;
		this->down.inwardLeftFace = &this->left;
		this->down.inwardRightFace = &this->right;

		this->left.inwardAcrossFace = &this->right;
		this->left.inwardLeftFace = &this->up;
		this->left.inwardRightFace = &this->down;

		this->right.inwardAcrossFace = &this->left;
		this->right.inwardLeftFace = &this->down;
		this->right.inwardRightFace = &this->up;

	}
	else if (type == 2)
	{
		this->up = Face('j', 'j', 'j');
		this->down = Face('j', 'j', 'j');
		this->left = Face('j', 'j', 'j');
		this->right = Face('j', 'j', 'j');
		this->center = Block('d');
		this->boar = false;
		this->buffalo = false;
		this->deer = false;
		this->type = 'b';

		this->up.inwardAcrossFace = &this->down;
		this->up.inwardLeftFace = &this->right;
		this->up.inwardRightFace = &this->left;

		this->down.inwardAcrossFace = &this->up;
		this->down.inwardLeftFace = &this->left;
		this->down.inwardRightFace = &this->right;

		this->left.inwardAcrossFace = &this->right;
		this->left.inwardLeftFace = &this->up;
		this->left.inwardRightFace = &this->down;

		this->right.inwardAcrossFace = &this->left;
		this->right.inwardLeftFace = &this->down;
		this->right.inwardRightFace = &this->up;
	}
	else if (type == 3)
	{
		this->up = Face('j', 'j', 'j');
		this->down = Face('j', 't', 'j');
		this->left = Face('j', 'j', 'j');
		this->right = Face('j', 'j', 'j');
		this->center = Block('d');
		this->boar = false;
		this->buffalo = false;
		this->deer = false;
		this->type = 'c';

		this->up.inwardAcrossFace = NULL;
		this->up.inwardLeftFace = &this->right;
		this->up.inwardRightFace = &this->left;

		this->down.inwardAcrossFace = NULL;
		this->down.inwardLeftFace = NULL;
		this->down.inwardRightFace = NULL;

		this->left.inwardAcrossFace = &this->right;
		this->left.inwardLeftFace = &this->up;
		this->left.inwardRightFace = NULL;

		this->right.inwardAcrossFace = &this->left;
		this->right.inwardLeftFace = NULL;
		this->right.inwardRightFace = &this->up;
	}
	else if (type == 4)
	{
		this->up = Face('j', 't', 'j');
		this->down = Face('j', 't', 'j');
		this->left = Face('j', 't', 'j');
		this->right = Face('j', 't', 'j');
		this->boar = false;
		this->buffalo = false;
		this->deer = false;
		this->type = 'd';
	
		this->up.inwardAcrossFace = NULL;
		this->up.inwardLeftFace = NULL;
		this->up.inwardRightFace = NULL;

		this->down.inwardAcrossFace = NULL;
		this->down.inwardLeftFace = NULL;
		this->down.inwardRightFace = NULL;

		this->left.inwardAcrossFace = NULL;
		this->left.inwardLeftFace = NULL;
		this->left.inwardRightFace = NULL;

		this->right.inwardAcrossFace = NULL;
		this->right.inwardLeftFace = NULL;
		this->right.inwardRightFace = NULL;
	}
	else if (type == 5)
	{
		this->up = Face('j', 't', 'j');
		this->down = Face('j', 't', 'j');
		this->left = Face('j', 'j', 'j');
		this->right = Face('j', 'j', 'j');
		this->boar = false;
		this->buffalo = false;
		this->deer = false;
		this->type = 'e';

		this->up.inwardAcrossFace = &this->down;
		this->up.inwardLeftFace = NULL;
		this->up.inwardRightFace = NULL;

		this->down.inwardAcrossFace = &this->up;
		this->down.inwardLeftFace = NULL;
		this->down.inwardRightFace = NULL;

		this->left.inwardAcrossFace = NULL;
		this->left.inwardLeftFace = NULL;
		this->left.inwardRightFace = NULL;

		this->right.inwardAcrossFace = NULL;
		this->right.inwardLeftFace = NULL;
		this->right.inwardRightFace = NULL;
	}
	else if (type == 6)
	{
		this->up = Face('j', 't', 'j');
		this->down = Face('j', 'j', 'j');
		this->left = Face('j', 't', 'j');
		this->right = Face('j', 'j', 'j');
		this->boar = false;
		this->buffalo = false;
		this->deer = false;
		this->type = 'f';

		this->up.inwardAcrossFace = NULL;
		this->up.inwardLeftFace = NULL;
		this->up.inwardRightFace = &this->left;

		this->down.inwardAcrossFace = NULL;
		this->down.inwardLeftFace = NULL;
		this->down.inwardRightFace = &this->right;

		this->left.inwardAcrossFace = NULL;
		this->left.inwardLeftFace = &this->up;
		this->left.inwardRightFace = NULL;

		this->right.inwardAcrossFace = NULL;
		this->right.inwardLeftFace = &this->down;
		this->right.inwardRightFace = NULL;
	}
	else if (type == 7)
	{
		this->up = Face('j', 't', 'j');
		this->down = Face('j', 't', 'j');
		this->left = Face('j', 't', 'j');
		this->right = Face('j', 'j', 'j');
		this->boar = false;
		this->buffalo = false;
		this->deer = false;
		this->type = 'g';
	
		this->up.inwardAcrossFace = NULL;
		this->up.inwardLeftFace = NULL;
		this->up.inwardRightFace = NULL;

		this->down.inwardAcrossFace = NULL;
		this->down.inwardLeftFace = NULL;
		this->down.inwardRightFace = NULL;

		this->left.inwardAcrossFace = NULL;
		this->left.inwardLeftFace = NULL;
		this->left.inwardRightFace = NULL;

		this->right.inwardAcrossFace = NULL;
		this->right.inwardLeftFace = NULL;
		this->right.inwardRightFace = NULL;	
	}
	else if (type == 8)
	{
		this->up = Face('l', 'l', 'l');
		this->down = Face('l', 'l', 'l');
		this->left = Face('l', 'l', 'l');
		this->right = Face('l', 'l', 'l');
		this->boar = false;
		this->buffalo = false;
		this->deer = false;
		this->type = 'h';

		this->up.inwardAcrossFace = &this->down;
		this->up.inwardLeftFace = &this->right;
		this->up.inwardRightFace = &this->left;

		this->down.inwardAcrossFace = &this->up;
		this->down.inwardLeftFace = &this->left;
		this->down.inwardRightFace = &this->right;

		this->left.inwardAcrossFace = &this->right;
		this->left.inwardLeftFace = &this->up;
		this->left.inwardRightFace = &this->down;

		this->right.inwardAcrossFace = &this->left;
		this->right.inwardLeftFace = &this->down;
		this->right.inwardRightFace = &this->up;
	}
	else if (type == 9)
	{
		this->up = Face('j', 'j', 'j');
		this->down = Face('l', 'l', 'l');
		this->left = Face('l', 'l', 'l');
		this->right = Face('l', 'l', 'l');
		this->boar = false;
		this->buffalo = false;
		this->deer = false;
		this->type = 'i';

		this->up.inwardAcrossFace = NULL;
		this->up.inwardLeftFace = NULL;
		this->up.inwardRightFace = NULL;

		this->down.inwardAcrossFace = NULL;
		this->down.inwardLeftFace = &this->left;
		this->down.inwardRightFace = &this->right;

		this->left.inwardAcrossFace = &this->right;
		this->left.inwardLeftFace = NULL;
		this->left.inwardRightFace = &this->down;

		this->right.inwardAcrossFace = &this->left;
		this->right.inwardLeftFace = &this->down;
		this->right.inwardRightFace = NULL;
	}
	else if (type == 10)
	{
		this->up = Face('l', 'l', 'l');
		this->down = Face('j', 'j', 'j');
		this->left = Face('j', 'j', 'j');
		this->right = Face('l', 'l', 'l');
		this->boar = false;
		this->buffalo = false;
		this->deer = false;
		this->type = 'j';

		this->up.inwardAcrossFace = NULL;
		this->up.inwardLeftFace = &this->right;
		this->up.inwardRightFace = NULL;

		this->down.inwardAcrossFace = NULL;
		this->down.inwardLeftFace = &this->left;
		this->down.inwardRightFace = NULL;

		this->left.inwardAcrossFace = NULL;
		this->left.inwardLeftFace = NULL;
		this->left.inwardRightFace = &this->down;

		this->right.inwardAcrossFace = NULL;
		this->right.inwardLeftFace = NULL;
		this->right.inwardRightFace = &this->up;
	}
	else if (type == 11)
	{
		this->up = Face('j', 'j', 'j');
		this->down = Face('j', 'j', 'j');
		this->left = Face('l', 'l', 'l');
		this->right = Face('l', 'l', 'l');
		this->boar = false;
		this->buffalo = false;
		this->deer = false;
		this->type = 'k';

		this->up.inwardAcrossFace = NULL;
		this->up.inwardLeftFace = NULL;
		this->up.inwardRightFace = NULL;

		this->down.inwardAcrossFace = NULL;
		this->down.inwardLeftFace = NULL;
		this->down.inwardRightFace = NULL;

		this->left.inwardAcrossFace = &this->right;
		this->left.inwardLeftFace = NULL;
		this->left.inwardRightFace = NULL;

		this->right.inwardAcrossFace = &this->left;
		this->right.inwardLeftFace = NULL;
		this->right.inwardRightFace = NULL;
	}
	else if (type == 12)
	{
		this->up = Face('l', 'l', 'l');
		this->down = Face('l', 'l', 'l');
		this->left = Face('j', 'j', 'j');
		this->right = Face('j', 'j', 'j');
		this->boar = false;
		this->buffalo = false;
		this->deer = false;
		this->type = 'l';
		
		this->up.inwardAcrossFace = NULL;
		this->up.inwardLeftFace = NULL;
		this->up.inwardRightFace = NULL;

		this->down.inwardAcrossFace = NULL;
		this->down.inwardLeftFace = NULL;
		this->down.inwardRightFace = NULL;

		this->left.inwardAcrossFace = &this->right;
		this->left.inwardLeftFace = NULL;
		this->left.inwardRightFace = NULL;

		this->right.inwardAcrossFace = &this->left;
		this->right.inwardLeftFace = NULL;
		this->right.inwardRightFace = NULL;
	}
	else if (type == 13)
	{
		this->up = Face('l', 'l', 'l');
		this->down = Face('j', 'j', 'j');
		this->left = Face('j', 'j', 'j');
		this->right = Face('j', 'j', 'j');
		this->boar = false;
		this->buffalo = false;
		this->deer = false;
		this->type = 'm';
		
		this->up.inwardAcrossFace = NULL;
		this->up.inwardLeftFace = NULL;
		this->up.inwardRightFace = NULL;

		this->down.inwardAcrossFace = NULL;
		this->down.inwardLeftFace = &this->left;
		this->down.inwardRightFace = &this->right;

		this->left.inwardAcrossFace = &this->right;
		this->left.inwardLeftFace = NULL;
		this->left.inwardRightFace = &this->down;

		this->right.inwardAcrossFace = &this->left;
		this->right.inwardLeftFace = &this->down;
		this->right.inwardRightFace = NULL;
	}
	else if (type == 14)
	{
		this->up = Face('j', 'j', 'j');
		this->down = Face('l', 'l', 'l');
		this->left = Face('j', 'j', 'j');
		this->right = Face('l', 'l', 'l');
		this->boar = false;
		this->buffalo = false;
		this->deer = false;
		this->type = 'n';
		
		this->up.inwardAcrossFace = NULL;
		this->up.inwardLeftFace = NULL;
		this->up.inwardRightFace = &this->left;

		this->down.inwardAcrossFace = NULL;
		this->down.inwardLeftFace = NULL;
		this->down.inwardRightFace = &this->right;

		this->left.inwardAcrossFace = NULL;
		this->left.inwardLeftFace = &this->up;
		this->left.inwardRightFace = NULL;

		this->right.inwardAcrossFace = NULL;
		this->right.inwardLeftFace = &this->down;
		this->right.inwardRightFace = NULL;
	}
	else if (type == 15)
	{
		this->up = Face('j', 't', 'j');
		this->down = Face('j', 'j', 'j');
		this->left = Face('j', 't', 'j');
		this->right = Face('l', 'l', 'l');
		this->boar = false;
		this->buffalo = false;
		this->deer = false;
		this->type = 'o';
		connectInnerFaces();
	}
	else if (type == 16)
	{
		this->up = Face('j', 't', 'j');
		this->down = Face('j', 'j', 'j');
		this->left = Face('j', 't', 'j');
		this->right = Face('l', 'l', 'l');
		this->boar = true;
		this->buffalo = false;
		this->deer = false;
		this->type = 'p';
		connectInnerFaces();
	}
	else if (type == 17)
	{
		this->up = Face('j', 'j', 'j');
		this->down = Face('j', 't', 'j');
		this->left = Face('j', 't', 'j');
		this->right = Face('l', 'l', 'l');
		this->boar = false;
		this->buffalo = false;
		this->deer = false;
		this->type = 'q';
		connectInnerFaces();
	}
	else if (type == 18)
	{
		this->up = Face('j', 'j', 'j');
		this->down = Face('j', 't', 'j');
		this->left = Face('j', 't', 'j');
		this->right = Face('l', 'l', 'l');
		this->boar = false;
		this->buffalo = true;
		this->deer = false;
		this->type = 'r';
		connectInnerFaces();
	}
	else if (type == 19)
	{
		this->up = Face('j', 't', 'j');
		this->down = Face('j', 't', 'j');
		this->left = Face('j', 'j', 'j');
		this->right = Face('l', 'l', 'l');
		this->boar = false;
		this->buffalo = false;
		this->deer = false;
		this->type = 's';
		connectInnerFaces();
	}
	else if (type == 20)
	{
		this->up = Face('j', 't', 'j');
		this->down = Face('j', 't', 'j');
		this->left = Face('j', 'j', 'j');
		this->right = Face('l', 'l', 'l');
		this->boar = false;
		this->buffalo = false;
		this->deer = true;
		this->type = 't';
		connectInnerFaces();
	}
	else if (type == 21)
	{
		this->up = Face('j', 't', 'j');
		this->down = Face('l', 'l', 'l');
		this->left = Face('l', 'l', 'l');
		this->right = Face('l', 'l', 'l');
		this->boar = false;
		this->buffalo = false;
		this->deer = false;
		this->type = 'u';
		connectInnerFaces();
	}
	else if (type == 22)
	{
		this->up = Face('j', 't', 'j');
		this->down = Face('j', 't', 'j');
		this->left = Face('j', 't', 'j');
		this->right = Face('l', 'l', 'l');
		this->boar = false;
		this->buffalo = false;
		this->deer = false;
		this->type = 'v';
		connectInnerFaces();
	}
	else if (type == 23)
	{
		this->up = Face('j', 't', 'j');
		this->down = Face('j', 't', 'j');
		this->left = Face('j', 't', 'j');
		this->right = Face('l', 'l', 'l');
		this->boar = true;
		this->buffalo = false;
		this->deer = false;
		this->type = 'w';
		connectInnerFaces();
	}
	else if (type == 24)
	{
		this->up = Face('j', 't', 'j');
		this->down = Face('l', 'l', 'l');
		this->left = Face('j', 't', 'j');
		this->right = Face('l', 'l', 'l');
		this->boar = false;
		this->buffalo = false;
		this->deer = false;
		this->type = 'x';
		connectInnerFaces();
	}
	else if (type == 25)
	{
		this->up = Face('j', 't', 'j');
		this->down = Face('l', 'l', 'l');
		this->left = Face('j', 't', 'j');
		this->right = Face('l', 'l', 'l');
		this->boar = false;
		this->buffalo = true;
		this->deer = false;
		this->type = 'y';
		connectInnerFaces();
	}
	else if (type == 26)
	{
		this->up = Face('l', 'l', 'l');
		this->down = Face('j', 't', 'j');
		this->left = Face('j', 'j', 'j');
		this->right = Face('j', 'j', 'j');
		this->boar = false;
		this->buffalo = false;
		this->deer = false;
		this->type = 'z';
		connectInnerFaces();
	}
	else if (type == 27)
	{
		this->up = Face('l', 'l', 'l');
		this->down = Face('j', 't', 'j');
		this->left = Face('j', 'j', 'j');
		this->right = Face('j', 'j', 'j');
		this->boar = false;
		this->buffalo = false;
		this->deer = true;
		this->type = '#';
		connectInnerFaces();
	}
	else
	{
		hasInit = false;
	}
}
