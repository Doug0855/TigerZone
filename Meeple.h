#pragma once

#include <string>
#include <utility>

class Meeple{
public:
	Meeple();
	~Meeple();
	
	
protected:
	std::pair<int, int> m_location;
	std::string m_role;
		
	
};

