#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Meeple.h"
#include "Board.h"

class Player{
public:
	Player();
	~Player();
	
private:
	std::vector<Meeple> meeples;
	int score;
	Board board;
};

#endif