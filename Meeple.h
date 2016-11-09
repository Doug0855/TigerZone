#pragma once

#include <string>

class Meeple{
public:
	Meeple();
	~Meeple();
	
	int countPoints();
	
private:
	std::string m_role;
		
	
};

