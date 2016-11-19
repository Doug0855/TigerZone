#include <iostream>
#include <utility>
#include <fstream>
#include <iomanip>

#include "Tile_Structure/Tile.h"
#include "Tile_Structure/Block.h"
#include "Tile_Structure/Face.h"
#include "Tile_Structure/TileStack.h"
//#include "Meeple.h"
#include "Board.h"

#define WHITE   "\033[37m"      /* White */
#define BLUE    "\033[34m"      /* Blue */
#define GREEN   "\033[32m"      /* Green */
#define RED     "\033[31m"      /* Red */
#define BLACK   "\033[30m"      /* Black */
#define RESET   "\033[0m"       /* Reset */
#define BOLD    "\033[1m"       /* Bold */
#define INVERT  "\033[7m"       /* Invert */

/*void printToTextFile(Board gameboard)
{
	std::ofstream out_data("Levels/level.txt");
	out_data << "Level:" << std::endl;
	for (auto& inner : gameboard.m_board)
	{
		for (auto& item : inner)
		{
			out_data << item->getRotations() << item->getType();
		}
		out_data << std::endl;
	}
	out_data.close();
}*/
void printBoard(Board gameBoard) //debugging
{

	// Print out gameboard
	std::cout << "size of gameBoard is: " << gameBoard.m_board.size() << " x " << gameBoard.m_board[0].size() << std::endl;
	for(int i = 0; i < gameBoard.m_board.size(); i++)
	{
		std::cout << std::setw(3) << i << ' ';
		for(int j = 0; j < gameBoard.m_board[i].size(); j++)
		{
				if (gameBoard.m_board[i][j] != NULL)
					std::cout << GREEN <<  gameBoard.m_board[i][j]->getRotations() << gameBoard.m_board[i][j]->getType() << WHITE << RESET;
				else
					std::cout << std::setw(2) << '.';
		}
		std::cout<<std::endl;
	}
} 															//debug
void printStack(TileStack stack) //debugging
{
	/*print tile stack content for debugging*/
	std::cout << "TileStack content(" << stack.tiles.size() << "): ";
	for(int i = 0; i < stack.tiles.size(); i++) {
		Tile tile = stack.tiles[i];
		std::cout << tile.getType() << ' ';
	}
	std::cout << std::endl;/**/
}
void printTileAdddresses(Tile &tile) //debugging
{
	std::cout << "DownFace addr: " << tile.getDownFace() << std::endl;
	std::cout << " Accross addr: " << tile.getDownFace()->getAccrossFace() << std::endl;
	std::cout << " Left addr: " << tile.getDownFace()->getLeftFace() << std::endl;
	std::cout << " Right addr: " << tile.getDownFace()->getRightFace() << std::endl;

	std::cout << "UpFace addr: " << tile.getUpFace() << std::endl;
	std::cout << " Accross addr: " << tile.getUpFace()->getAccrossFace() << std::endl;
	std::cout << " Left addr: " << tile.getUpFace()->getLeftFace() << std::endl;
	std::cout << " Right addr: " << tile.getUpFace()->getRightFace() << std::endl;

	std::cout << "RightFace addr: " << tile.getRightFace() << std::endl;
	std::cout << " Accross addr: " << tile.getRightFace()->getAccrossFace() << std::endl;
	std::cout << " Left addr: " << tile.getRightFace()->getLeftFace() << std::endl;
	std::cout << " Right addr: " << tile.getRightFace()->getRightFace() << std::endl;

	std::cout << "LeftFace addr: " << tile.getLeftFace() << std::endl;
	std::cout << " Accross addr: " << tile.getLeftFace()->getAccrossFace() << std::endl;
	std::cout << " Left addr: " << tile.getLeftFace()->getLeftFace() << std::endl;
	std::cout << " Right addr: " << tile.getLeftFace()->getRightFace() << std::endl;
}

int main() {
	Tile tile1(19);
	TileStack tStack;
	tStack.shuffle();
	Board gameBoard;
	gameBoard.place_tile(std::pair<int, int>(72, 50), tile1);

	for(int i = 0; i < /**/tStack.tiles.size()/**/; i++) {
		// Get all positions that we may place the tile
		std::vector<std::pair<int,int> > availableLocations = gameBoard.display_positions(tStack.tiles[i]);
		// check if there are any available moves. If so then place at the optimal spot.
		if(availableLocations.size() > 0) {
			Tile *tmpTile = new Tile(tStack.tiles[i].getNum());
			std::pair<int,int> optimalLocation = gameBoard.getOptimalPlacement(*tmpTile, availableLocations);
			gameBoard.place_tile(optimalLocation, *tmpTile);
		}
		else {
			std::cout << "TILE " << tStack.tiles[i].getType() << " CANNOT BE PLACED" << std::endl;
			continue;
		}
	}
	printStack(tStack);
	printBoard(gameBoard);

	/**/if (gameBoard.m_board[67][47] != NULL && gameBoard.m_board[67][47]->getType() == 'e')  //debugging
	{
		//gameBoard.m_board[67][47]->getUpFace()->placeMeeple();
		std::cout << gameBoard.m_board[67][47]->getUpFace()->hasMeeple() << std::endl;
		std::cout << gameBoard.m_board[67][47]->getDownFace()->getAccrossFace()->hasMeeple() << std::endl;;
		std::cout << "Is there meeple? " << gameBoard.checkMeeplePlacement(*gameBoard.m_board[61][47]->getDownFace());
	}
	else
		std::cout << "meeple not placed" << std::endl;/**/																			//debugging

	return 0;
};
