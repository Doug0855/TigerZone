#include <iostream>
#include <utility>
#include <fstream>

#include "Board.cpp"
#include "Tile.cpp"
#include "Block.cpp"
#include "Face.cpp"
#include "Meeple.cpp"
#include "TileStack.cpp"

void printToTextFile(Board gameboard)
{
	std::ofstream out_data("Levels/level.txt");
	out_data << "Level:" << std::endl;
	for (auto& inner : gameboard.m_board) 
	{
		for (auto& item : inner) 
		{
			out_data << item.getRotations() << item.getType();
		}
		out_data << std::endl;
	}
	out_data.close();
}


int main() {
	Board gameBoard;	

	Tile tile1(19);	

	std::cout<< "Inner faces of tile 19: "<<
	TileStack tStack;
	tStack.shuffle();

	gameBoard.place_tile(std::pair<int,int>(72,72), tile1);

	for(int i = 0; i < tStack.tiles.size(); i ++) {
		Tile tile = tStack.tiles[i];

		// Get all positions that we may place the tile
		std::vector<std::pair<int,int> > availableLocations = gameBoard.display_positions(tile);

		// check if there are any available moves. If so then place at the optimal spot.
		if(availableLocations.size() > 0) {
			std::pair<int,int> optimalLocation = gameBoard.getOptimalPlacement(tile, availableLocations);	
			gameBoard.place_tile(optimalLocation, tile);	
		}
	}

	/*
	std::cout<< "rotations: ";
	for(int i = 0; i < rotations.size(); i++) {
		std::cout<<rotations[i]<<' ';
	}
	*/
	printToTextFile(gameBoard);
	// int z;
	// std::cin >> z;
	
	// Print out gameboard
	for(int i = 0; i < gameBoard.m_board.size(); i++)
	{
		for(int j = 0; j < gameBoard.m_board[0].size(); j++)
		{
			if(gameBoard.m_board[i][j].hasInit)
				std::cout<<'A';
			else
				std::cout<<'.';
		}
		std::cout<<std::endl;
	}
};

