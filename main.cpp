#include <iostream>
#include <utility>

#include "Board.cpp"
#include "Tile.cpp"
#include "Block.cpp"
#include "Face.cpp"
#include "Meeple.cpp"

int main() {
	std::cout <<"Hello!"<<std::endl;
	Board gameBoard;
	

	// Create center tile to place in middle of matrix and test place_tile working
	std::pair<int,int> loc(72,72);
	Tile centerTile;	
	centerTile.hasInit = true;
	
	gameBoard.place_tile(loc, centerTile);

	// Print out gameboard, if actual tile will print A, if default will print '.' 
	// Should only have 1 A in the middle as of now
	for(int i = 0; i < gameBoard.m_board	.size(); i++)
	{
		for(int j = 0; j < gameBoard.m_board	[0].size(); j++)
		{
			if(gameBoard.m_board	[i][j].hasInit)
				std::cout<<'A';
			else
				std::cout<<'.';
		}
		std::cout<<std::endl;
	}
}