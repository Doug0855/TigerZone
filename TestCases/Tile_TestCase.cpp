#include "Tile.h"
#include <iostream>

void print_tile(Tile &tile)
{	
	Face up = tile.getUpFace();
	Face down = tile.getDownFace();
	Face left = tile.getLeftFace();
	Face right = tile.getRightFace();
	Block center = tile.getCenter();

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
	std::cout << "*     Testing Tile Class     *" << std::endl;
	std::cout << "******************************" << std::endl;	

	for (int i = 1; i <= 28; i++)
	{
		Tile tile(i);
		std::cout << "Printing Tile " << i << " values" << std::endl;
		print_tile(tile);
	}
	return 0;
}
