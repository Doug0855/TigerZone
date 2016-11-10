#include "Face.h"
#include <iostream>

Face::Face()
{
	neighborFace = NULL;

	m_1.setType("city");
	m_2.setType("ground"); 
	m_3.setType("city");
}

Face::~Face()
{
	neighborFace = NULL;
}

bool Face::faceEquals(Face face)
{
	if(this->m_1.getType() == face.m_1.getType() &&
		this->m_2.getType() == face.m_2.getType() &&
		this->m_3.getType() == face.m_3.getType())
	{
		std::cout<<"These two faces were EQUAL"<<std::endl;
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
