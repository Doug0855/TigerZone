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
	// Loop through the rows of board
	for(size_t i = 0; i < m_board.size(); i++)
	{
		// Loop through column of board
		for(size_t j = 0; j < m_board[i].size())
		{
			if(m_board[i][j] != null && m_board[i][j].hasOpenFace())
			{
				if(m_board[i][j].getOpenFaces()  )
			}
		}
	}
}

bool Board::place_tile(int location, Tile tile)
{
	
}
