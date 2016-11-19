#include "Monk.h"

Monk::Monk()
{

}

Monk::~Monk()
{

}

/*int Monk::countPoints(std::vector<std::vector<Tile>> board, bool& complete)
{
	int i = m_location.first;
	int j = m_location.second;
	int sum = 1;

	if(board[i+1][j].hasInit) sum++;
	if (board[i][j + 1].hasInit) sum++;
	if (board[i - 1][j].hasInit) sum++;
	if (board[i][j - 1].hasInit) sum++;
	if (board[i + 1][j + 1].hasInit) sum++;
	if (board[i - 1][j + 1].hasInit) sum++;
	if (board[i - 1][j - 1].hasInit) sum++;
	if (board[i + 1][j - 1].hasInit) sum++;

	if(sum == 9)
	{
		return sum;
		complete = true;
	}
	else
	{
		return sum;
		complete = false;
	}
}*/
