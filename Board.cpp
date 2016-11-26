#include "Board.h"


Board::Board()
{
	// Initialize board to be 150x150 vector of Tiles*
	Tile *NULL_tile = NULL;
	for(int i = 0; i < 160; i++)
	{
		std::vector<Tile*> temp;
		m_board.push_back(temp);
		for(int j = 0; j < 160; j++) {
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
	for (size_t i = 0; i < m_board.size(); i++)
	{
		// Loop through column of board
		for (size_t j = 0; j < m_board[i].size(); j++)
		{
			if (m_board[i][j] != NULL && m_board[i][j]->hasOpenFace())
			{
				std::vector< std::string> tempFaces = m_board[i][j]->getOpenFaces();
				/*std::cout << "checking set of faces for <" << i << ", " << j << ">: ";
				for (int gg = 0; gg < tempFaces.size(); gg++)
				{
						std::cout << tempFaces[gg] << ", ";
				}
				std::cout<<std::endl;*/
				for (size_t k = 0; k < tempFaces.size(); k++)
				{
					// Check that the open faces for each location (and adjacent ones) may actually connect to the tile
					// Get back a vector of locations where we may place the tile
					Tile tmpTile(tile.getNum()); //couldn't figure the heck of the pointers (whoa!)
					std::vector< std::pair<int, int> > tempPlacements = checkPlacement(tmpTile, i, j, tempFaces[k]);
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
				 //std::cout<<"Can connect to up face of i,j"<<std::endl;
				// std::cout << "up face type is: " << m_board[i][j]->getUpFace()->getType() << std::endl;
				 //std::cout << "down face type of " << tile.getType() << " is: " << tile.getDownFace()->getType() << std::endl;
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
				//std::cout<<"Checking down face equals"<<m_board[i][j]->getDownFace()->faceEquals(*tile.getUpFace())<<std::endl;		//debugging
				//std::cout<<"Down face type: "<<m_board[i][j]->getDownFaceType()<<std::endl;	//debugging
				//std::cout<<"Tile up face type: "<<tile.getUpFaceType()<<std::endl;					//debugging
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
				// std::cout<<"Can connect to left face at i,j"<<std::endl;
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
				// std::cout<<"Can connect to right face at i,j"<<std::endl;
				places.push_back(std::pair<int, int>(i, j + 1));
				break;
			}
			tile.rotate();
		}
	}
	return places;
}

std::pair<int,int> Board::getOptimalPlacement(Tile &tile, std::vector< std::pair<int, int> > availableMoves) {
	 if (availableMoves.size() > 1)
	 {
	 	int bestRotation = 0;
	 	std::pair<int, int> bestSpot;
	 	int mostPoints = -2;
	 	for (size_t z = 0; z < availableMoves.size(); z++)
	 	{
			int i = availableMoves[z].first;
	 		int j = availableMoves[z].second;
	 		for (int q = 0; q < 4; q++)
	 		{
	 			int points = 0;
	 			if ((m_board[i + 1][j] == NULL || m_board[i + 1][j]->getUpFace()->faceEquals(*tile.getDownFace())) &&
	 				(m_board[i - 1][j] == NULL || m_board[i - 1][j]->getDownFace()->faceEquals(*tile.getUpFace())) &&
	 				(m_board[i][j + 1] == NULL || m_board[i][j + 1]->getLeftFace()->faceEquals(*tile.getRightFace())) &&
	 				(m_board[i][j - 1] == NULL || m_board[i][j - 1]->getRightFace()->faceEquals(*tile.getLeftFace())))
	 			{
	 				points = positionPoints(i, j);
					//std::cout << "triggered points are: " << points << std::endl;
	 			}
	 			else
	 			{
	 				points = -1;
	 			}
	 			if (points > mostPoints)
	 			{
	 				mostPoints = points;
	 				bestSpot = availableMoves[z];
	 				bestRotation = q;
	 			}
				/*else
				{
					bestSpot = availableMoves[z]; //what the heck, we need this otherwise if better points are not reached we won't have a place to put the tile
				}*/
	 			tile.rotate();
				//std::cout << "triggered3" << std::endl;
	 		}
	 	}
	 	for (int i = 0; i < bestRotation; i++)
	 	{
	 		tile.rotate();
	 	}
		//std:: cout << "final trigger for optimal, best spot at " << bestSpot.first << ", " << bestSpot.second << std::endl;
	 	return bestSpot;
	 }
	 else
	 {
	 	int i = availableMoves[0].first;
	 	int j = availableMoves[0].second;
	 	for (int q = 0; q < 4; q++)
	 	{
	 		if ((m_board[i + 1][j] == NULL || m_board[i + 1][j]->getUpFace()->faceEquals(*tile.getDownFace())) &&
	 			(m_board[i - 1][j] == NULL || m_board[i - 1][j]->getDownFace()->faceEquals(*tile.getUpFace())) &&
	 			(m_board[i][j + 1] == NULL || m_board[i][j + 1]->getLeftFace()->faceEquals(*tile.getRightFace())) &&
	 			(m_board[i][j - 1] == NULL || m_board[i][j - 1]->getRightFace()->faceEquals(*tile.getLeftFace())))
	 		{
	 			//std::cout << "Location " << i << ' ' << j << " passed optimalPlacement checks of connecting to all surrounding tiles" << std::endl;
	 			break;
	 		}
	 		else
	 		{
	 			tile.rotate();
	 		}
	 	}
	 	return availableMoves[0];
	 }
	//return availableMoves[0]; //this is redundant
}

int Board::positionPoints(int i, int j)
{
	const int LAKE_POINTS = 6;
	const int JUNGLE_POINTS = 3;
	const int TRAIL_POINTS = 1;

	int points = 0;
	if (m_board[i + 1][j] != NULL)
	{
		points += animalPoints(i + 1, j);
		if (m_board[i + 1][j]->getUpFace()->getType() == "lake")
		{
			points += LAKE_POINTS;
		}
		else if (m_board[i + 1][j]->getUpFace()->getType() == "jungle")
		{
			points += JUNGLE_POINTS;
		}
		else if (m_board[i + 1][j]->getUpFace()->getType() == "trail")
		{
			points += TRAIL_POINTS;
		}
	}
	if (m_board[i - 1][j] != NULL)
	{
		points += animalPoints(i - 1, j);
		if (m_board[i - 1][j]->getDownFace()->getType() == "lake")
		{
			points += LAKE_POINTS;
		}
		else if (m_board[i - 1][j]->getDownFace()->getType() == "jungle")
		{
			points += JUNGLE_POINTS;
		}
		else if (m_board[i - 1][j]->getDownFace()->getType() == "trail")
		{
			points += TRAIL_POINTS;
		}
	}
	if (m_board[i][j + 1] != NULL)
	{
		points += animalPoints(i, j + 1);
		if (m_board[i][j + 1]->getLeftFace()->getType() == "lake")
		{
			points += LAKE_POINTS;
		}
		else if (m_board[i][j + 1]->getLeftFace()->getType() == "jungle")
		{
			points += JUNGLE_POINTS;
		}
		else if (m_board[i][j + 1]->getLeftFace()->getType() == "trail")
		{
			points += TRAIL_POINTS;
		}
	}
	if (m_board[i][j - 1] != NULL)
	{
		points += animalPoints(i, j - 1);
		if (m_board[i][j - 1]->getRightFace()->getType() == "lake")
		{
			points += LAKE_POINTS;
		}
		else if (m_board[i][j - 1]->getRightFace()->getType() == "jungle")
		{
			points += JUNGLE_POINTS;
		}
		else if (m_board[i][j - 1]->getRightFace()->getType() == "trail")
		{
			points += TRAIL_POINTS;
		}
	}
	return points;
}

int Board::animalPoints(int i, int j)
{
	const int DEN_POINTS = 10;
	const int DEER_POINTS = 2;
	const int BOAR_POINTS = 2;
	const int BUFFALO_POINTS = 2;
	const int CROCODILE_POINTS = -2;
	int points = 0;
	if (m_board[i][j]->getCenter().getType() == "Den")
	{
		points += DEN_POINTS;
	}
	if (m_board[i][j]->hasBoar())
	{
		points += BOAR_POINTS;
	}
	if (m_board[i][j]->hasBuffalo())
	{
		points += BUFFALO_POINTS;
	}
	if (m_board[i][j]->hasDeer())
	{
		points += DEER_POINTS;
	}
	if (m_board[i][j]->hasCrocodile())
	{
		points += CROCODILE_POINTS;
	}
	return points;
}

// Place a tile on the board. Make sure all neighboring tiles are pointing to the corresponding faces
void Board::place_tile(std::pair<int, int> location, Tile &tile)
{
	int row = location.first;
	int col = location.second;

	m_board[row][col] = &tile;
	connectFaces(row, col);

	/*std::vector< std::string> tempFaces = m_board[row][col]->getOpenFaces();
	std::cout << "checking set of open faces for <" << m_board[row][col]->getType() << ">: ";
	for (int gg = 0; gg < tempFaces.size(); gg++)
	{
			std::cout << tempFaces[gg] << ", ";
	}
	std::cout<<std::endl;*/
}

bool Board::checkMeeplePlacement(Tile tile, std::pair<int,int> blockSpot)
{
	std::vector< std::vector<Block> > innerBlocks = tile.getInnerBlocks();
	Block block = innerBlocks[blockSpot.first][blockSpot.second];
	if (block.hasMeeple()) { return true; }
	else if (block.getType() == "lake" || block.getType() == "trail")
	{
		if (blockSpot.first == 0)
			return traverseTrailOrLakes(*tile.getUpFace());
		else if (blockSpot.first == 2)
			return traverseTrailOrLakes(*tile.getDownFace());
		else if (blockSpot.second == 0)
			return traverseTrailOrLakes(*tile.getLeftFace());
		else if (blockSpot.second == 2)
			return traverseTrailOrLakes(*tile.getRightFace());
		else
		{
			std::cout << "NO OPTION TRIGGERED TO FIND MEEPLE" << std::endl;
			return false;
		}
	}
	else if (block.getType() == "den")
		return block.hasMeeple();
	else
	{
		std::cout << "NO OPTION TRIGGERED TO FIND MEEPLE" << std::endl;
		return false;
	}
	//else if (block.getType() == "jungle" || block.getType() == "mixed")
		//return traverseJungle(tile, blockSpot);
}
/*So you can use the blocks in a tile to find all of the parts of a tile in the same feature,
To do this i have a queue of blocks and i find all of the adjacent blocks of the blocks your searching from that are the same type,
the problem comes in when youre traversing to a new tile since the blocks dont have any connections to anything else
i could add a queue of tiles and push tiles onto that queue if you traverse to them from the blocks
but then im not sure how i would hold that information for the new blocks of that tile in relation to the existing queue
instead of having a queue of tiles i could recall the function again and have it run the same process on the tiles on whatever block you move onto it from
the problem there is how to remember which tiles youve already visited and which blocks youve visted in those tiles
*/

/*/bool Board::checkJungle(Tile tile, std::pair<int, int> blockSpot)
{
	string TYPE1 = "jungle";
	string TYPE2 = "mixed";
	int i = blockSpot.first;
	int j = blockSpot.second;;
	tile.getInnerBlocks()[i][j].visit();

	if (tile.getInnerBlocks()[i][j].hasMeeple())
		return true;
	if ((i+1 <= 2) && (tile.getInnerBlocks()[i+1][j] == TYPE1 || tile.getInnerBlocks()[i+1][j] == TYPE2) &&
			!tile.getInnerBlocks()[i+1][j].hasBeenVisited())
	{ //get immediate block below
		std::pair<int, int> spot (i+1,j);
		if (checkJungle(tile, spot))
			return true;
	}
	else if ((i+1 > 2) && (tile.getNeighborTileBelow() != NULL))
	{ //get immediate block below from neighbor tile
		std::pair<int, int> spot (0,j);
		if (checkJungle(*tile.getNeighborTileBelow(), spot))
			return true;
	}
	if ((i-1 >= 0) && (tile.getInnerBlocks()[i-1][j] == TYPE1 || tile.getInnerBlocks()[i-1][j] == TYPE2) &&
			!tile.getInnerBlocks()[i-1][j].hasBeenVisited())
	{ //get immediate block above
		std::pair<int, int> spot (i-1,j);
		if (checkJungle(tile, spot))
			return true;
	}
	else if ((i-1 < 0) && (tile.getNeighborTileAbove() != NULL))
	{ //get immediate block above from neighbor tile
		std::pair<int, int> spot (2,j);
		if (checkJungle(*tile.getNeighborTileAbove(), spot))
			return true;
	}
	if ((j+1 <= 2) && (tile.getInnerBlocks()[i][j+1] == TYPE1 || tile.getInnerBlocks()[i][j+1] == TYPE2) &&
			!tile.getInnerBlocks()[i][j+1].hasBeenVisited())
	{ //get immediate block to the right
		std::pair<int, int> spot (i,j+1);
		if (checkJungle(tile, spot))
			return true;
	}
	else if ((j+1 > 2) && (tile.getNeighborTileRight() != NULL))
	{ //get immediate block to the right from the neighbor tile
		std::pair<int, int> spot (i, 0);
		if (checkJungle(*tile.getNeighborTileRight(), spot))
			return true;
	}
	if ((j-1 >= 0) && (tile.getInnerBlocks()[i][j-1] == TYPE1 || tile.getInnerBlocks()[i][j-1] == TYPE2) &&
			!tile.getInnerBlocks()[i][j-1].hasBeenVisited())
	{ //get immediate block to the left
		std::pair<int, int> spot (i,j-1);
		if (checkJungle(tile, spot))
			return true;
	}
	else if ((j-1 < 0) && (tile.getNeighborTileLeft() != NULL))
	{
		std::pair<int, int> spot (i,2);
		if (checkJungle(*tile.getNeighborTileLeft(), spot))
			return true;
	}
	return false;
}


bool Board::checkLake(Tile tile, std::pair<int, int> blockSpot)
{
	string TYPE1 = "lake";
	int i = blockSpot.first;
	int j = blockSpot.second;;
	tile.getInnerBlocks()[i][j].visit();

	if (tile.getInnerBlocks()[i][j].hasMeeple())
		return true;
	if ((i+1 <= 2) && (tile.getInnerBlocks()[i+1][j] == TYPE1) &&
			!tile.getInnerBlocks()[i+1][j].hasBeenVisited())
	{ //get immediate block below
		std::pair<int, int> spot (i+1,j);
		if (checkLake(tile, spot))
			return true;
	}
	else if ((i+1 > 2) && (tile.getNeighborTileBelow() != NULL))
	{ //get immediate block below from neighbor tile
		std::pair<int, int> spot (0,j);
		if (checkJungle(*tile.getNeighborTileBelow(), spot))
			return true;
	}
	if ((i-1 >= 0) && (tile.getInnerBlocks()[i-1][j] == TYPE1 || tile.getInnerBlocks()[i-1][j] == TYPE2) &&
			!tile.getInnerBlocks()[i-1][j].hasBeenVisited())
	{ //get immediate block above
		std::pair<int, int> spot (i-1,j);
		if (checkJungle(tile, spot))
			return true;
	}
	else if ((i-1 < 0) && (tile.getNeighborTileAbove() != NULL))
	{ //get immediate block above from neighbor tile
		std::pair<int, int> spot (2,j);
		if (checkJungle(*tile.getNeighborTileAbove(), spot))
			return true;
	}
	if ((j+1 <= 2) && (tile.getInnerBlocks()[i][j+1] == TYPE1 || tile.getInnerBlocks()[i][j+1] == TYPE2) &&
			!tile.getInnerBlocks()[i][j+1].hasBeenVisited())
	{ //get immediate block to the right
		std::pair<int, int> spot (i,j+1);
		if (checkJungle(tile, spot))
			return true;
	}
	else if ((j+1 > 2) && (tile.getNeighborTileRight() != NULL))
	{ //get immediate block to the right from the neighbor tile
		std::pair<int, int> spot (i, 0);
		if (checkJungle(*tile.getNeighborTileRight(), spot))
			return true;
	}
	if ((j-1 >= 0) && (tile.getInnerBlocks()[i][j-1] == TYPE1 || tile.getInnerBlocks()[i][j-1] == TYPE2) &&
			!tile.getInnerBlocks()[i][j-1].hasBeenVisited())
	{ //get immediate block to the left
		std::pair<int, int> spot (i,j-1);
		if (checkJungle(tile, spot))
			return true;
	}
	else if ((j-1 < 0) && (tile.getNeighborTileLeft() != NULL))
	{
		std::pair<int, int> spot (i,2);
		if (checkJungle(*tile.getNeighborTileLeft(), spot))
			return true;
	}

	return false;
}

bool Board::checkTrail(Tile tile, std::pair<int, int> blockSpot)
{

}*/

bool Board::traverseTrailOrLakes(Face &face)
{
	std::queue<Face*> faces;
	std::queue<Face*> resetFaces;
	faces.push(&face);
	while (faces.size() > 0)
	{
		if (faces.front()->hasMeeple()) {
			while (resetFaces.size() > 0)
			{
				resetFaces.front()->resetVisitation();
				resetFaces.pop();
			}
			return true;
		}

		if (faces.front()->getAcrossFace() != NULL && !faces.front()->getAcrossFace()->hasBeenVisited())
		{
			resetFaces.push(faces.front()->getAcrossFace());
			faces.push(faces.front()->getAcrossFace());
		}

		if (faces.front()->getLeftFace() != NULL && !faces.front()->getLeftFace()->hasBeenVisited())
		{
			resetFaces.push(faces.front()->getLeftFace());
			faces.push(faces.front()->getLeftFace());
		}

		if (faces.front()->getRightFace() != NULL && !faces.front()->getRightFace()->hasBeenVisited())
		{
			resetFaces.push(faces.front()->getRightFace());
			faces.push(faces.front()->getRightFace());
		}

		if (faces.front()->getNeighborFace() != NULL && !faces.front()->getNeighborFace()->hasBeenVisited())
		{
			resetFaces.push(faces.front()->getNeighborFace());
			faces.push(faces.front()->getNeighborFace());
		}

		faces.front()->visit();
		faces.pop();
	}
	while (resetFaces.size() > 0)
	{
		resetFaces.front()->resetVisitation();
		resetFaces.pop();
	}
	return false;
}

void Board::connectFaces(int row, int col)
{
	//std::cout << "triger1" << std::endl;
	if(row+1 <= 150 && m_board[row+1][col] != NULL &&
		 (*m_board[row+1][col]->getUpFace()).faceEquals(*m_board[row][col]->getDownFace()))
	{
		//std::cout << "triger2" << std::endl;
		(*m_board[row + 1][col]->getUpFace()).setNeighborFace(*m_board[row][col]->getDownFace());
		(*m_board[row][col]->getDownFace()).setNeighborFace(*m_board[row + 1][col]->getUpFace());
		m_board[row][col]->setNeighborTileBelow(*m_board[row+1][col]);
		m_board[row+1][col]->setNeighborTileAbove(*m_board[row][col]);

		//std::cout << "Neighbor of the up face of " << row + 1 << ' ' << col << " is " << m_board[row + 1][col]->getUpFace()->getNeighborFace() << std::endl;
		//std::cout << "Neighbor of the down face of " << row << ' ' << col << " is " << m_board[row][col]->getDownFace()->getNeighborFace() << std::endl;
	}
	else if(m_board[row+1][col] != NULL)// && !m_board[row+1][col]->getUpFace()->faceEquals(*m_board[row][col]->getDownFace()))
	{
		//std::cout<<"Down face type: "<<m_board[row][col]->getDownFaceType()<<std::endl;	//debugging
		//std::cout<<"Tile up face type: "<<m_board[row+1][col]->getUpFaceType()<<std::endl;					//debugging
		std::cout << "ERROR: FACES DON'T MATCH for tile down face" << std::endl;
	}

	// Connect top face of tile to existing tile above it
	if(row-1 >= 0 && m_board[row-1][col] != NULL &&
		 (*m_board[row-1][col]->getDownFace()).faceEquals(*m_board[row][col]->getUpFace()))
	{
		//std::cout << "it entered" << std::endl;
		(*m_board[row - 1][col]->getDownFace()).setNeighborFace(*m_board[row][col]->getUpFace());
		(*m_board[row][col]->getUpFace()).setNeighborFace(*m_board[row - 1][col]->getDownFace());
		m_board[row][col]->setNeighborTileAbove(*m_board[row-1][col]);
		m_board[row-1][col]->setNeighborTileBelow(*m_board[row][col]);

		//std::cout << "it exited" << std::endl;
		//std::cout << "Neighbor of the down face of " << row - 1 << ' ' << col << " is " << m_board[row - 1][col]->getDownFace()->getNeighborFace() << std::endl;
		//std::cout << "Neighbor of the up face of " << row << ' ' << col << " is " << m_board[row][col]->getUpFace()->getNeighborFace() << std::endl;
	}
	else if(m_board[row-1][col] != NULL)// && !m_board[row-1][col]->getDownFace()->faceEquals(*m_board[row][col]->getUpFace()))
	{
		std::cout << "ERROR: FACES DON'T MATCH for tile up face" << std::endl;
	}

	// Connect left face of tile to existing tile to the left of it
	if (col-1 >= 0 && m_board[row][col-1] != NULL &&
		  (*m_board[row][col-1]->getRightFace()).faceEquals(*m_board[row][col]->getLeftFace()))
	{
		(*m_board[row][col - 1]->getRightFace()).setNeighborFace(*m_board[row][col]->getLeftFace());
		(*m_board[row][col]->getLeftFace()).setNeighborFace(*m_board[row][col - 1]->getRightFace());
		m_board[row][col]->setNeighborTileLeft(*m_board[row][col-1]);
		m_board[row][col-1]->setNeighborTileRight(*m_board[row][col]);

		//std::cout << "Neighbor of the right face of " << row << ' ' << col - 1 << " is " << m_board[row][col - 1]->getRightFace()->getNeighborFace() << std::endl;
		//std::cout << "Neighbor of the left face of " << row << ' ' << col << " is " << m_board[row][col]->getLeftFace()->getNeighborFace() << std::endl;
	}
	else if(m_board[row][col-1] != NULL)// && !m_board[row][col-1]->getRightFace()->faceEquals(*m_board[row][col]->getLeftFace()))
	{
		std::cout << "ERROR: FACES DON'T MATCH for tile left face" << std::endl;
	}
	//	std::cout << "triger5" << std::endl;
	// Connect right face of tile to the existing tile to the right of it
	if (col+1 <= 150 && m_board[row][col+1] != NULL &&
		  (*m_board[row][col+1]->getLeftFace()).faceEquals(*m_board[row][col]->getRightFace()))
	{
		(*m_board[row][col + 1]->getLeftFace()).setNeighborFace(*m_board[row][col]->getRightFace());
		(*m_board[row][col]->getRightFace()).setNeighborFace(*m_board[row][col + 1]->getLeftFace());
		m_board[row][col]->setNeighborTileRight(*m_board[row][col+1]);
		m_board[row][col+1]->setNeighborTileBelow(*m_board[row][col]);

		//std::cout << "Neighbor of the left face of " << row << ' ' << col + 1 << " is " << m_board[row][col + 1]->getLeftFace()->getNeighborFace() << std::endl;
		//std::cout << "Neighbor of the right face of " << row << ' ' << col << " is " << m_board[row][col]->getRightFace()->getNeighborFace() << std::endl;
	}
	else if(m_board[row][col+1] != NULL )//&& !m_board[row][col+1]->getLeftFace()->faceEquals(*m_board[row][col]->getRightFace()))
	{
		std::cout << "ERROR: FACES DON'T MATCH for tile right face" << std::endl;
	}
}
