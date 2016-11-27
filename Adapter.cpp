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

values_t Adapter::exprToTile(std::string &expr) {
	values_t output;
	output.tile_num = -1;

	transform(expr.begin(), expr.end(), expr.begin(), toupper);
	if (expr == "JJJJ-")
	{
		output.tile_num = 1;
		return output;
	}
	if (expr == "LLLL-")
	{
		output.tile_num = 2;
		return output;
	}
	if (expr == "TLJT-")
	{
		output.tile_num = 3;
		return output;
	}
	if (expr == "TLTT-")
	{
		output.tile_num = 4;
		return output;
	}
	if (expr == "JJJJX")
	{
		output.tile_num = 5;
		return output;
	}
	if (expr == "JLLL-")
	{
		output.tile_num = 6;
		return output;
	}
	if (expr == "TLJTP")
	{
		output.tile_num = 7;
		return output;
	}
	if (expr == "TLTTP")
	{
		output.tile_num = 8;
		return output;
	}
	if (expr == "JJTJX")
	{
		output.tile_num = 9;
		return output;
	}
	if (expr == "LLJJ-")
	{
		output.tile_num = 10;
		return output;
	}
	if (expr == "JLTT-")
	{
		output.tile_num = 11;
		return output;
	}
	if (expr == "TLLT-")
	{
		output.tile_num = 12;
		return output;
	}
	if (expr == "TTTT-")
	{
		output.tile_num = 13;
		return output;
	}
	if (expr == "JLJL-")
	{
		output.tile_num = 14;
		return output;
	}
	if (expr == "JLTTB")
	{
		output.tile_num = 15;
		return output;
	}
	if (expr == "TLLTB")
	{
		output.tile_num = 16;
		return output;
	}
	if (expr == "TJTJ-")
	{
		output.tile_num = 17;
		return output;
	}
	if (expr == "LJLJ-")
	{
		output.tile_num = 18;
		return output;
	}
	if (expr == "TLTJ-")
	{
		output.tile_num = 19;
		return output;
	}
	if (expr == "LJTJ-")
	{
		output.tile_num = 20;
		return output;
	}
	if (expr == "TJJT-")
	{
		output.tile_num = 21;
		return output;
	}
	if (expr == "LJJJ-")
	{
		output.tile_num = 22;
		return output;
	}
	if (expr == "TLTJD")
	{
		output.tile_num = 23;
		return output;
	}
	if (expr == "LJTJD")
	{
		output.tile_num = 24;
		return output;
	}
	if (expr == "TJTT-")
	{
		output.tile_num = 25;
		return output;
	}
	if (expr == "JLLJ-")
	{
		output.tile_num = 26;
		return output;
	}
	if (expr == "TLLL-")
	{
		output.tile_num = 27;
		return output;
	}
	return output;
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
