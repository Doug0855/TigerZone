#ifndef PLAYER_H
#define PLAYER_H

#inlcude <vector>

class Meeple;
class Board;

class Player{
public:
	Player();
	~Player();
	
private:
	std::vector<Meeple> meeples;
	int score;
	Board board;
};
