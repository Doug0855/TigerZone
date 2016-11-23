#include "Face.h"

Face::Face(char b1, char b2, char b3, Face &accross_face, Face& left_face, Face &right_face)
{
	m_1 = Block(b1);
	m_2 = Block(b2);
	m_3 = Block(b3);
  meeple = false;
  visited = false;
	neighborFace = NULL;
  inwardAcrossFace = &accross_face;
  inwardLeftFace = &left_face;
  inwardRightFace = &right_face;
}
Face::Face()
{
  m_1 = Block();
  m_2 = Block();
  m_3 = Block();
  meeple = false;
  visited = false;
	neighborFace = NULL;
  inwardAcrossFace = NULL;
  inwardLeftFace = NULL;
  inwardRightFace = NULL;
}
Face::~Face()
{

}
void Face::setNeighborFace(Face &face)
{
  neighborFace = &face;
}
std::string Face::getBlockType(int block)
{
  if (block == 1)
    return this->m_1.getType();
  else if (block == 2)
    return this->m_2.getType();
  else if (block == 3)
    return this->m_3.getType();
  else
    return "";
}
void Face::placeMeeple()
{
  meeple = true;
}
void Face::visit()
{
  visited = true;
}
bool Face::faceEquals(Face face)
{
  std::cout<<"board face: "<<this->m_1.getType()<<' '<<this->m_2.getType()<<' '<<this->m_2.getType()<<std::endl;
  std::cout<<"tile face: "<<face.getBlockType(1)<<' '<<face.getBlockType(2)<<' '<<face.getBlockType(3)<<std::endl;
	if(this->m_1.getType() == face.getBlockType(1) &&
		 this->m_2.getType() == face.getBlockType(2) &&
		 this->m_3.getType() == face.getBlockType(3))
	{
			return true;
	}
	return false;
}
bool Face::connected()
{
	//return true if current Face is connected to a neighborFace
	if(neighborFace != NULL)
		return true;
	else
		return false;
}
