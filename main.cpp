#include <iostream>
#include <utility>

#include "Board.cpp"
#include "Tile.cpp"
#include "Block.cpp"
#include "Face.cpp"
#include "Meeple.cpp"

int main() {
	Board gameBoard;	

	// Create center tile to place in middle of matrix and test place_tile working
	std::pair<int,int> loc(72,72);
	Tile centerTile;	

	Tile additonalTile;
	gameBoard.place_tile(loc, centerTile);
	gameBoard.place_tile(std::pair<int,int>(71,72), additonalTile);

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