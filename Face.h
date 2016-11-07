#ifndef FACE_H
#define FACE_H

blass Block;

class Face{
public:
	Face();
	~Face();
	
	bool faceEquals(Face face);
	bool connected(); ///< returns false if not connected
	
private:
	Block m_1, m_2, m_3;
	
};

#endif
