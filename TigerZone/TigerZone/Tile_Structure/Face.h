#ifndef FACE_H
#define FACE_H

#include "Block.h"
#include <iostream>

class Face {
public:
	Face(char b1, char b2, char b3, Face &accross_face, Face &left_face, Face &right_face);
	Face();
	~Face();

  void setNeighborFace(Face &face);
  Face* getNeighborFace() { return neighborFace; }
  Face* getAccrossFace() { return inwardAcrossFace; }
  Face* getLeftFace() { return inwardLeftFace; }
  Face* getRightFace() { return inwardRightFace; }

  std::string getBlockType(int block);

  void placeMeeple();
	bool hasMeeple() { return meeple; }
  void visit();
  bool hasBeenVisited() { return visited; }

	bool faceEquals(Face face);	//determines if two faces are equal
	bool connected(); //function to check if a face is connected to a neighborFace


private:
	bool meeple, visited;
  Block m_1, m_2, m_3;
  Face *neighborFace, *inwardAcrossFace, *inwardLeftFace, *inwardRightFace;
};

#endif
