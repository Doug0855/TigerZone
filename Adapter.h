#ifndef ADAPTER_H
#define ADAPTER_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include "Tile_Structure/Tile.h"
#include "Tile_Structure/Face.h"
#include "Tile_Structure/Block.h"

class Adapter {
public:
	Adapter();
	~Adapter();

	// Methods
	std::string tileToExpr(Tile& tile);
	int exprToTile(std::string& expr);
	int numRotations(const int x);
	std::vector<std::string> convertExpression(const std::string& expr);
	std::string get(const std::string& prop);
	void set(const std::string& prop, const std::string value);
	std::string getTileString(const int& index);
	int getCommand();

private:
	std::string playerID, roundID, score, numChallenges, numRounds, planTime, moveTime;
	std::vector<std::string> tileList;
};

#endif
