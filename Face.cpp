#inlcude "Face.h"

Face::Face()
{
	
}

Face::~Face()
{
	
}

bool Face::faceEquals(Face face)
{
	if(this->m_1.getType == face.m_1.getType &&
		this->m_2.getType == face.m_2.getType &&
		this->m_3.getType == face.m_3.getType)
		{
			return true;
		}
		
	return false;
}
