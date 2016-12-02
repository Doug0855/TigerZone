#include "Tile.h"
#include "Face.h"
#include "TileStack.h"
#include "Board.h"

class UnitTester {
public:
	// Constructor & Destructor 
	UnitTester();
	~UnitTester();

	// Methods for Face
	std::vector<bool> createFace();
	std::vector<bool> internalPointers();
	std::vector<bool> externalPointer();

	// Methods for Tile
	std::vector<bool> createTile();
	std::vector<bool> rotateTest();
	std::vector<bool> openFacesTest();
	std::vector<bool> connectedFacesTest();

	// Methods for TileStack
	std::vector<bool> createTileStack();
	std::vector<bool> drawTileTest();
	std::vector<bool> shuffleTest();

	// Other Methods
	void runTests();						// Executes tests
	void printResults(std::vector<bool> &v);// Prints vector containing results

private:
	
};