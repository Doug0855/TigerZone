#include "UnitTester.h"

UnitTester::UnitTester() {}

UnitTester::~UnitTester() {}

std::vector<bool> UnitTester::createFace() 
{
	// Vector to store results
	std::vector<bool> results;
	
	// Test 0: Create face
	try {
		Face testFace;
		results.push_back(true);
	} catch (bool result) {
		results.push_back(result);
	}

	// Test 1: Create face with assigned values
	try {
		Face testFace(NULL, "Jungle", "Boar");
		results.push_back(true);
	} catch (bool result) {
		results.push_back(false);
	}

	// Test 2: Create face with more values
	try {
		Face testFace(NULL, NULL, NULL, NULL, "Lake", "Deer");
		results.push_back(true);
	} catch (bool result) {
		results.push_back(false);
	}

	return results;
}

std::vector<bool> UnitTester::internalPointers() 
{
	// Vector to store results
	std::vector<bool> results;

	// Create testFace and other faces
	Face* left = new Face(NULL, "Lake", "None");
	Face* right = new Face(NULL, "Jungle", "Boar");
	Face* opposite = new Face(NULL, "Path", "Deer");
	Face testFace(NULL, left, right, opposite, "Lake", "Deer");

	// Conduct tests
	if (testFace.getLeft()->getType() == "Lake" && !testFace.getLeft()->hasAnimal())
		results.push_back(true);
	else
		results.push_back(false);

	if (testFace.getRight()->getType() == "Jungle" && testFace.getRight()->hasAnimal())
		results.push_back(true);
	else
		results.push_back(false);

	if (testFace.getOpposite()->getType() == "Path" && testFace.getOpposite()->hasAnimal())
		results.push_back(true);
	else
		results.push_back(false);

	return results;
}

std::vector<bool> UnitTester::externalPointer() 
{
	// Vector to store results
	std::vector<bool> results;

	// Create testFace
	Face testFace(NULL, "Lake", "Deer");

	// Conduct tests
	if (testFace.getExternal() == NULL)
		results.push_back(true);
	else
		results.push_back(false);

	// Create face to point to
	Face* externalFace = new Face(NULL, "Lake", "None");
	testFace.setExternal(externalFace);

	if (testFace.getExternal()->getType() == "Lake" && !testFace.getExternal()->hasAnimal())
		results.push_back(true);
	else
		results.push_back(false);

	return results;
}

std::vector<bool> UnitTester::createTile() 
{
	// Vector to store results
	std::vector<bool> results;
	
	// Test 0
	Tile testTile0;
	if (!testTile0.getDen())
		results.push_back(true);
	else
		results.push_back(false);
	
	// Test 1
	Face* testUp;
	Face* testDown;
	Face* testLeft;
	Face* testRight;
	Tile testTile1(testUp, testDown, testLeft, testRight, true, false);

	if (testTile1.getDen())
		results.push_back(true);
	else
		results.push_back(false);

	return results;
}

std::vector<bool> UnitTester::rotateTest() 
{
	// Vector to store results
	std::vector<bool> results;

	// Construct faces for tile
	Face* up = new Face(NULL, "Lake", "Deer");
	Face* down = new Face(NULL, "Lake", "None");
	Face* left = new Face(NULL, "Jungle", "None");
	Face* right = new Face(NULL, "Jungle", "None");
	
	up->setInternalPointer("o", down);
	down->setInternalPointer("o", up);

	// Create tile and rotate
	Tile testTile(up, down, left, right, false, true);
	testTile.rotate();

	if (testTile.getUpFace()->getType() == "Jungle"   && 
		testTile.getDownFace()->getType() == "Jungle" && 
		testTile.getLeftFace()->getType() == "Lake"   && 
		testTile.getRightFace()->getType() == "Lake")
		results.push_back(true);
	else
		results.push_back(false);

	// Another rotate
	testTile.rotate();
	if (testTile.getUpFace()->getType() == "Lake"   	&& 
		testTile.getDownFace()->getType() == "Lake" 	&& 
		testTile.getLeftFace()->getType() == "Jungle"   && 
		testTile.getRightFace()->getType() == "Jungle")
		results.push_back(true);
	else
		results.push_back(false);

	// Another rotate
	testTile.rotate();
	if (testTile.getUpFace()->getType() == "Jungle"   &&
		testTile.getDownFace()->getType() == "Jungle" && 
		testTile.getLeftFace()->getType() == "Lake"   && 
		testTile.getRightFace()->getType() == "Lake")
		results.push_back(true);
	else
		results.push_back(false);

	return results;
}

std::vector<bool> UnitTester::openFacesTest() 
{
	// Vector to store results
	std::vector<bool> results;

	// Construct faces for tile
	Face* up = new Face(NULL, "Lake", "Deer");
	Face* down = new Face(NULL, "Lake", "None");
	Face* left = new Face(NULL, "Jungle", "None");
	Face* right = new Face(NULL, "Jungle", "None");
	Face* external = new Face();
	
	// Set internal pointers
	up->setInternalPointer("o", down);
	down->setInternalPointer("o", up);

	// Create tile and get faces
	Tile testTile(up, down, left, right, false, true);
	std::vector<Face*> openFaces;
	openFaces = testTile.getOpenFaces();

	if (openFaces.size() == 4)
		results.push_back(true);
	else
		results.push_back(false);

	// Change external pointer
	testTile.getUpFace()->setExternal(external);
	openFaces.clear();
	openFaces = testTile.getOpenFaces();

	if (openFaces.size() == 3)
		results.push_back(true);
	else
		results.push_back(false);

	// Change external pointer
	testTile.getLeftFace()->setExternal(external);
	openFaces.clear();
	openFaces = testTile.getOpenFaces();

	if (openFaces.size() == 2)
		results.push_back(true);
	else
		results.push_back(false);

	return results;
}

std::vector<bool> UnitTester::connectedFacesTest() 
{
	// Vector to store results
	std::vector<bool> results;

	// Construct faces for tile
	Face* up = new Face(NULL, "Lake", "Deer");
	Face* down = new Face(NULL, "Lake", "None");
	Face* left = new Face(NULL, "Jungle", "None");
	Face* right = new Face(NULL, "Jungle", "None");
	Face* external = new Face();
	
	// Set internal pointers
	up->setInternalPointer("o", down);
	down->setInternalPointer("o", up);

	// Create tile and get faces
	Tile testTile(up, down, left, right, false, true);
	std::vector<Face*> connectedFaces;
	connectedFaces = testTile.getConnected(testTile.getUpFace());

	if (connectedFaces.size() == 1)
		results.push_back(true);
	else
		results.push_back(false);

	connectedFaces.clear();
	connectedFaces = testTile.getConnected(testTile.getDownFace());
	if (connectedFaces.size() == 1)
		results.push_back(true);
	else
		results.push_back(false);

	return results;
}

std::vector<bool> UnitTester::createTileStack() 
{
	// Vector to store results
	std::vector<bool> results;

	// Create tileStack with 10 tiles
	TileStack testStack(10);
	if (testStack.isEmpty() == false)
		results.push_back(true);
	else
		results.push_back(false);

	if (!testStack.getTile(0)->getDen())
		results.push_back(true);
	else
		results.push_back(false);

	// Create standard tileStack 
	TileStack testStack1;
	if (testStack1.getStackSize() == 76)
		results.push_back(true);
	else
		results.push_back(false);


	return results;
}

std::vector<bool> UnitTester::drawTileTest() 
{
	// Vector to store results
	std::vector<bool> results;

	// Create stack and draw card
	TileStack testStack(10);
	int initSize = testStack.getStackSize();
	testStack.getTile(9)->getUpFace()->setType("Jungle");
	Tile* drawnTile = testStack.drawTile();

	if (testStack.getStackSize() == initSize)
		results.push_back(false);
	else
		results.push_back(true);

	if (drawnTile->getUpFace()->getType() == "Jungle")
		results.push_back(true);
	else
		results.push_back(false);

	return results;
}

std::vector<bool> UnitTester::shuffleTest() {
	// Vector to store results
	std::vector<bool> results;

	// Create stack and shuffle
	TileStack testStack(10);
	for (int i = 0; i < testStack.getStackSize(); i++) {
		if (i%2 == 0)
			testStack.getTile(i)->getUpFace()->setType("Jungle");
		else if (i%2 != 0 && i%3 == 0)
			testStack.getTile(i)->getUpFace()->setType("Lake");
		else if (i == 7)
			testStack.getTile(i)->getUpFace()->setType("None");
		else
			testStack.getTile(i)->getUpFace()->setType("Path");
	}

	// Get position of changed tile to make sure not in same place
	int position = -1;
	testStack.shuffle();
	for (int i = 0; i < testStack.getStackSize(); i++) {
		if (testStack.getTile(i)->getUpFace()->getType() == "None")
			position = i;
	}

	if (position == 7)
		results.push_back(false);
	else
		results.push_back(true);


	return results;
}

std::vector<bool> UnitTester::insertTileTest()
{
	// Vector to store results
	std::vector<bool> results;

	return results;
}	

void UnitTester::printResults(std::vector<bool> &v) 
{
	// Prints contents of vector
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == true)
			std::cout<<"Test "<<i<<": PASS"<<std::endl;
		else
			std::cout<<"Test "<<i<<": FAIL"<<std::endl;
	}
}

void UnitTester::runTests() 
{
	// Executes tests
	std::vector<bool> myVector;
	myVector = createFace();
	std::cout<<"Conducting createFace tests..."<<std::endl;
	printResults(myVector);

	std::cout<<std::endl;
	std::cout<<"Conducting externalPointer tests..."<<std::endl;
	myVector.clear();
	myVector = externalPointer();
	printResults(myVector);

	std::cout<<std::endl;
	std::cout<<"Conducting internalPointers tests..."<<std::endl;
	myVector.clear();
	myVector = internalPointers();
	printResults(myVector);

	std::cout<<std::endl;
	std::cout<<"Conducting createTile tests..."<<std::endl;
	myVector.clear();
	myVector = createTile();
	printResults(myVector);

	std::cout<<std::endl;
	std::cout<<"Conducting rotateTile tests..."<<std::endl;
	myVector.clear();
	myVector = rotateTest();
	printResults(myVector);

	std::cout<<std::endl;
	std::cout<<"Conducting getOpenFaces tests..."<<std::endl;
	myVector.clear();
	myVector = openFacesTest();
	printResults(myVector);

	std::cout<<std::endl;
	std::cout<<"Conducting getConnectedFaces tests..."<<std::endl;
	myVector.clear();
	myVector = connectedFacesTest();
	printResults(myVector);

	std::cout<<std::endl;
	std::cout<<"Conducting createTileStack tests..."<<std::endl;
	myVector.clear();
	myVector = createTileStack();
	printResults(myVector);

	std::cout<<std::endl;
	std::cout<<"Conducting drawTileTest tests..."<<std::endl;
	myVector.clear();
	myVector = drawTileTest();
	printResults(myVector);

	std::cout<<std::endl;
	std::cout<<"Conducting shuffleTest tests..."<<std::endl;
	myVector.clear();
	myVector = shuffleTest();
	printResults(myVector);

	std::cout<<std::endl;
	std::cout<<"Conducting createBoard tests..."<<std::endl;
	myVector.clear();
	myVector = createBoard();
	printResults(myVector);
}