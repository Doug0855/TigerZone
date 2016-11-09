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
	Tile tile1;	
	Tile tile2;
	Tile tile3;

	gameBoard.place_tile(std::pair<int,int>(71,72), tile1);
	gameBoard.place_tile(std::pair<int,int>(72,72), tile2);
	gameBoard.place_tile(std::pair<int,int>(73,72), tile3);
	
	std::vector<std::pair<int,int> > openSpots = gameBoard.display_positions();
	std::cout<<"open spots: "<<openSpots.size()<<std::endl;
	for(int i = 0; i < openSpots.size(); i++) {
		int row = openSpots[i].first;
		int col = openSpots[i].second;

		std::vector<std::string> openFaces = gameBoard.m_board[row][col].getOpenFaces();
		std::cout<<"Open faces of "<<row<<" "<<col<<" are: ";
		for(int j = 0; j < openFaces.size(); j++) {
			std::cout<<openFaces[j]<<" ";
		}
		std::cout<<std::endl;
	}

	// Print out gameboard, if actual tile will print A, if default will print '.' 
	// Should only have 1 A in the middle as of now
	// for(int i = 0; i < gameBoard.m_board.size(); i++)
	// {
	// 	for(int j = 0; j < gameBoard.m_board[0].size(); j++)
	// 	{
	// 		if(gameBoard.m_board[i][j].hasInit)
	// 			std::cout<<'A';
	// 		else
	// 			std::cout<<'.';
	// 	}
	// 	std::cout<<std::endl;
	// }
}