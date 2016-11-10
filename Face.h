#pragma once
#include "Block.h"

class Face{
	public:
		Face();
		~Face();
		
		Face* neighborFace;
		bool faceEquals(Face face);	//determines if two faces are equal
		bool connected(); ///< returns false if not connected
		
		Block* getM1() { return &m_1; };
		Block* getM2() { return &m_2; };
		Block* getM3() { return &m_3; };
		
	private:
		Block m_1, m_2, m_3;
	
};

