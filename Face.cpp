#include "Face.h"
#include <iostream>

Face::Face()
{
	neighborFace = NULL;
	inwardAcrossFace = NULL;
	inwardLeftFace = NULL;
	inwardRightFace = NULL;

}

Face::~Face()
{
	neighborFace = NULL;
}

std::string Face::getType() {
	return this->type;
}

void Face::setType(std::string newType) {
	this->type = newType;
	return;
}

bool Face::faceEquals(Face face)
{
	if(this->type == face.type)
	{
			return true;
	}	
	return false;
}

bool Face::connected()
{
	// std::cout<<"Neighborface is "<<neighborFace<<std::endl;
	if(neighborFace != NULL) 
		return true;
	else
		return false;
	// if(!m_1.connected() && !m_2.connected() && !m_3.connected()) return false;
	// return true;
}
