#include "../Tile.h"
#include <iostream>

void print_tile(Tile &tile)
{
	//g++ Block.h Block.cpp Face.h Face.cpp Tile.h Tile.cpp Tile_TestCase.cpp -o TileTest.out
	Face* up = tile.getUpFace();
	Face* down = tile.getDownFace();
	Face* left = tile.getLeftFace();
	Face* right = tile.getRightFace();
	Block* center = tile.getCenter();

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
	tile.rotate();
}
void print_tile_copy(Tile tile)
{
	Face* up = tile.getUpFace();
	std::cout << "Printing from copy: " << up->getLeftFace()->getBlockType(1) << std::endl;
	tile.rotate();
	tile.rotate();
}
int main ()
{
	std::cout << "******************************" << std::endl;
	std::cout << "*     Testing Tile Class     *" << std::endl;
	std::cout << "******************************" << std::endl;

		Tile tile1(1), tile2(2);
		std::cout << "Printing Tile 1 values" << std::endl;
		print_tile(tile1);
		print_tile_copy(tile1);
		std::cout << "print tile rotation: " << tile1.getRotations() << std::endl;
		std::cout << "Printing Tile 2 values" << std::endl;
		print_tile(tile2);

		std::vector<std::string> openFaces = tile1.getOpenFaces();
		std::cout << "How many open faces does tile 1 have? " << openFaces.size() << std::endl;
		std::cout << "Does tile 2 have open faces? " << tile2.hasOpenFace() << std::endl;

		std::cout << "Compare two tile's faces: " << tile1.getUpFace()->faceEquals(*tile2.getDownFace()) << std::endl;
			tile1.getUpFace()->setNeighborFace(*tile2.getDownFace());
			tile2.getDownFace()->setNeighborFace(*tile1.getUpFace());
		std::vector<std::string> openFaces2 = tile1.getOpenFaces();
		std::cout << "How many open faces does tile 1 have? " << openFaces2.size() << std::endl;
		std::cout << "Getting neighborFace's second block type: " << tile1.getUpFace()->getNeighborFace()->getBlockType(2) << std::endl;


	return 0;


}
