#include "Tile.h"
#include "Face.h"

class UnitTester {
public:
	// Constructor & Destructor 
	UnitTester();
	~UnitTester();

	// Methods for Face
	std::vector<bool> createFace();			// Tests constructors
	std::vector<bool> internalPointers();	// Tests internal pointers
	std::vector<bool> externalPointer();	// Tests external pointers

	// Methods for Tile
	std::vector<bool> createTile();			// Tests constructor 
	std::vector<bool> rotateTest();
	std::vector<bool> openFacesTest();
	std::vector<bool> connectedFacesTest();

	// Other Methods
	void runTests();						// Executes tests
	void printResults(std::vector<bool> &v);// Prints vector containing results

private:
	
};