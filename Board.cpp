#inlcude "Board.h"

Board::Board()
{
	
}

Board::~Board()
{
	
}

string Board::to_string(void)
{
	
}

vector<int> Board::display_positions(Tile tile)
{
	std::vector<int> places;
	// Loop through the rows of board
	for(size_t i = 0; i < m_board.size(); i++)
	{
		// Loop through column of board
		for(size_t j = 0; j < m_board[i].size())
		{
			if(m_board[i][j] != null && m_board[i][j].hasOpenFace())
			{
				// get all the open faces for the tile on the board
				std::vector<std::string> openFaces = m_board[i][j].getOpenFaces();
				// loop through all the open faces
				for(size_t k = 0; k < openFaces.size(); k++)
				{
					// see which face is open for the tile on the board
					places.push_back(checkPlacement(tile&, i, j, openFaces));
					
				}
			}
		}
	}
}

bool Board::place_tile(int location, Tile tile)
{
	
}

vector<int> checkPlacement(Tile* tile, int i, int j, std::vector<std::string> openFaces)
{
	std::vector<int> places;
	switch(openFaces[k])
	{
		// if the face is the up face compare the down face of the tile were trying to place
		case "up":
			for(int ii = 0; ii < 3; ii++)
			{
				// if the botton face of the tile were trying to place equals the top face of the tile on the board
				// and it equals the faces of all the other faces
				if(board[i][j].getUpFace().faceEquals(tile.getDownFace()) &&
					(board[i-1][j-1] == null || board[i-1][j-1].getRightFace().faceEquals(tile.getLeftFace())) &&
					(board[i-1][j+1] == null || board[i-1][j+1].getLeftFace().faceEquals(tile.getRightFace())) &&
					(board[i-2][j] == null || board[i-2][j].getDownFace().faceEquals(tile.getUpFace())))
					{
						places.push_back(i-1);
						places.push_back(j);
						break;
					}
				rotate(tile);
			}
		break;
		case "down":
			for(int ii = 0; ii < 3; ii++)
			{
				// same thing as above but with down
				if(board[i+2][j].getUpFace().faceEquals(tile.getDownFace()) &&
					(board[i+1][j-1] == null || board[i-1][j-1].getRightFace().faceEquals(tile.getLeftFace())) &&
					(board[i+1][j+1] == null || board[i-1][j+1].getLeftFace().faceEquals(tile.getRightFace())) &&
					(board[i][j] == null || board[i][j-2].getDownFace().faceEquals(tile.getUpFace())))
					{
						places.push_back(i+1);
						places.push_back(j);
						break;
					}
				rotate(tile);
			}
		break;
		case "left":
			for(int ii = 0; ii < 3; ii++)
			{
				// same thing as above but with left 
				if(board[i][j].getUpFace().faceEquals(tile.getDownFace()) &&
					(board[i+1][j+1] == null || board[i-1][j-1].getRightFace().faceEquals(tile.getLeftFace())) &&
					(board[i+1][j+1] == null || board[i-1][j+1].getLeftFace().faceEquals(tile.getRightFace())) &&
					(board[i+2][j] == null || board[i][j-2].getDownFace().faceEquals(tile.getUpFace())))
					{
						places.push_back(i+2);
						places.push_back(j);
						break;
					}
				rotate(tile);
			}			
		break;
		case "right":
			for(int ii = 0; ii < 3; ii++)
			{
				// same thing as above but with right
				if(board[i+1][j+1].getUpFace().faceEquals(tile.getDownFace()) &&
					(board[i][j] == null || board[i-1][j-1].getRightFace().faceEquals(tile.getLeftFace())) &&
					(board[i][j+2] == null || board[i-1][j+1].getLeftFace().faceEquals(tile.getRightFace())) &&
					(board[i-1][j+1] == null || board[i][j-2].getDownFace().faceEquals(tile.getUpFace())))
					{
						places.push_back(i+2);
						places.push_back(j);
						break;
					}
				rotate(tile);
			}			
		break;
	}
}
