#include "Face.h"

Face::Face(std::string faceType)
{
	type = faceType;
	neighborFace = NULL;
}
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
// std::string Face::getBlockType(int block)
// {
//   if (block == 1)
//     return this->m_1.getType();
//   else if (block == 2)
//     return this->m_2.getType();
//   else if (block == 3)
//     return this->m_3.getType();
//   else
//     return "";
// }
// void Face::placeMeeple()
// {
//   meeple = true;
// }
// void Face::visit()
// {
//   visited = true;
// }

void Face::setType(std::string type) {
  this->type = type;
}
bool Face::faceEquals(Face face)
{
	if(this->getType() == face.getType())
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




