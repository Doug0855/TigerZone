#ifndef MEEPLE_H
#define MEEPLE_H

#include <string>

class Meeple{
public:
	Meeple();
	~Meeple();
	
	int countPoints();
	
private:
	std::string m_role;
		
	
};

#endif
