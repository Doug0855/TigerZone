#include "Block.h"
#include <iostream>

int main ()
{
	std::cout << "******************************" << std::endl;
	std::cout << "*     Testing Block Class    *" << std::endl;
	std::cout << "******************************" << std::endl;

    Block block_face1('j');
    Block block_face2('l');
    Block block_face3('t');
    Block block_face4('d');
    Block block_center;

    std::string blockType1, blockType2, blockType3, blockType4, blockType5;
    blockType1 = block_face1.getType();
    blockType2 = block_face2.getType();
    blockType3 = block_face3.getType();
    blockType4 = block_face4.getType();
    blockType5 = block_center.getType();

    std::cout << "Block1 type value is: " << blockType1 << std::endl;
    std::cout << "Block2 type value is: " << blockType2 << std::endl;
    std::cout << "Block3 type value is: " << blockType3 << std::endl;
    std::cout << "Block4 type value is: " << blockType4 << std::endl;
    std::cout << "Block5 type value is: " << blockType5 << std::endl;
    return 0;
}
