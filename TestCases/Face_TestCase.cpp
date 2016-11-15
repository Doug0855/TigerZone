#include "Face.h"
#include <iostream>

int main ()
{
	std::cout << "******************************" << std::endl;
	std::cout << "*     Testing Face Class     *" << std::endl;
	std::cout << "******************************" << std::endl;

	Face up_face('j', 'j', 'j');
	Face down_face('l', 'l', 'l');
	Face left_face('l', 'l', 'l');
	Face right_face('j', 'j', 'j');
	Face x_face;

	std::string blockType1, blockType2, blockType3, blockType4, blockType5;
	blockType1 = up_face.m_1.getType();
	blockType2 = down_face.m_2.getType();
	blockType3 = left_face.m_3.getType();
	blockType4 = right_face.m_1.getType();
	blockType5 = x_face.m_1.getType();

	std::cout << "Block1 type value is: " << blockType1 << std::endl;
	std::cout << "Block2 type value is: " << blockType2 << std::endl;
	std::cout << "Block3 type value is: " << blockType3 << std::endl;
	std::cout << "Block4 type value is: " << blockType4 << std::endl;
	std::cout << "Block5 type value is: " << blockType5 << std::endl;
	return 0;
}
