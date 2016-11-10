#include <iostream>
#include <utility>

#include "Board.cpp"
#include "Tile.cpp"
#include "Block.cpp"
#include "Face.cpp"
#include "Meeple.cpp"

int main() {
	Board gameBoard;	

	Tile tile1;	
	Tile tile2;
	Tile tile3;

	tile2.up.getM1()->setType("up2");
	tile2.up.getM2()->setType("up2");
	tile2.up.getM3()->setType("up2");

	tile2.left.getM1()->setType("left2");
	tile2.left.getM2()->setType("left2");
	tile2.left.getM3()->setType("left2");

	tile2.right.getM1()->setType("right2");
	tile2.right.getM2()->setType("right2");
	tile2.right.getM3()->setType("right2");

	tile2.down.getM1()->setType("Ground");
	tile2.down.getM2()->setType("Ground");
	tile2.down.getM3()->setType("Ground");

	tile3.up.getM1()->setType("Ground");
	tile3.up.getM2()->setType("Ground");
	tile3.up.getM3()->setType("Ground");

	tile3.left.getM1()->setType("left3");
	tile3.left.getM2()->setType("left3");
	tile3.left.getM3()->setType("left3");

	tile3.right.getM1()->setType("right3");
	tile3.right.getM2()->setType("right3");
	tile3.right.getM3()->setType("right3");
	
	tile3.down.getM1()->setType("down3");
	tile3.down.getM2()->setType("down3");
	tile3.down.getM3()->setType("down3");


	gameBoard.place_tile(std::pair<int,int>(71,72), tile1);
	gameBoard.place_tile(std::pair<int,int>(72,72), tile2);
	// gameBoard.place_tile(std::pair<int,int>(73,72), tile3);

	// Get coordinates of all possible locations where we can place a tile 
	std::vector<std::pair<int,int> > availablePlacements = gameBoard.display_positions(&tile3);

	std::cout<<"# of open places: "<<availablePlacements.size();
	for(int i = 0; i < availablePlacements.size(); i++) {
		int row = availablePlacements[i].first;
		int col = availablePlacements[i].second;

		std::cout<<"Open placement at "<<row<<" "<<col<<std::endl;
	}

	int z;
	std::cin >> z;
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
};