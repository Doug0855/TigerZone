#include <iostream>
#include <utility>
#include <fstream>
#include <iomanip>

#include "Tile_Structure/Tile.h"
#include "Tile_Structure/Block.h"
#include "Tile_Structure/Face.h"
#include "Tile_Structure/TileStack.h"
//#include "Meeple.h"
#include "Game.h"
#include "Board.h"

#define WHITE   "\033[37m"      /* White */
#define BLUE    "\033[34m"      /* Blue */
#define GREEN   "\033[32m"      /* Green */
#define RED     "\033[31m"      /* Red */
#define BLACK   "\033[30m"      /* Black */
#define RESET   "\033[0m"       /* Reset */
#define BOLD    "\033[1m"       /* Bold */
#define INVERT  "\033[7m"       /* Invert */

void printToTextFile(Board gameboard)
{
	std::ofstream out_data("Levels/level.txt");
	out_data << "Level:" << std::endl;
	for (auto& inner : gameboard.m_board)
	{
		for (auto& item : inner)
		{
			if (item != NULL)
				out_data << item->getRotations() << item->getType();
			else
				out_data << '0' << '.';

		}
		out_data << std::endl;
	}
	out_data.close();
}
void printBoard(Board gameBoard) //debugging
{
	std::cout<<"in print board"<<std::endl;
	// Print out gameboard
	std::cout << "size of gameBoard is: " << gameBoard.m_board.size() << " x " << gameBoard.m_board[0].size() << std::endl;
	std::cout << "    ";
	for(int i = 38; i < gameBoard.m_board.size()-60; i++)
	{
		std::cout << std::setw(2) << i;
	}
	std::cout<<std::endl;
	for(int i = 38; i < gameBoard.m_board.size()-60; i++)
	{
		std::cout << std::setw(3) << i << ' ';
		for(int j = 38; j < gameBoard.m_board[i].size()-60; j++)
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
/*void printTileAdddresses(Tile &tile) //debugging
{
		std::cout << "DownFace addr: " << tile.getDownFace() << std::endl;
		std::cout << " Accross addr: " << tile.getDownFace()->getAcrossFace() << std::endl;
		std::cout << " Left addr: " << tile.getDownFace()->getLeftFace() << std::endl;
		std::cout << " Right addr: " << tile.getDownFace()->getRightFace() << std::endl;

		std::cout << "UpFace addr: " << tile.getUpFace() << std::endl;
		std::cout << " Across addr: " << tile.getUpFace()->getAcrossFace() << std::endl;
		std::cout << " Left addr: " << tile.getUpFace()->getLeftFace() << std::endl;
		std::cout << " Right addr: " << tile.getUpFace()->getRightFace() << std::endl;

		std::cout << "RightFace addr: " << tile.getRightFace() << std::endl;
		std::cout << " Across addr: " << tile.getRightFace()->getAcrossFace() << std::endl;
		std::cout << " Left addr: " << tile.getRightFace()->getLeftFace() << std::endl;
		std::cout << " Right addr: " << tile.getRightFace()->getRightFace() << std::endl;

		std::cout << "LeftFace addr: " << tile.getLeftFace() << std::endl;
		std::cout << " Across addr: " << tile.getLeftFace()->getAcrossFace() << std::endl;
		std::cout << " Left addr: " << tile.getLeftFace()->getLeftFace() << std::endl;
		std::cout << " Right addr: " << tile.getLeftFace()->getRightFace() << std::endl;
}*/
void printTile(Tile tile)
{
	tile.rotate();
	std::cout << "printing tile info: " << std::endl;

	std::cout << tile.innerBlocks[0][0].getType() << ", " << tile.innerBlocks[0][1].getType() << ", " << tile.innerBlocks[0][2].getType() << std::endl;
	std::cout << tile.innerBlocks[1][0].getType() << ", " << tile.innerBlocks[1][1].getType() << ", " << tile.innerBlocks[1][2].getType() << std::endl;
	std::cout << tile.innerBlocks[2][0].getType() << ", " << tile.innerBlocks[2][1].getType() << ", " << tile.innerBlocks[2][2].getType() << std::endl;

	std::cout << "up face of tile is " << tile.getUpFace()->getType() << std::endl;
	std::cout << "left face of tile is " << tile.getLeftFace()->getType() << std::endl;
	std::cout << "right face of tile is " << tile.getRightFace()->getType() << std::endl;
	std::cout << "down face of tile is " << tile.getDownFace()->getType() << std::endl;
}
int main() {
	Board gameBoard;
	std::cout<<"in game"<<std::endl;
	Tile tile1(19);
	//printTile(tile1);
	TileStack tStack;
	for (int i=0;i<2;i++)
		tStack.shuffle();
	Player p1;
	Player p2;
	//std::cout<<"tile 1 up face is "<<tile1.getUpFace()->getType()<<std::endl;			//debugging
	gameBoard.place_tile(std::pair<int, int>(72,72), tile1);
	Game game1("123", p1, p2, tStack, tile1, std::pair<int,int> (72,72));
	game1.play();
	/*
	Tile *tmpTile = new Tile(tStack.tiles[0].getNum());
	gameboard.place_tile(std::pair<int,int>(72,71), *tmpTile);

	std::vector<std::pair<int, int> > availableLocations = gameboard.display_positions(tStack.tiles[1]);
	std::cout<<"there are "<<availableLocations.size()<<" available locations for tile "<<tStack.tiles[1].getType()<<std::endl;
	for(int i = 0; i < availableLocations.size(); i++) {
		std::cout<<i<<") "<<availableLocations[i].first<<' '<<availableLocations[i].second<<std::endl;
	}
	*/
	//printStack(tStack);
	//printBoard(game1.gameboard);

	for(int i = 0; i < /**/tStack.tiles.size()/**/; i++) {
		// Get all positions that we may place the tile
		//std::cout << "placing tyle of type: " << tStack.tiles[i].getType() << std::endl; //debugging
		//if (tStack.tiles[i].getType() == 'h')
		//	printTile(tStack.tiles[i]);
		std::vector<std::pair<int,int> > availableLocations = gameBoard.display_positions(tStack.tiles[i]);
		// check if there are any available moves. If so then place at the optimal spot.
		/*for (int i = 0; i < availableLocations.size(); i++) //debugging
		{
			std::cout << "pair " << i << ": " << availableLocations[i].first << ", " << availableLocations[i].second << std::endl;
		}	*/																									//debugging
		if(availableLocations.size() > 0) {
			Tile *tmpTile = new Tile(tStack.tiles[i].getNum());
			std::pair<int,int> optimalLocation = gameBoard.getOptimalPlacement(*tmpTile, availableLocations);
			//std::cout << "optimal placement obtained, about to place_tile" << std::endl;
			//std::cout << "optimal location at: <" << optimalLocation.first << ", " << optimalLocation.second << ">" << std::endl;
			gameBoard.place_tile(optimalLocation, *tmpTile);
			//std::cout << "tile successfully placed" << std::endl;
		}
		else {
			std::cout << "TILE " << tStack.tiles[i].getType() << " CANNOT BE PLACED" << std::endl;
			continue;
		}
	}
	printStack(tStack);
	printBoard(gameBoard);
	//printToTextFile(gameBoard);

	/**/if (gameBoard.m_board[67][77] != NULL)  //debugging
	{
		gameBoard.m_board[67][77]->innerBlocks[1][0].placeMeeple();
		std::cout << gameBoard.m_board[67][77]->getLeftFace()->hasMeeple() << std::endl;
		//std::cout << gameBoard.m_board[67][77]->getDownFace()->hasMeeple() << std::endl;
		//std::cout << gameBoard.m_board[67][77]->getDownFace()->getAcrossFace()->hasMeeple() << std::endl;;
		std::pair<int, int> spot (2,1);
		std::cout << "Is there meeple? " << gameBoard.checkMeeplePlacement(*gameBoard.m_board[66][76], spot);
	}
	else
		std::cout << "meeple not placed" << std::endl;/**/																			//debugging
	//int z;
	//std::cin >> z;

	return 0;
};
