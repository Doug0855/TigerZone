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
				for (size_t k = 0; k < tempFaces.size(); k++)
				{
					// Check that the open faces for each location (and adjacent ones) may actually connect to the tile
					// Get back a vector of locations where we may place the tile
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
	// std::cout<<"Checking placement for tile "<<tile.getType()<<" based off location "<<i<<' '<<j<<std::endl;
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
				// std::cout<<"Can connect to up face of i,j"<<std::endl;
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
				std::cout<<"Checking down face equals"<<m_board[i][j]->getDownFace()->faceEquals(*tile.getUpFace())<<std::endl;
				std::cout<<"Down face type: "<<m_board[i][j]->getDownFaceType()<<std::endl;
				std::cout<<"Tile up face type: "<<tile.getUpFaceType()<<std::endl;
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
	 	int mostPoints = 0;
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
	 			tile.rotate();
	 		}
	 	}
	 	for (int i = 0; i < bestRotation; i++)
	 	{
	 		tile.rotate();
	 	}
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
	 			std::cout << "Location " << i << ' ' << j << " passed optimalPlacement checks of connecting to all surrounding tiles" << std::endl;
	 			break;
	 		}
	 		else
	 		{
	 			tile.rotate();
	 		}
	 	}
	 	return availableMoves[0];
	 }
	return availableMoves[0];
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
	std::vector<Structure> availableStructures = getStructures(row, col);
}

void Board::placeMeeple(int i, int j, std::pair<int, int> location)
{
	m_board[i][j]->placeMeeple(location);
}

// bool Board::checkMeeplePlacement(Tile tile, std::pair<int,int> blockSpot)
// {
// 	std::vector< std::vector<Block> > innerBlocks = tile.getInnerBlocks();
// 	Block block = innerBlocks[blockSpot.first][blockSpot.second];
// 	if (block.hasMeeple()) { return true; }
// 	if (block.getType() == "jungle" || block.getType() == "mixed") 
// 		checkJungle(tile, blockSpot);
// 	if (block.getType() == "lake") checkLake(tile, blockSpot);
// 	if (block.getType() == "trail") checkTrail(tile, blockSpot);
// }


/*So you can use the blocks in a tile to find all of the parts of a tile in the same feature,
To do this i have a queue of blocks and i find all of the adjacent blocks of the blocks your searching from that are the same type,
the problem comes in when youre traversing to a new tile since the blocks dont have any connections to anything else
i could add a queue of tiles and push tiles onto that queue if you traverse to them from the blocks
but then im not sure how i would hold that information for the new blocks of that tile in relation to the existing queue
instead of having a queue of tiles i could recall the function again and have it run the same process on the tiles on whatever block you move onto it from
the problem there is how to remember which tiles youve already visited and which blocks youve visted in those tiles
*/

Structure Board::checkJungle(Tile *tile, std::vector< std::vector<Block> >& tileBlocks, std::pair<int, int> blockSpot)
{
	Structure jungleStruct("jungle", blockSpot);
	jungleStruct.checkAnimals(tile);
	std::vector<Tile*> visitedTiles;
	visitedTiles.push_back(tile);
	buildJungle(&jungleStruct, tile, tileBlocks, blockSpot, visitedTiles);
	return jungleStruct;
}

void Board::buildJungle(Structure* struc, Tile *tile, std::vector< std::vector<Block> >& tileBlocks, std::pair<int,int> blockSpot, std::vector<Tile*> &visitedTiles) {
	int row = blockSpot.first;
	int col = blockSpot.second;
	std::cout<<"in build jungle at "<<row<<' '<<col<<std::endl;
	tileBlocks[row][col].visit();

	struc->structureBlocks.push_back(tileBlocks[row][col]);

	if(tileBlocks[row][col].hasMeeple())
		struc->hasMeeple = true;

	bool addedTileAnimals = false;
	for(int i = 0; i < visitedTiles.size(); i++) {
			if(visitedTiles[i] == tile)
			{
				addedTileAnimals = true;
				std::cout<<"Added animals already for this tile"<<std::endl;
			}
	}
	if(!addedTileAnimals) {
		struc->checkAnimals(tile);
	}

	std::cout<<"block type is "<<tileBlocks[row][col].getType()<<std::endl;
	if(tileBlocks[row][col].getType() == "mixed") {
		int trailFaces = 0;
		// Determine how many faces are trail faces. If there's only 1 than we know the mixed blocks don't connect
		if(tile->getUpFace()->getType() == "trail")
			trailFaces++;
		if(tile->getDownFace()->getType() == "trail")
			trailFaces++;
		if(tile->getRightFace()->getType() == "trail")
			trailFaces++;
		if(tile->getLeftFace()->getType() == "trail")
			trailFaces++;

		std::cout<<"trail faces is "<<trailFaces<<std::endl;
		if(trailFaces > 0) {
			if(trailFaces != 1) {
				for(int i = 0; i < 3; i++) {
					for(int j = 0; j < 3; j++) {
						if(tileBlocks[i][j].getType() == "mixed" && !(tileBlocks[i][j].isVisited()))
							buildJungle(struc, tile, tileBlocks, std::pair<int,int>(i,j), visitedTiles);
					}	
				}
			}
		}

	}

	// Check tiles above, below, left, and right of the current block to see if lake structure continues
	// std::cout<<"about to cehck row+1"<<std::endl;
	if((row + 1) <= 2 && !(tileBlocks[row + 1][col].isVisited()) && 
		(tileBlocks[row+1][col].getType() == "jungle" || tileBlocks[row+1][col].getType() == "mixed")) {
		buildJungle(struc, tile, tileBlocks, std::pair<int,int>(row+1,col), visitedTiles);
	}
	else if(row + 1 > 2 && tile->getDownTile() != NULL) {
		bool visitedNeighborTile = false;
		for(int i = 0; i < visitedTiles.size(); i++) {
			if(visitedTiles[i] == tile->getDownTile())
				visitedNeighborTile = true;
		}
		if(!visitedNeighborTile && tile->getDownTile()->getUpFaceType()!= "lake") {
			visitedTiles.push_back(tile->getDownTile());
			std::vector< std::vector<Block> > newBlocks = tile->getDownTile()->getInnerBlocks();
			buildJungle(struc, tile->getDownTile(), newBlocks, std::pair<int,int>(row-2,col), visitedTiles);
		}
	}
	// std::cout<<"about to check row-1"<<std::endl;
	if((row - 1) >= 0 && !(tileBlocks[row - 1][col].isVisited()) && 
		(tileBlocks[row - 1][col].getType() == "jungle" || tileBlocks[row-1][col].getType() == "mixed")) {
		buildJungle(struc, tile, tileBlocks, std::pair<int,int>(row-1,col), visitedTiles);
	}
	else if(row-1 < 0 && tile->getUpTile() != NULL) {
		bool visitedNeighborTile = false;
		for(int i = 0; i < visitedTiles.size(); i++) {
			if(visitedTiles[i] == tile->getUpTile())
				visitedNeighborTile = true;
		}
		if (!visitedNeighborTile && tile->getUpTile()->getDownFaceType() != "lake") {
			visitedTiles.push_back(tile->getUpTile());
			std::vector< std::vector<Block> > newBlocks = tile->getUpTile()->getInnerBlocks();
			buildJungle(struc, tile->getUpTile(), newBlocks, std::pair<int,int>(row+2,col), visitedTiles);
		}
	}
	// std::cout<<"about to check col+1"<<std::endl;
	if((col + 1) <= 2 && !(tileBlocks[row][col + 1].isVisited()) && 
		(tileBlocks[row][col + 1].getType() == "jungle" || tileBlocks[row][col+1].getType() == "mixed")) {
		buildJungle(struc, tile, tileBlocks, std::pair<int,int>(row,col+1), visitedTiles);
	}
	else if(col+1 > 2 && tile->getRightTile() != NULL) {
		bool visitedNeighborTile = false;
		for(int i = 0; i < visitedTiles.size(); i++) {
			if(visitedTiles[i] == tile->getRightTile())
				visitedNeighborTile = true;
		}
		if (!visitedNeighborTile && tile->getRightTile()->getLeftFaceType() != "lake") {
			visitedTiles.push_back(tile->getRightTile());
			std::vector< std::vector<Block> > newBlocks = tile->getRightTile()->getInnerBlocks();
			buildJungle(struc, tile->getRightTile(), newBlocks, std::pair<int,int>(row,col-2), visitedTiles);
		}
	}
	// std::cout<<"about to check col-1"<<std::endl;
	if((col - 1) >= 0 && !(tileBlocks[row][col-1].isVisited()) && 
		(tileBlocks[row][col - 1].getType() == "jungle" ||	 tileBlocks[row][col-1].getType() == "mixed")) {
		// std::cout<<"passing col-1"<<std::endl;
		buildJungle(struc, tile, tileBlocks, std::pair<int,int>(row,col-1), visitedTiles);
	} 
	else if(col-1 < 0 && tile->getLeftTile() != NULL) {
		bool visitedNeighborTile = false;
		for(int i = 0; i < visitedTiles.size(); i++) {
			if(visitedTiles[i] == tile->getLeftTile())
				visitedNeighborTile = true;
		}
		if (!visitedNeighborTile && tile->getLeftTile()->getRightFaceType() != "lake") {
			visitedTiles.push_back(tile->getLeftTile());
			std::vector< std::vector<Block> > newBlocks = tile->getLeftTile()->getInnerBlocks();
			buildJungle(struc, tile->getLeftTile(), newBlocks, std::pair<int,int>(row,col+2), visitedTiles);
		}
	}
	return;
}

Structure Board::checkLake(Tile *tile, std::vector< std::vector<Block> >& tileBlocks, std::pair<int, int> blockSpot)
{
	Structure lakeStruct("lake", blockSpot);
	lakeStruct.checkAnimals(tile);
	std::vector<Tile*> visitedTiles;
	visitedTiles.push_back(tile);
	buildLake(&lakeStruct, tile, tileBlocks, blockSpot, visitedTiles);
	return lakeStruct;
}

void Board::buildLake(Structure* struc, Tile *tile, std::vector< std::vector<Block> >& tileBlocks, std::pair<int,int> blockSpot, std::vector<Tile*> &visitedTiles) {
	// std::cout<<"in build lake"<<std::endl;
	int row = blockSpot.first;
	int col = blockSpot.second;
	tileBlocks[row][col].visit();
	// for(int i = 0; i < 3; i++) {
	// 	for(int j = 0; j < 3; j++) {
	// 		std::cout<<"Block at "<<i<<' '<<j<<" for tile "<<tile<<" has been visited? "<<tileBlocks[i][j].isVisited()<<std::endl;
	// 	}
	// }
	struc->structureBlocks.push_back(tileBlocks[row][col]);

	// check block for meeple
	if(tileBlocks[row][col].hasMeeple())
		struc->hasMeeple = true;

	bool addedTileAnimals;
	for(int i = 0; i < visitedTiles.size(); i++) {
			if(visitedTiles[i] == tile)
			{
				addedTileAnimals = true;
				std::cout<<"Added animals already for this tile"<<std::endl;
			}
	}
	if(!addedTileAnimals) {
		struc->checkAnimals(tile);
		// if(tile->hasCrocodile())
		// 	struc->crocodileCount++;
		// if(tile->hasDeer())
		// 	struc->deerCount++;
		// if(tile->hasBoar())
		// 	struc->boarCount++;
		// if(tile->hasBuffalo())
		// 	struc->buffaloCount++;
	}

	// Check tiles above, below, left, and right of the current block to see if lake structure continues
	// std::cout<<"about to cehck row+1"<<std::endl;
	if((row + 1) <= 2 && !(tileBlocks[row + 1][col].isVisited()) && tileBlocks[row+1][col].getType() == "lake") {
		buildLake(struc, tile, tileBlocks, std::pair<int,int>(row+1,col), visitedTiles);
	}
	else if(row + 1 > 2 && tile->getDownTile() != NULL) {
		bool visitedNeighborTile = false;
		for(int i = 0; i < visitedTiles.size(); i++) {
			if(visitedTiles[i] == tile->getDownTile())
				visitedNeighborTile = true;
		}
		if(!visitedNeighborTile) {
			visitedTiles.push_back(tile->getDownTile());
			std::vector< std::vector<Block> > newBlocks = tile->getDownTile()->getInnerBlocks();
			buildLake(struc, tile->getDownTile(), newBlocks, std::pair<int,int>(row-2,col), visitedTiles);
		}
	}
	// std::cout<<"about to check row-1"<<std::endl;
	if((row - 1) >= 0 && !(tileBlocks[row - 1][col].isVisited()) && tileBlocks[row - 1][col].getType() == "lake") {
		buildLake(struc, tile, tileBlocks, std::pair<int,int>(row-1,col), visitedTiles);
	}
	else if(row-1 < 0 && tile->getUpTile() != NULL) {
		bool visitedNeighborTile = false;
		for(int i = 0; i < visitedTiles.size(); i++) {
			if(visitedTiles[i] == tile->getUpTile())
				visitedNeighborTile = true;
		}
		if(!visitedNeighborTile) {
			visitedTiles.push_back(tile->getUpTile());
			std::vector< std::vector<Block> > newBlocks = tile->getUpTile()->getInnerBlocks();
			buildLake(struc, tile->getUpTile(), newBlocks, std::pair<int,int>(row+2,col), visitedTiles);
		}
	}
	// std::cout<<"about to check col+1"<<std::endl;
	if((col + 1) <= 2 && !(tileBlocks[row][col + 1].isVisited()) && tileBlocks[row][col + 1].getType() == "lake") {
		buildLake(struc, tile, tileBlocks, std::pair<int,int>(row,col+1), visitedTiles);
	}
	else if(col+1 > 2 && tile->getRightTile() != NULL) {
		bool visitedNeighborTile = false;
		for(int i = 0; i < visitedTiles.size(); i++) {
			if(visitedTiles[i] == tile->getRightTile())
				visitedNeighborTile = true;
		}
		if(!visitedNeighborTile) {
			visitedTiles.push_back(tile->getRightTile());
			std::vector< std::vector<Block> > newBlocks = tile->getRightTile()->getInnerBlocks();
			buildLake(struc, tile->getRightTile(), newBlocks, std::pair<int,int>(row,col-2), visitedTiles);
		}
	}
	// std::cout<<"about to check col-1"<<std::endl;
	if((col - 1) >= 0 && !(tileBlocks[row][col-1].isVisited()) && tileBlocks[row][col - 1].getType() == "lake") {
		// std::cout<<"passing col-1"<<std::endl;
		buildLake(struc, tile, tileBlocks, std::pair<int,int>(row,col-1), visitedTiles);
	} 
	else if(col-1 < 0 && tile->getLeftTile() != NULL) {
		bool visitedNeighborTile = false;
		for(int i = 0; i < visitedTiles.size(); i++) {
			if(visitedTiles[i] == tile->getLeftTile())
				visitedNeighborTile = true;
		}
		if(!visitedNeighborTile) {
			visitedTiles.push_back(tile->getLeftTile());
			std::vector< std::vector<Block> > newBlocks = tile->getLeftTile()->getInnerBlocks();
			buildLake(struc, tile->getLeftTile(), newBlocks, std::pair<int,int>(row,col+2), visitedTiles);
		}
	}
	return;
}

Structure Board::checkTrail(Tile *tile, std::vector< std::vector<Block> >& tileBlocks, std::pair<int, int> blockSpot)
{
	Structure trailStruct("trail", blockSpot);
	trailStruct.checkAnimals(tile);
	std::vector<Tile*> visitedTiles;
	visitedTiles.push_back(tile);
	buildTrail(&trailStruct, tile, tileBlocks, blockSpot, visitedTiles);
	return trailStruct;
}

void Board::buildTrail(Structure* struc, Tile *tile, std::vector< std::vector<Block> >& tileBlocks, std::pair<int,int> blockSpot, std::vector<Tile*> &visitedTiles) {
	int row = blockSpot.first;
	int col = blockSpot.second;
	tileBlocks[row][col].visit();

	if(row == 1 && col == 1) {
		int divergingTrailCount = 0;
		if(tileBlocks[row+1][col].getType() == "trail") 
			divergingTrailCount++;
		if(tileBlocks[row-1][col].getType() == "trail") 
			divergingTrailCount++;
		if(tileBlocks[row][col+1].getType() == "trail") 
			divergingTrailCount++;
		if(tileBlocks[row][col-1].getType() == "trail") 
			divergingTrailCount++;
		if(divergingTrailCount > 2) 
			return;
	}

	struc->structureBlocks.push_back(tileBlocks[row][col]);

	// Check block for meeple
	if(tileBlocks[row][col].hasMeeple())
		struc->hasMeeple = true;

	bool addedTileAnimals;
	for(int i = 0; i < visitedTiles.size(); i++) {
			if(visitedTiles[i] == tile)
			{
				addedTileAnimals = true;
				std::cout<<"Added animals already for this tile"<<std::endl;
			}
	}
	if(!addedTileAnimals) {
		struc->checkAnimals(tile);
		// if(tile->hasCrocodile())
		// 	struc->crocodileCount++;
		// if(tile->hasDeer())
		// 	struc->deerCount++;
		// if(tile->hasBoar())
		// 	struc->boarCount++;
		// if(tile->hasBuffalo())
		// 	struc->buffaloCount++;
	}

	// Check tiles above, below, left, and right of the current block to see if lake structure continues
	// std::cout<<"about to cehck row+1"<<std::endl;
	if((row + 1) <= 2 && !(tileBlocks[row + 1][col].isVisited()) && tileBlocks[row+1][col].getType() == "trail") {
		buildTrail(struc, tile, tileBlocks, std::pair<int,int>(row+1,col), visitedTiles);
	}
	else if(row + 1 > 2 && tile->getDownTile() != NULL) {
		bool visitedNeighborTile = false;
		for(int i = 0; i < visitedTiles.size(); i++) {
			if(visitedTiles[i] == tile->getDownTile())
				visitedNeighborTile = true;
		}
		if(!visitedNeighborTile) {
			visitedTiles.push_back(tile->getDownTile());
			std::vector< std::vector<Block> > newBlocks = tile->getDownTile()->getInnerBlocks();
			buildTrail(struc, tile->getDownTile(), newBlocks, std::pair<int,int>(row - 2,col), visitedTiles);
		}
	}
	// std::cout<<"about to check row-1"<<std::endl;
	if((row - 1) >= 0 && !(tileBlocks[row - 1][col].isVisited()) && tileBlocks[row - 1][col].getType() == "trail") {
		buildTrail(struc, tile, tileBlocks, std::pair<int,int>(row-1,col), visitedTiles);
	}
	else if(row-1 < 0 && tile->getUpTile() != NULL) {
		bool visitedNeighborTile = false;
		for(int i = 0; i < visitedTiles.size(); i++) {
			if(visitedTiles[i] == tile->getUpTile())
				visitedNeighborTile = true;
		}
		if(!visitedNeighborTile) {
			visitedTiles.push_back(tile->getUpTile());
			std::vector< std::vector<Block> > newBlocks = tile->getUpTile()->getInnerBlocks();
			buildTrail(struc, tile->getUpTile(), newBlocks, std::pair<int,int>(row+2,col), visitedTiles);
		}
	}
	// std::cout<<"about to check col+1"<<std::endl;
	if((col + 1) <= 2 && !(tileBlocks[row][col + 1].isVisited()) && tileBlocks[row][col + 1].getType() == "trail") {
		buildTrail(struc, tile, tileBlocks, std::pair<int,int>(row,col+1), visitedTiles);
	}
	else if(col+1 > 2 && tile->getRightTile() != NULL) {
		bool visitedNeighborTile = false;
		for(int i = 0; i < visitedTiles.size(); i++) {
			if(visitedTiles[i] == tile->getRightTile())
				visitedNeighborTile = true;
		}
		if(!visitedNeighborTile) {
			visitedTiles.push_back(tile->getRightTile());
			std::vector< std::vector<Block> > newBlocks = tile->getRightTile()->getInnerBlocks();
			buildTrail(struc, tile->getRightTile(), newBlocks, std::pair<int,int>(row,col-2), visitedTiles);
		}
	}
	// std::cout<<"about to check col-1"<<std::endl;
	if((col - 1) >= 0 && !(tileBlocks[row][col-1].isVisited()) && tileBlocks[row][col - 1].getType() == "trail") {
		// std::cout<<"passing col-1"<<std::endl;
		buildTrail(struc, tile, tileBlocks, std::pair<int,int>(row,col-1), visitedTiles);
	} 
	else if(col-1 < 0 && tile->getLeftTile() != NULL) {
		bool visitedNeighborTile = false;
		for(int i = 0; i < visitedTiles.size(); i++) {
			if(visitedTiles[i] == tile->getLeftTile())
				visitedNeighborTile = true;
		}
		if(!visitedNeighborTile) {
			visitedTiles.push_back(tile->getLeftTile());
			std::vector< std::vector<Block> > newBlocks = tile->getLeftTile()->getInnerBlocks();
			buildTrail(struc, tile->getLeftTile(), newBlocks, std::pair<int,int>(row,col+2), visitedTiles);
		}
	}
	return;
}

void Board::connectFaces(int row, int col)
{
	if(row+1 <= 150 && m_board[row+1][col] != NULL &&
		 (*m_board[row+1][col]->getUpFace()).faceEquals(*m_board[row][col]->getDownFace()))
	{
		(*m_board[row + 1][col]->getUpFace()).setNeighborFace(*m_board[row][col]->getDownFace());
		(*m_board[row][col]->getDownFace()).setNeighborFace(*m_board[row + 1][col]->getUpFace());


		// Set adjacent tiles now after setting faces
		
		// std::cout<<"**********DOWN TILE BEFORE SETTING IS "<<m_board[row][col]->getDownTile()<<std::endl;
		(m_board[row][col])->setNeighborDownTile(*m_board[row + 1][col]);
		// std::cout<<"**********DOWN TILE AFTER SETTING IS "<<m_board[row][col]->getDownTile()<<std::endl;
		// std::cout<<"72 72 up tile before setting is "<<m_board[row+1][col]->getUpTile()<<std::endl;
		(m_board[row+1][col])->setNeighborUpTile(*m_board[row][col]);
		// std::cout<<"72 72 up tile after setting is "<<m_board[row+1][col]->getUpTile()<<std::endl;

		//std::cout << "Neighbor of the up face of " << row + 1 << ' ' << col << " is " << m_board[row + 1][col]->getUpFace()->getNeighborFace() << std::endl;
		//std::cout << "Neighbor of the down face of " << row << ' ' << col << " is " << m_board[row][col]->getDownFace()->getNeighborFace() << std::endl;
	}
	else if(m_board[row+1][col] != NULL)// && !m_board[row+1][col]->getUpFace()->faceEquals(*m_board[row][col]->getDownFace()))
	{
		std::cout << "ERROR: FACES DON'T MATCH for tile down face" << std::endl;
	}
	// Connect top face of tile to existing tile above it
	if(row-1 >= 0 && m_board[row-1][col] != NULL &&
		 (*m_board[row-1][col]->getDownFace()).faceEquals(*m_board[row][col]->getUpFace()))
	{
		(*m_board[row - 1][col]->getDownFace()).setNeighborFace(*m_board[row][col]->getUpFace());
		(*m_board[row][col]->getUpFace()).setNeighborFace(*m_board[row - 1][col]->getDownFace());

		// Set adjacent tiles now after setting faces
		(m_board[row][col])->setNeighborUpTile(*m_board[row - 1][col]);
		(m_board[row - 1][col])->setNeighborDownTile(*m_board[row][col]);

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

		// Set adjacent tiles now after setting faces
		(m_board[row][col])->setNeighborLeftTile(*m_board[row][col - 1]);
		(m_board[row][col - 1])->setNeighborRightTile(*m_board[row][col]);

		//std::cout << "Neighbor of the right face of " << row << ' ' << col - 1 << " is " << m_board[row][col - 1]->getRightFace()->getNeighborFace() << std::endl;
		//std::cout << "Neighbor of the left face of " << row << ' ' << col << " is " << m_board[row][col]->getLeftFace()->getNeighborFace() << std::endl;
	}
	else if(m_board[row][col-1] != NULL)// && !m_board[row][col-1]->getRightFace()->faceEquals(*m_board[row][col]->getLeftFace()))
	{
		std::cout << "ERROR: FACES DON'T MATCH for tile left face" << std::endl;
	}
	// Connect right face of tile to the existing tile to the right of it
	if (col+1 <= 150 && m_board[row][col+1] != NULL &&
		  (*m_board[row][col+1]->getLeftFace()).faceEquals(*m_board[row][col]->getRightFace()))
	{
		(*m_board[row][col + 1]->getLeftFace()).setNeighborFace(*m_board[row][col]->getRightFace());
		(*m_board[row][col]->getRightFace()).setNeighborFace(*m_board[row][col + 1]->getLeftFace());

		// Set adjacent tiles now after setting faces
		(m_board[row][col])->setNeighborRightTile(*m_board[row][col + 1]);
		(m_board[row][col + 1])->setNeighborLeftTile(*m_board[row][col]);

		//std::cout << "Neighbor of the left face of " << row << ' ' << col + 1 << " is " << m_board[row][col + 1]->getLeftFace()->getNeighborFace() << std::endl;
		//std::cout << "Neighbor of the right face of " << row << ' ' << col << " is " << m_board[row][col]->getRightFace()->getNeighborFace() << std::endl;
	}
	else if(m_board[row][col+1] != NULL )//&& !m_board[row][col+1]->getLeftFace()->faceEquals(*m_board[row][col]->getRightFace()))
	{
		std::cout << "ERROR: FACES DON'T MATCH for tile right face" << std::endl;
	}
}

// Pass in the coordinates of the tile that you just placed
std::vector<Structure> Board::getStructures(int row, int col) {
	std::cout<<"IN GET STRUCTURES FOR "<<row<<' '<<col<<std::endl;
	std::vector<Structure> structures;
	Tile* tile = m_board[row][col];
	std::vector< std::vector<Block> > tileBlocks = tile->getInnerBlocks();
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(!(tileBlocks[i][j].isVisited())) {
				if(tileBlocks[i][j].getType() == "jungle" || tileBlocks[i][j].getType() == "mixed") {
					Structure struc = checkJungle(tile, tileBlocks, std::pair<int,int>(i,j));
					structures.push_back(struc);
				}
				else if(tileBlocks[i][j].getType() == "lake") {
					Structure struc = checkLake(tile, tileBlocks, std::pair<int,int>(i,j));
					structures.push_back(struc);
				}
				else if(tileBlocks[i][j].getType() == "trail") {
					Structure struc = checkTrail(tile, tileBlocks, std::pair<int,int>(i,j));
					structures.push_back(struc);
				}
			}
		}
	}
	for(int i = 0; i < structures.size(); i++) {
		for(int j = 0; j < structures[i].structureBlocks.size(); j++) {
			structures[i].structureBlocks[j].unVisit();
		}
	}
	for(int i = 0; i < structures.size(); i++) {
		std::cout<<"Structure is of type "<<structures[i].type<<" with "<<structures[i].structureBlocks.size()
		<<" blocks and starting block at "<<structures[i].startingBlock.first<<' '<<structures[i].startingBlock.second<<std::endl;
		std::cout<<" and how many buffalo? : "<<structures[i].buffaloCount<<std::endl;
	}
	std::cout<<"Structures size is "<<structures.size()<<std::endl;
	return structures;
}
