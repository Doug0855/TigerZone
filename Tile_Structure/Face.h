#ifndef FACE_H
#define FACE_H

#include "Block.h"
#include <iostream>

// #define    Jungle     'j'
// #define    Lake       'l'
// #define    Trail      't'
// #define    Den        'd' // this is probably unnecessary

class Face {
public:
	Face(Block &b1, Block &b2, Block &b3, Face &accross_face, Face &left_face, Face &right_face);
	//Face(std::string faceType);
	Face();
	~Face();

  void setNeighborFace(Face &face);
  Face* getNeighborFace() { return neighborFace; }
	Face* getAcrossFace() { return inwardAcrossFace; }
	Face* getLeftFace() { return inwardLeftFace; }
	Face* getRightFace() { return inwardRightFace; }

  std::string getType() { return m_2->getType(); }
  void setType(Block &b1, Block &b2, Block &b3);

  std::string getBlockType(int block);

  // void placeMeeple();
	bool hasMeeple();
  void visit();
	void resetVisitation() { this->visited = false; }
  bool hasBeenVisited() { return visited; }

	bool faceEquals(Face face);	//determines if two faces are equal
	bool connected(); //function to check if a face is connected to a neighborFace


private:
	std::string type;
	bool visited; //,meeple
	Block *m_1, *m_2, *m_3;
  Face *neighborFace, *inwardAcrossFace, *inwardLeftFace, *inwardRightFace;
};

#endif
