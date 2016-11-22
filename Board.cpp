#include "Board.h"


Board::Board()
{
	// Initialize board to be 150x150 vector of Tiles*
	Tile *NULL_tile = NULL;
	for(int i = 0; i < 80; i++)
	{
		std::vector<Tile*> temp;
		m_board.push_back(temp);
		for(int j = 0; j < 80; j++) {
			m_board[i].push_back(NULL_tile);
		}
	}
}
Board::~Board()
{

}

// Returns a vector of locations <i,j> on the board where this tile can be placed
std::vector< std::pair<int, int> > Board::display_positions(Tile tile)
{
	// Create empty vector to store possible placement locations
	std::vector< std::pair<int, int> > places;
	// Loop through the rows of board
	for (int i = 0; i < m_board.size(); i++)
	{
		// Loop through column of board
		for (int j = 0; j < m_board[i].size(); j++)
		{
			if (m_board[i][j] != NULL && m_board[i][j]->hasOpenFace())
			{
				std::vector< std::string> tempFaces = m_board[i][j]->getOpenFaces();
				for(int k = 0; k < tempFaces.size(); k++)
				{
					std::vector< std::pair<int, int> > tempPlacements = checkPlacement(tile, i, j, tempFaces[k]);
					places.insert(places.end(), tempPlacements.begin(), tempPlacements.end());
				}
			}
		}
	}
	return places;
}

// For each open face on the board, compare it with all the faces of our new tile to see if they can link together
// Returns location pairs where the tile may be placed
std::vector< std::pair<int, int> > Board::checkPlacement(Tile tile, int i, int j, std::string openFaces)
{
	std::vector< std::pair<int, int> > places;
	if (openFaces == "up"){
		for (int ii = 0; ii < 4; ii++)
		{
			// if the bottom face of the tile we're trying to place equals the top face of the tile on the board
			// and it equals the faces of all the other surrounding tiles
			if (m_board[i][j]->getUpFace()->faceEquals(*tile.getDownFace()) &&
				 (m_board[i - 1][j - 1] == NULL || m_board[i - 1][j - 1]->getRightFace()->faceEquals(*tile.getLeftFace())) &&
				 (m_board[i - 1][j + 1] == NULL || m_board[i - 1][j + 1]->getLeftFace()->faceEquals(*tile.getRightFace())) &&
				 (m_board[i - 2][j] == NULL || m_board[i - 2][j]->getDownFace()->faceEquals(*tile.getUpFace())))
			{
				places.push_back(std::pair<int, int>(i - 1, j));
				break;
			}
			tile.rotate();
		}
	}
	else if (openFaces == "down")
	{
		for (int ii = 0; ii < 4; ii++)
		{
			// same thing as above but with down
			if ((m_board[i + 2][j] == NULL || m_board[i + 2][j]->getUpFace()->faceEquals(*tile.getDownFace())) &&
				 (m_board[i + 1][j - 1] == NULL || m_board[i + 1][j - 1]->getRightFace()->faceEquals(*tile.getLeftFace())) &&
				 (m_board[i + 1][j + 1] == NULL || m_board[i + 1][j + 1]->getLeftFace()->faceEquals(*tile.getRightFace())) &&
				 (m_board[i][j]->getDownFace()->faceEquals(*tile.getUpFace())))
			{
				places.push_back(std::pair<int, int>(i + 1, j));
				break;
			}
			tile.rotate();
		}
	}
	else if (openFaces == "left")
	{
		for (int ii = 0; ii < 4; ii++)
		{
			// same thing as above but with left
			if ((m_board[i + 1][j - 1] == NULL || m_board[i + 1][j - 1]->getUpFace()->faceEquals(*tile.getDownFace())) &&
				 (m_board[i][j - 2] == NULL || m_board[i][j - 2]->getRightFace()->faceEquals(*tile.getLeftFace())) &&
				 (m_board[i][j]->getLeftFace()->faceEquals(*tile.getRightFace())) &&
				 (m_board[i - 1][j - 1] == NULL || m_board[i - 1][j - 1]->getDownFace()->faceEquals(*tile.getUpFace())))
			{
				places.push_back(std::pair<int, int>(i, j - 1));
				break;
			}
			tile.rotate();
		}
	}
	else if (openFaces == "right")
	{
		for (int ii = 0; ii < 4; ii++)
		{
			// same thing as above but with right
			if ((m_board[i + 1][j + 1] == NULL || m_board[i + 1][j + 1]->getUpFace()->faceEquals(*tile.getDownFace())) &&
				 (m_board[i][j]->getRightFace()->faceEquals(*tile.getLeftFace())) &&
				 (m_board[i][j + 2] == NULL || m_board[i][j + 2]->getLeftFace()->faceEquals(*tile.getRightFace())) &&
				 (m_board[i - 1][j + 1] == NULL || m_board[i - 1][j + 1]->getDownFace()->faceEquals(*tile.getUpFace())))
			{
				places.push_back(std::pair<int, int>(i, j + 1));
				break;
			}
			tile.rotate();
		}
	}
	return places;
}

std::pair<int,int> Board::getOptimalPlacement(Tile &tile, std::vector< std::pair<int, int> > availableMoves) {
	for (size_t z = 0; z < availableMoves.size(); z++)
	{
		int i = availableMoves[z].first;
		int j = availableMoves[z].second;

		if ((m_board[i + 1][j] == NULL || m_board[i + 1][j]->getUpFace()->faceEquals(*tile.getDownFace())) &&
			(m_board[i - 1][j] == NULL || m_board[i - 1][j]->getDownFace()->faceEquals(*tile.getUpFace())) &&
			(m_board[i][j + 1] == NULL || m_board[i][j + 1]->getLeftFace()->faceEquals(*tile.getRightFace())) &&
			(m_board[i][j - 1] == NULL || m_board[i][j - 1]->getRightFace()->faceEquals(*tile.getLeftFace())))
		{
			return availableMoves[z];
		}
		else
		{
			tile.rotate();
		}
	}
	return availableMoves[0];
}

// Place a tile on the board. Make sure all neighboring tiles are pointing to the corresponding faces
void Board::place_tile(std::pair<int, int> location, Tile &tile)
{
	int row = location.first;
	int col = location.second;

	m_board[row][col] = &tile;
	connectFaces(row, col);
}

bool Board::checkMeeplePlacement(Face &face)
{
	std::queue<Face*> faces;
	faces.push(&face);
	while (faces.size() > 0)
	{
		if (faces.front()->hasMeeple()) { return true; }

		if (faces.front()->getAccrossFace() != NULL && !faces.front()->getAccrossFace()->hasBeenVisited())
		{
			faces.push(faces.front()->getAccrossFace());
		}

		if (faces.front()->getLeftFace() != NULL && !faces.front()->getLeftFace()->hasBeenVisited())
		{
			faces.push(faces.front()->getLeftFace());
		}

		if (faces.front()->getRightFace() != NULL && !faces.front()->getRightFace()->hasBeenVisited())
		{
			faces.push(faces.front()->getRightFace());
		}

		if (faces.front()->getNeighborFace() != NULL && !faces.front()->getNeighborFace()->hasBeenVisited())
		{
			faces.push(faces.front()->getNeighborFace());
		}

		faces.front()->visit();
		faces.pop();
	}
	return false;
}

void Board::connectFaces(int row, int col)
{
	if(row+1 <= 150 && m_board[row+1][col] != NULL &&
		 (*m_board[row+1][col]->getUpFace()).faceEquals(*m_board[row][col]->getDownFace()))
	{
		(*m_board[row + 1][col]->getUpFace()).setNeighborFace(*m_board[row][col]->getDownFace());
		(*m_board[row][col]->getDownFace()).setNeighborFace(*m_board[row + 1][col]->getUpFace());

		//std::cout << "Neighbor of the up face of " << row + 1 << ' ' << col << " is " << m_board[row + 1][col]->getUpFace()->getNeighborFace() << std::endl;
		//std::cout << "Neighbor of the down face of " << row << ' ' << col << " is " << m_board[row][col]->getDownFace()->getNeighborFace() << std::endl;
	}
	else if(m_board[row+1][col] != NULL)// && !m_board[row+1][col]->getUpFace()->faceEquals(*m_board[row][col]->getDownFace()))
	{
		std::cout << "ERROR: FACES DON'T MATCH" << std::endl;
	}
	// Connect top face of tile to existing tile above it
	if(row-1 >= 0 && m_board[row-1][col] != NULL &&
		 (*m_board[row-1][col]->getDownFace()).faceEquals(*m_board[row][col]->getUpFace()))
	{
		(*m_board[row - 1][col]->getDownFace()).setNeighborFace(*m_board[row][col]->getUpFace());
		(*m_board[row][col]->getUpFace()).setNeighborFace(*m_board[row - 1][col]->getDownFace());

		//std::cout << "Neighbor of the down face of " << row - 1 << ' ' << col << " is " << m_board[row - 1][col]->getDownFace()->getNeighborFace() << std::endl;
		//std::cout << "Neighbor of the up face of " << row << ' ' << col << " is " << m_board[row][col]->getUpFace()->getNeighborFace() << std::endl;
	}
	else if(m_board[row-1][col] != NULL)// && !m_board[row-1][col]->getDownFace()->faceEquals(*m_board[row][col]->getUpFace()))
	{
		std::cout << "ERROR: FACES DON'T MATCH" << std::endl;
	}
	// Connect left face of tile to existing tile to the left of it
	if (col-1 >= 0 && m_board[row][col-1] != NULL &&
		  (*m_board[row][col-1]->getRightFace()).faceEquals(*m_board[row][col]->getLeftFace()))
	{
		(*m_board[row][col - 1]->getRightFace()).setNeighborFace(*m_board[row][col]->getLeftFace());
		(*m_board[row][col]->getLeftFace()).setNeighborFace(*m_board[row][col - 1]->getRightFace());

		//std::cout << "Neighbor of the right face of " << row << ' ' << col - 1 << " is " << m_board[row][col - 1]->getRightFace()->getNeighborFace() << std::endl;
		//std::cout << "Neighbor of the left face of " << row << ' ' << col << " is " << m_board[row][col]->getLeftFace()->getNeighborFace() << std::endl;
	}
	else if(m_board[row][col-1] != NULL)// && !m_board[row][col-1]->getRightFace()->faceEquals(*m_board[row][col]->getLeftFace()))
	{
		std::cout << "ERROR: FACES DON'T MATCH" << std::endl;
	}
	// Connect right face of tile to the existing tile to the right of it
	if (col+1 <= 150 && m_board[row][col+1] != NULL &&
		  (*m_board[row][col+1]->getLeftFace()).faceEquals(*m_board[row][col]->getRightFace()))
	{
		(*m_board[row][col + 1]->getLeftFace()).setNeighborFace(*m_board[row][col]->getRightFace());
		(*m_board[row][col]->getRightFace()).setNeighborFace(*m_board[row][col + 1]->getLeftFace());

		//std::cout << "Neighbor of the left face of " << row << ' ' << col + 1 << " is " << m_board[row][col + 1]->getLeftFace()->getNeighborFace() << std::endl;
		//std::cout << "Neighbor of the right face of " << row << ' ' << col << " is " << m_board[row][col]->getRightFace()->getNeighborFace() << std::endl;
	}
	else if(m_board[row][col+1] != NULL )//&& !m_board[row][col+1]->getLeftFace()->faceEquals(*m_board[row][col]->getRightFace()))
	{
		std::cout << "ERROR: FACES DON'T MATCH" << std::endl;
	}
}
