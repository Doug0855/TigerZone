#include <iostream>
#include <utility>

#include "Board.cpp"
#include "Tile.cpp"
#include "Block.cpp"
#include "Face.cpp"
#include "Meeple.cpp"

int main() {
	Board gameBoard;	

	Tile("jungle","lake","road","jungle") tile1;	
	Tile tile2;
	Tile tile3;


	gameBoard.place_tile(std::pair<int,int>(71,72), tile1);
	// gameBoard.place_tile(std::pair<int,int>(72,72), tile2);
	// gameBoard.place_tile(std::pair<int,int>(73,72), tile3);

	// Get coordinates of all possible locations where we can place a tile 
	std::vector<std::pair<int,int> > availableLocations = gameBoard.display_positions(&tile3);

	// std::cout<<"# of open places: "<<availableLocations.size()<<std::endl;
	// for(int i = 0; i < availableLocations.size(); i++) {
	// 	int row = availableLocations[i].first;
	// 	int col = availableLocations[i].second;

	// 	std::cout<<"Open Location at "<<row<<" "<<col<<std::endl;
	// }

	std::pair<int,int> optimalLocation = gameBoard.getOptimalPlacement(&tile3, availableLocations);
	gameBoard.place_tile(optimalLocation, tile3);

	// int z;
	// std::cin >> z;
	
	Print out gameboard
	for(int i = 0; i < gameBoard.m_board.size(); i++)
	{
		for(int j = 0; j < gameBoard.m_board[0].size(); j++)
		{
			if(gameBoard.m_board[i][j].hasInit) {
				std::cout<<m_board[i][j].up->getType()<<endl
				<<m_board[i][j].up->getType()<< ' '<<m_board[i][j].up->getType()
				<<m_board[i][j].up->getType()<<;
			}
			else
				std::cout<<'*';
		}
		std::cout<<std::endl;
	}
};