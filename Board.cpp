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

// Returns a vector of locations <i,j> on the board where this is a tile WITH >= 1 open face
std::vector< std::pair<int, int> > Board::display_positions(Tile* tile)
{
	// Create empty vector to store possible placement locations
	std::vector< std::pair<int, int> > places;
	
	// Loop through the rows of board
	for(size_t i = 0; i < m_board.size(); i++)
	{
		// Loop through column of board
		for (size_t j = 0; j < m_board[i].size(); j++)
		{
			if (m_board[i][j].hasInit && m_board[i][j].hasOpenFace())
			{
				// Push back location of tile with at least 1 open face
				// places.push_back(std::pair<int,int>(i,j));
				std::vector< std::string> tempFaces = m_board[i][j].getOpenFaces();
				for(int k = 0; k < tempFaces.size(); k ++)
				{
					std::vector< std::pair<int, int> > tempPlacements = checkPlacement(tile, i, j, tempFaces[k]);
					places.insert(places.end(), tempPlacements.begin(), tempPlacements.end());
				}
			}
		}
	}
	return places;
}


// For each open face on the board, compare it with 
// all the faces of our new tile to see if the can link together

// Returns a location pair where the tile may be placed
std::vector< std::pair<int, int> > Board::checkPlacement(Tile* tile, int i, int j, std::string openFaces)
{
	std::vector< std::pair<int, int> > places;
	
	// if the face is the up
	if (openFaces == "up"){
		for (int ii = 0; ii < 4; ii++)
		{
			// if the bottom face of the tile were trying to place equals the top face of the tile on the board
			// and it equals the faces of all the other faces
			if (m_board[i][j].up.faceEquals(tile->down) &&
				(!m_board[i - 1][j - 1].hasInit || m_board[i - 1][j - 1].right.faceEquals(tile->left)) &&
				(!m_board[i - 1][j + 1].hasInit || m_board[i - 1][j + 1].left.faceEquals(tile->right)) &&
				(!m_board[i - 2][j].hasInit || m_board[i - 2][j].down.faceEquals(tile->up)))
			{
				places.push_back(std::pair<int, int>(i - 1, j));
				break;
			}
			tile->rotate();
		}
	}
	else if (openFaces == "down")
	{
		for (int ii = 0; ii < 4; ii++)
		{
			// same thing as above but with down
			if ((!m_board[i + 2][j].hasInit || m_board[i + 2][j].up.faceEquals(tile->down)) &&
				(!m_board[i + 1][j - 1].hasInit || m_board[i + 1][j - 1].right.faceEquals(tile->left)) &&
				(!m_board[i + 1][j + 1].hasInit || m_board[i + 1][j + 1].left.faceEquals(tile->right)) &&
				(m_board[i][j].down.faceEquals(tile->up)))
			{
				places.push_back(std::pair<int, int>(i + 1, j));
				break;
			}
			tile->rotate();
		}
	}
	else if (openFaces == "left")
	{
		for (int ii = 0; ii < 4; ii++)
		{
			// same thing as above but with left 
			if ((!m_board[i + 1][j - 1].hasInit || m_board[i + 1][j - 1].up.faceEquals(tile->down)) &&
				(!m_board[i][j - 2].hasInit || m_board[i - 1][j - 1].right.faceEquals(tile->left)) &&
				(m_board[i][j].left.faceEquals(tile->right)) &&
				(!m_board[i - 1][j - 1].hasInit || m_board[i][j - 2].down.faceEquals(tile->up)))
			{
				places.push_back(std::pair<int, int>(i, j - 1));
				break;
			}
			tile->rotate();
		}
	}
	else if (openFaces == "right")
	{
		for (int ii = 0; ii < 4; ii++)
		{
			// same thing as above but with right
			if ((!m_board[i + 1][j + 1].hasInit || m_board[i + 1][j + 1].up.faceEquals(tile->down)) &&
				(m_board[i][j].right.faceEquals(tile->left)) &&
				(!m_board[i][j + 2].hasInit || m_board[i - 1][j + 1].left.faceEquals(tile->right)) &&
				(!m_board[i - 1][j + 1].hasInit || m_board[i][j - 2].down.faceEquals(tile->up)))
			{
				places.push_back(std::pair<int, int>(i, j + 1));
				break;
			}
			tile->rotate();
		}
	}
	return places;
}


std::pair<int,int> Board::getOptimalPlacement(Tile* tile, std::vector< std::pair<int, int> > availableMoves) {
	return availableMoves[0];
}

// Place a tile on the board. Make sure all neighboring tiles are pointing to the corresponding faces
void Board::place_tile(std::pair<int, int> location, Tile& tile)
{
	tile.hasInit = true;

	int row = location.first;
	int col = location.second;
	
	m_board[row][col] = tile;

	// WE SHOULD REPLACE WITH A FUNCTION LIKE connectFaces(face1, face2) that does the mutual connection
	// between two faces rather than the method we have now. A bit cleaner and more readable code
	
	// Connect bottom face of tile to existing tile below it
	if(row+1 <= 150 && m_board[row+1][col].hasInit)
	{
		m_board[row + 1][col].up.neighborFace = &m_board[row][col].down;
		m_board[row][col].down.neighborFace = &m_board[row+1][col].up;
	}
	// Connect top face of tile to existing tile below it
	if(row-1 >= 0 && m_board[row-1][col].hasInit)
	{
		m_board[row - 1][col].down.neighborFace = &m_board[row][col].up;
		m_board[row][col].up.neighborFace = &m_board[row - 1][col].down;
	}
	// Connect left face of tile to existing tile to the left of it
	if (col - 1 >= 0 && m_board[row][col - 1].hasInit)
	{
		m_board[row][col - 1].right.neighborFace = &m_board[row][col].left;
		m_board[row][col].left.neighborFace = &m_board[row][col - 1].right;
	}
	// Connect right face of tile to the existing tile to the right of int
	if (col+1 <= 150 && m_board[row][col + 1].hasInit)
	{
		m_board[row][col + 1].left.neighborFace = &m_board[row][col].right;
		m_board[row][col].right.neighborFace = &m_board[row][col + 1].left;
	}

	// std::vector< std::string > openSpots = m_board[i][col].getOpenFaces();
	// std::cout<<"After placement, tile has open faces: ";
	// for(int i = 0; i < openSpots.size(); i++) {
	// 	std::cout<<openSpots[i]<<" "<<std::endl;
	// }
}
