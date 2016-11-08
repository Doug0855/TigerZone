#inlcude "Face.h"

Face::Face()
{
	neighborFace = NULL;
}

Face::~Face()
{
	neighborFace = NULL;
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

bool Face::connected()
{
	if(!m_1.connected() && !m_2.connected() && !m_3.connected()) return false;
	return true;
}
