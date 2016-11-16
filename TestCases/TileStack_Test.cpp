#include "TileStack.h"
#include <iostream>

void print_tile(Tile &tile)
{	
	Face up = tile.up;
	Face down = tile.down;
	Face left = tile.left;
	Face right = tile.right;
	Block center = tile.getCenter();
	
	std::cout << "Printing Tile of type: " << tile.getType() << std::endl;
	std::cout << "	Tile up face values are: " << std::endl;
	std::cout << "	    " << up.m_1.getType() << " " << up.m_2.getType() << " " << up.m_3.getType() << std::endl;
	std::cout << "	Tile down face values are: " << std::endl;
	std::cout << "	    " << down.m_1.getType() << " " << down.m_2.getType() << " " << down.m_3.getType() << std::endl;
	std::cout << "	Tile left face values are: " << std::endl;
	std::cout << "	    " << left.m_1.getType() << " " << left.m_2.getType() << " " << left.m_3.getType() << std::endl;
	std::cout << "	Tile right face values are: " << std::endl;
	std::cout << "	    " << right.m_1.getType() << " " << right.m_2.getType() << " " << right.m_3.getType() << std::endl;
	std::cout << "	Tile center block value is: " << std::endl;
	std::cout << "	    " << center.getType() << std::endl;
	std::cout << "	Does the tile have a boar, buffalo, deer? " << std::endl;
	std::cout << "	    " << tile.hasBoar() << ", " << tile.hasBuffalo() << ", " << tile.hasDeer() <<  std::endl;
}

int main ()
{
	std::cout << "******************************" << std::endl;
	std::cout << "*  Testing TileStack Class   *" << std::endl;
	std::cout << "******************************" << std::endl;

	TileStack tiles; 
//	tiles.shuffle();

	for (std::vector<Tile>::iterator it = tiles.tiles.begin(); it != tiles.tiles.end(); ++it)
		print_tile(*it);

	return 0;
}
