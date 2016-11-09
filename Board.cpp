#include "Board.h"
#include <iostream>
#include <utility>

Board::Board()
{
	// Initialize board to be 150x150 matrix of Tiles
	for(int i = 0; i < 150; i++)
	{
		std::vector<Tile> v(10);
		m_board.push_back(v);
		for(int j = 0; j < 150; j++)
		{
			Tile boardTile;
			m_board[i].push_back(boardTile);
		}
	}
}

Board::~Board()
{
	
}

std::string Board::to_string(void)
{
	return "empty";
}

std::vector< std::pair<int, int> > Board::display_positions(Tile tile)
{
	std::vector< std::pair<int, int> > places;
	// Loop through the rows of board
	for(size_t i = 0; i < m_board.size(); i++)
	{
		// Loop through column of board
		for (size_t j = 0; j < m_board[i].size(); j++)
		{
			if (m_board[i][j].hasInit && m_board[i][j].hasOpenFace())
			{
				// get all the open faces for the tile on the board
				std::vector<std::string> openFaces = m_board[i][j].getOpenFaces();
				// loop through all the open faces
				for(size_t k = 0; k < openFaces.size(); k++)
				{
					// see which face is open for the tile on the board
					std::vector< std::pair<int, int> > tmp = checkPlacement(&tile, i, j, openFaces[k]);
					places.insert(places.end(), tmp.begin(), tmp.end());			
				}
			}
		}
	}
	return places;
}

std::pair<int,int> getOptimalPlacement(Tile* tile, std::vector< std::pair<int, int> > availableMoves) {
	return availableMoves[0];
}

void Board::place_tile(std::pair<int, int> location, Tile tile)
{
	tile.hasInit = true;

	int i = location.first;
	int j = location.second;
	
	m_board[i][j] = tile;
	
	// Connect bottom face of tile to existing tile below it
	if(m_board[i+1][j].hasInit)
	{
		std::cout<<"A tile exists below the placement of this one"<<std::endl;
		m_board[i+1][j].up.neighborFace = &tile.down;
		std::cout<<"Connected to down face"<<std::endl;
		tile.down.neighborFace = &m_board[i + 1][j].up;
		bool isConnect = (tile.down.neighborFace->faceEquals(m_board[i + 1][j].up));
		if(isConnect) { std::cout<< "Connected"; }
	}
	// Connect top face of tile to existing tile above it
	if(m_board[i-1][j].hasInit)
	{
		*m_board[i-1][j].down.neighborFace = tile.getUpFace();
		*tile.up.neighborFace = m_board[i - 1][j].getDownFace();
	}
	// Connect left face of tile to existing tile to the left of it
	if (m_board[i][j - 1].hasInit)
	{
		*m_board[i][j-1].right.neighborFace = tile.getLeftFace();
		*tile.left.neighborFace = m_board[i][j - 1].getRightFace();
	}
	// Connect right face of tile to the existing tile to the right of int
	if (m_board[i][j + 1].hasInit)
	{
		*m_board[i][j+1].left.neighborFace = tile.getRightFace();
		*tile.right.neighborFace = m_board[i][j + 1].getLeftFace();
	}
}

std::vector< std::pair<int, int> > Board::checkPlacement(Tile* tile, int i, int j, std::string openFaces)
{
	std::vector< std::pair<int, int> > places;
		// if the face is the up face compare the down face of the tile were trying to place
	if (openFaces == "up"){
		for (int ii = 0; ii < 3; ii++)
		{
			// if the botton face of the tile were trying to place equals the top face of the tile on the board
			// and it equals the faces of all the other faces
			if (m_board[i][j].getUpFace().faceEquals(tile->getDownFace()) &&
				(m_board[i - 1][j - 1].hasInit || m_board[i - 1][j - 1].getRightFace().faceEquals(tile->getLeftFace())) &&
				(m_board[i - 1][j + 1].hasInit || m_board[i - 1][j + 1].getLeftFace().faceEquals(tile->getRightFace())) &&
				(m_board[i - 2][j].hasInit || m_board[i - 2][j].getDownFace().faceEquals(tile->getUpFace())))
			{
				places.push_back(std::pair<int, int>(i - 1, j));
				break;
			}
			tile->rotate();
		}
	}
	else if (openFaces == "down")
	{
		for (int ii = 0; ii < 3; ii++)
		{
			// same thing as above but with down
			if ((m_board[i + 2][j].hasInit || m_board[i + 2][j].getUpFace().faceEquals(tile->getDownFace())) &&
				(m_board[i + 1][j - 1].hasInit || m_board[i + 1][j - 1].getRightFace().faceEquals(tile->getLeftFace())) &&
				(m_board[i + 1][j + 1].hasInit || m_board[i + 1][j + 1].getLeftFace().faceEquals(tile->getRightFace())) &&
				(m_board[i][j].getDownFace().faceEquals(tile->getUpFace())))
			{
				places.push_back(std::pair<int, int>(i + 1, j));
				break;
			}
			tile->rotate();
		}
	}
	else if (openFaces == "left")
	{
		for (int ii = 0; ii < 3; ii++)
		{
			// same thing as above but with left 
			if ((m_board[i + 1][j - 1].hasInit || m_board[i + 1][j - 1].getUpFace().faceEquals(tile->getDownFace())) &&
				(m_board[i][j - 2].hasInit || m_board[i - 1][j - 1].getRightFace().faceEquals(tile->getLeftFace())) &&
				(m_board[i][j].getLeftFace().faceEquals(tile->getRightFace())) &&
				(m_board[i - 1][j - 1].hasInit || m_board[i][j - 2].getDownFace().faceEquals(tile->getUpFace())))
			{
				places.push_back(std::pair<int, int>(i, j - 1));
				break;
			}
			tile->rotate();
		}
	}
	else if (openFaces == "right")
	{
		for (int ii = 0; ii < 3; ii++)
		{
			// same thing as above but with right
			if ((m_board[i + 1][j + 1].hasInit || m_board[i + 1][j + 1].getUpFace().faceEquals(tile->getDownFace())) &&
				(m_board[i][j].getRightFace().faceEquals(tile->getLeftFace())) &&
				(m_board[i][j + 2].hasInit || m_board[i - 1][j + 1].getLeftFace().faceEquals(tile->getRightFace())) &&
				(m_board[i - 1][j + 1].hasInit || m_board[i][j - 2].getDownFace().faceEquals(tile->getUpFace())))
			{
				places.push_back(std::pair<int, int>(i, j + 1));
				break;
			}
			tile->rotate();
		}
	}
	return places;
}
