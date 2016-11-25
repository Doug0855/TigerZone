#ifndef FACE_H
#define FACE_H

#include "Block.h"
#include <iostream>

#define    Jungle     'j'
#define    Lake       'l'
#define    Trail      't'
#define    Den        'd' // this is probably unnecessary

class Face {
public:
	Face(std::string faceType);
	Face();
	~Face();

  void setNeighborFace(Face &face);
  Face* getNeighborFace() { return neighborFace; }

  std::string getType() { return type; }
  void setType(std::string type);

  // std::string getBlockType(int block);

  // void placeMeeple();
	// bool hasMeeple() { return meeple; }
  // void visit();
  // bool hasBeenVisited() { return visited; }

	bool faceEquals(Face face);	//determines if two faces are equal
	bool connected(); //function to check if a face is connected to a neighborFace


private:
	// bool meeple, visited;
  std::string type;
  Face *neighborFace;
};

#endif
