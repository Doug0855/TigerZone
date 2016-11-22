#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Meeple.h"
#include "Board.h"

class Player{
public:
	Player();
	~Player();

	void makeMove(Tile);

	// The three possibilities when a player draws an unplayable tile

	// pass in coordinate of where the meeple is that you'd like returned
	void getMeepleBack(std::pair<int,int>);
	// Pass in the address of the face where you would like to place the meeple
	void placeMeeple(Face &face);
	void passMove();

private:
	std::vector<Meeple> meeples;
	int score;
};

#endif
