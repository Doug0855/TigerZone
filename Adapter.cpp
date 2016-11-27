#include "Adapter.h"

Adapter::Adapter() {}

Adapter::~Adapter() {}

/*std::string Adapter::tileToExpr(Tile& tile) {
	// Vector of chars to be converted to string
	std::vector<char> expr;

	// Get Tile type, push to vector
	if (tile.getUpFace()->getBlockType(2) == "jungle")
		expr.push_back('J');
	else if (tile.getUpFace()->getBlockType(2) == "trail")
		expr.push_back('T');
	else if (tile.getUpFace()->getBlockType(2) == "lake")
		expr.push_back('L');

	if (tile.getRightFace()->getBlockType(2) == "jungle")
		expr.push_back('J');
	else if (tile.getRightFace()->getBlockType(2) == "trail")
		expr.push_back('T');
	else if (tile.getRightFace()->getBlockType(2) == "lake")
		expr.push_back('L');

	if (tile.getDownFace()->getBlockType(2) == "jungle")
		expr.push_back('J');
	else if (tile.getDownFace()->getBlockType(2) == "trail")
		expr.push_back('T');
	else if (tile.getDownFace()->getBlockType(2) == "lake")
		expr.push_back('L');

	if (tile.getLeftFace()->getBlockType(2) == "jungle")
		expr.push_back('J');
	else if (tile.getLeftFace()->getBlockType(2) == "trail")
		expr.push_back('T');
	else if (tile.getLeftFace()->getBlockType(2) == "lake")
		expr.push_back('L');

	// Get Special character (animal, den, nothing special)
	if (tile.hasBoar())
		expr.push_back('P');
	else if (tile.hasBuffalo())
		expr.push_back('B');
	else if (tile.hasDeer())
		expr.push_back('D');
	else if (tile.getCenter()->getType() == "den")
		expr.push_back('X');
	else
		expr.push_back('-');

	// Convert to string
	std::string expression(expr.begin(), expr.end());

	return expression;
}*/

int Adapter::exprToTile(std::string& expr) {
	int type = -1;
	transform(expr.begin(), expr.end(), expr.begin(), toupper);
	if (expr == "JJJJ-")
		return type = 1;
	if (expr == "LLLL-")
		return type = 2;
	if (expr == "TLJT-")
		return type = 3;
	if (expr == "TLTT-")
		return type = 4;
	if (expr == "JJJJX")
		return type = 5;
	if (expr == "JLLL-")
		return type = 6;
	if (expr == "TLJTP")
		return type = 7;
	if (expr == "TLTTP")
		return type = 8;
	if (expr == "JJTJX")
		return type = 9;
	if (expr == "LLJJ-")
		return type = 10;
	if (expr == "JLTT-")
		return type = 11;
	if (expr == "TLLT-")
		return type = 12;
	if (expr == "TTTT-")
		return type = 13;
	if (expr == "JLJL-")
		return type = 14;
	if (expr == "JLTTB")
		return type = 15;
	if (expr == "TLLTB")
		return type = 16;
	if (expr == "TJTJ-")
		return type = 17;
	if (expr == "LJLJ-")
		return type = 18;
	if (expr == "TLTJ-")
		return type = 19;
	if (expr == "LJTJ-")
		return type = 20;
	if (expr == "TJJT-")
		return type = 21;
	if (expr == "LJJJ-")
		return type = 22;
	if (expr == "TLTJD")
		return type = 23;
	if (expr == "LJTJD")
		return type = 24;
	if (expr == "TJTT-")
		return type = 25;
	if (expr == "JLLJ-")
		return type = 26;
	if (expr == "TLLL-")
		return type = 27;
	if (expr == "TLLLC")
		return type = 28;

	return type;
}

int Adapter::numRotations(const int x) {
	int numRotations = 0;
	if (x == 90)
		return numRotations = 1;
	if (x == 180)
		return numRotations = 2;
	if (x == 270)
		return numRotations = 3;

	return numRotations;
}

std::vector<std::string> Adapter::convertExpression(const std::string& expr) {
	// Convert to stream
	std::istringstream buf(expr);
	std::istream_iterator<std::string> begin(buf), end;

	// Store in vector and return
	std::vector<std::string> myV(begin, end);
	return myV;
}

std::string Adapter::get(const std::string& prop) {
	// Based on prop, return value
	if (prop == "pid")
		return this->playerID;
	if (prop == "rid")
		return this->roundID;
	if (prop == "score")
		return this->score;
	if (prop == "challenges")
		return this->numChallenges;
	if (prop == "rounds")
		return this->numRounds;
	if (prop == "ptime")
		return this->planTime;
	if (prop == "mtime")
		return this->moveTime;

	return "Error";
}

void Adapter::set(const std::string& prop, const std::string value) {
	// Based on prop, return value
	if (prop == "pid")
		this->playerID = value;
	if (prop == "rid")
		this->roundID = value;
	if (prop == "score")
		this->score = value;
	if (prop == "challenges")
		this->numChallenges = value;
	if (prop == "rounds")
		this->numRounds = value;
	if (prop == "ptime")
		this->planTime = value;
	if (prop == "mtime")
		this->moveTime = value;
}

std::string Adapter::getTileString(const int& index) {
	// Error check
	if (index < 0 || index > this->tileList.size())
		return "Error";

	return this->tileList[index];
}

int Adapter::getCommand(const std::vector<std::string>& myV) {

}

std::pair<int, int> Adapter::convertCoordinates(int i, int j)
{
	int row = i + 72;
	int col = j + 72;
	return std::pair<int, int> (row, col);
}

std::pair<int, int> Adapter::convertCoordinates(std::pair<int, int> location)
{
	int i = location.first - 72;
	int j = location.second - 72;
	return std::pair<int, int>(i, j);
}

int Adapter::convertZone(std::pair<int, int> location)
{
	int i = location.first;
	int j = location.second;
	if(i = 0)
	{
		if(j = 0) return 0;
		else if(j = 1) return 1;
		else if(j = 2) return 3;
	}
	else if(i = 1)
	{
		if(j = 0) return 4;
		else if(j = 1) return 5;
		else if(j = 2) return 6;
	}
	else if(i = 2)
	{
		if(j = 0) return 7;
		else if(j = 1) return 8;
		else if(j = 2) return 9;
	}
}

std::pair<int, int> Adapter::convertZone(int spot)
{
	if(spot = 1) return std::pair<int, int>(0,0);
	else if(spot = 2) return std::pair<int, int>(0,1);
	else if(spot = 3) return std::pair<int, int>(0,2);
	else if(spot = 4) return std::pair<int, int>(1,0);
	else if(spot = 5) return std::pair<int, int>(1,1);
	else if(spot = 6) return std::pair<int, int>(1,2);
	else if(spot = 7) return std::pair<int, int>(2,0);
	else if(spot = 8) return std::pair<int, int>(2,1);
	else if(spot = 9) return std::pair<int, int>(2,2);
}
