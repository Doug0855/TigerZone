#include "Face.h"

Face::Face(Block &b1, Block &b2, Block &b3, Face &accross_face, Face &left_face, Face &right_face)
{
	m_1 = &b1;
	m_2 = &b2;
	m_3 = &b3;
  //meeple = false;
  visited = false;
	neighborFace = NULL;
  inwardAcrossFace = &accross_face;
  inwardLeftFace = &left_face;
  inwardRightFace = &right_face;
	this->type = m_2->getType();
}
//Face::Face(std::string faceType)
//{
//	this->type = faceType;
//	neighborFace = NULL;
//}
Face::Face()
{
	neighborFace = NULL;
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
    return this->m_1->getType();
  else if (block == 2)
    return this->m_2->getType();
  else if (block == 3)
    return this->m_3->getType();
  else
    return "";
}
// void Face::placeMeeple()
// {
//   meeple = true;
// }
void Face::visit()
{
  visited = true;
}
bool Face::hasMeeple()
{
	if (m_1->hasMeeple() || m_2->hasMeeple() || m_3->hasMeeple())
	{
		//std::cout << "block 1 has meeple? " << m_1->hasMeeple() << std::endl;
		//std::cout << "block 2 has meeple? " << m_2->hasMeeple() << std::endl;
		//std::cout << "block 3 has meeple? " << m_3->hasMeeple() << std::endl;
		return true;
	}
	else
		return false;

}
void Face::setType(Block &b1, Block &b2, Block &b3) {
  this->m_1 = &b1;
	this->m_2 = &b2;
	this->m_3 = &b3;
	this->type = m_2->getType();
}
bool Face::faceEquals(Face face)
{
	if(this->type == face.getType())
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
