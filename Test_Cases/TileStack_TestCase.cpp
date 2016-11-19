#include "TileStack.h"
#include <iostream>

void print_tile(Tile &tile)
{
	//g++ Block.h Block.cpp Face.h Face.cpp Tile.h Tile.cpp TileStack.h TileStack.cpp TileStack_TestCase.cpp -o TileStackTest.out
	Face *up = tile.getUpFace();
	Face *down = tile.getDownFace();
	Face *left = tile.getLeftFace();
	Face *right = tile.getRightFace();
	Block *center = tile.getCenter();

	std::cout << "Printing Tile of type " << tile.getType() << ": " << std::endl;
	std::cout << "	Tile up face values are: " << std::endl;
	std::cout << "	    " << up->getBlockType(1) << " " << up->getBlockType(2) << " " << up->getBlockType(3) << std::endl;
	std::cout << "	Tile down face values are: " << std::endl;
	std::cout << "	    " << down->getBlockType(1) << " " << down->getBlockType(2) << " " << down->getBlockType(3) << std::endl;
	std::cout << "	Tile left face values are: " << std::endl;
	std::cout << "	    " << left->getBlockType(1) << " " << left->getBlockType(2) << " " << left->getBlockType(3) << std::endl;
	std::cout << "	Tile right face values are: " << std::endl;
	std::cout << "	    " << right->getBlockType(1) << " " << right->getBlockType(2) << " " << right->getBlockType(3) << std::endl;
	std::cout << "	Tile center block value is: " << std::endl;
	std::cout << "	    " << center->getType() << std::endl;
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
