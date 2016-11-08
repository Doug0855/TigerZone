#inlcude "Tile.h"

Tile()
{

}

~Tile()
{
	
}

string to_string()
{
	
}

// Rotate a tile to the right by 90 degrees. (Ex: left face would now be top face, top face would be right, etc...)
void rotate(Tile tile)
{
	Face upFace = this.up;
	Face downFace = this.down;
	Face leftface = this.left;
	Face rightFace = this.right;

	this.up = leftFace;
	this.right = upFace;
	this.down = rightFace;
	this.left = downFace;
	
	
}

bool hasOpenFace()
{
	if(!up.connected() || !down.connected() || !left.connected() || !right.conncted()) return true;
	else return false;
}

// Method to obtain all the open faces of a tile. Check each face, if not connected then push to vector
std::vector<Tile> getOpenFaces() 
{
	std::vector<Tile> openFaces;
	if(!up.connected())
		openFaces.pushBack(up);
	if(!down.connected())
		openFaces.pushBack(down);
	if(!left.connected())
		openFaces.pushBack(left);
	if(!right.connected())
		openFaces.pushBack(right);

	return openFaces;
}

bool shield
{
	
}
