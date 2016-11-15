#ifndef FACE_H
#define FACE_H

#include "Block.h"

class Face{
public:
	Face(char b1, char b2, char b3);
	Face();
	~Face();
	
	Face* neighborFace;
	bool faceEquals(Face face);	//determines if two faces are equal
	bool connected(); ///< returns false if not connected
	
//private:
	Block m_1, m_2, m_3;
	
};

#endif
