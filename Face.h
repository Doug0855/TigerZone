#pragma once
#include "Block.h"


class Face{
	public:
		Face();
		~Face();
		
		Face* neighborFace;
		Face* inwardAcrossFace;
		Face* inwardLeftFace;
		Face* inwardRightFace;

		std::string getType();
		void setType(std::string);
		
		bool faceEquals(Face face);	//determines if two faces are equal
		bool connected(); ///< returns false if not connected
	
	private:		
		std::string type;	
};

