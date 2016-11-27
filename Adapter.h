#ifndef ADAPTER_H
#define ADAPTER_H

#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include "Tile_Structure/Tile.h"
#include "Tile_Structure/Face.h"
#include "Tile_Structure/Block.h"

struct values_t {
	int tile_num;


};


class Adapter {
public:
	Adapter();
	~Adapter();

	// Methods
	//std::string tileToExpr(Tile& tile);
	values_t exprToTile(std::string &expr);
	int numRotations(const int x);
	std::vector<std::string> convertExpression(const std::string& expr);
	std::string get(const std::string& prop);
	void set(const std::string& prop, const std::string value);
	std::string getTileString(const int& index);
	int getCommand(const std::vector<std::string>& myV);
	std::pair<int, int> convertCoordinates(int i, int j);
	std::pair<int, int> convertCoordinates(std::pair<int, int> location);
	int convertZone(std::pair<int, int> location);
	std::pair<int, int> convertZone(int spot);
	
private:
	std::string playerID, roundID, score, numChallenges, numRounds, planTime, moveTime;
	std::vector<std::string> tileList;
};

#endif
