#include "../Face.h"
#include <iostream>

int main ()
{
	//g++ Block.h Block.cpp Face.h Face.cpp Face_TestCase.cpp -o FaceTest.out
	std::cout << "******************************" << std::endl;
	std::cout << "*     Testing Face Class     *" << std::endl;
	std::cout << "******************************" << std::endl;
	Face up_face, down_face, left_face, right_face, x_face, y_face, z_face, w_face;
	Face *NULL_face = NULL;
	
	up_face = Face('j', 't', 'j', down_face, right_face, left_face);
	down_face = Face('l', 'l', 'l', up_face, left_face, right_face);
	left_face = Face('l', 'l', 'l', right_face, up_face, down_face);
	right_face = Face('j', 'j', 'j', left_face, down_face, right_face);
	x_face = Face('j', 't', 'j', y_face, z_face, w_face);
	y_face = Face('j', 't', 'j', *NULL_face, z_face, w_face);

	std::string blockType1, blockType2, blockType3, blockType4, blockType5, blockType6, blockType7, blockType8;
	blockType1 = up_face.getBlockType(1);				//get first block type
	blockType2 = down_face.getBlockType(2);			//get second block type
	blockType3 = left_face.getBlockType(3);			//get third block type
	blockType4 = w_face.getBlockType(3);				//get block type from default initialized face
	blockType5 = up_face.getAccrossFace()->getBlockType(1);		//get first block type from accross face
	blockType6 = up_face.getAccrossFace()->getAccrossFace()->getBlockType(2);		//get second block type from current face by backwards traversal

	if (up_face.faceEquals(x_face)) 						//if faces equal each other set each other as neighborFace
	{
		x_face.setNeighborFace(up_face);
		up_face.setNeighborFace(x_face);
	}
	if (x_face.connected())
	{
		blockType7 = x_face.getNeighborFace()->getBlockType(2); //get second block type for initialized neighborFace
		blockType8 = up_face.getNeighborFace()->getAccrossFace()->getBlockType(3); 	//get second block type from uninitialized neighborFace
	}

	std::cout << "Block1 type value is: " << blockType1 << std::endl;
	std::cout << "Block2 type value is: " << blockType2 << std::endl;
	std::cout << "Block3 type value is: " << blockType3 << std::endl;
	std::cout << "Block4 type value is: " << blockType4 << std::endl;
	std::cout << "Block5 type value is: " << blockType5 << std::endl;
	std::cout << "Block6 type value is: " << blockType6 << std::endl;
	std::cout << "Block7 type value is: " << blockType7 << std::endl;
	std::cout << "Block8 type value is: " << blockType8 << std::endl;

	if (y_face.getNeighborFace() == NULL)
		std::cout << "checking NULL face comparison!" << std::endl;
	std::cout << "faceEquals test: " << up_face.faceEquals(x_face) << std::endl;
	std::cout << "faceEquals test: " << up_face.faceEquals(y_face) << std::endl;
	std::cout << "unchanged visited value: " << up_face.hasBeenVisited() << std::endl;
	x_face.getNeighborFace()->visit();
	std::cout << "changed visited value: " << up_face.hasBeenVisited() << std::endl;

	std::cout << "NULL value is: " << NULL_face << std::endl;

	return 0;
}
