#this target will compile all files
all: TigerZone	

TigerZone: main.o Game.o TileStack.o Face.o Block.o Player.o Board.o Tile.o Meeple.o
	g++ -o main.o Game.o TileStack.o Face.o Block.o Player.o Board.o Tile.o Meeple.o

main.o: main.cpp
	g++ -std=c++11 main.cpp

Game.o: Game.cpp
	g++ -std=c++11 -c Game.cpp 

TileStack.o: TileStack.cpp
	g++ -std=c++11 -c TileStack.cpp

Face.o: Face.cpp
	g++ -std=c++11 -c Face.cpp

Block.o: Block.cpp
	g++ -std=c++11 -c Block.cpp

Player.o: Player.cpp
	g++ -std=c++11 -c Player.cpp

Board.o: Board.cpp
	g++ -std=c++11 -c Board.cpp

Tile.o: Tile.cpp
	g++ -std=c++11 -c Tile.cpp

Meeple.o: Meeple.cpp
	g++ -std=c++11 -c Meeple.cpp

clean:
	rm -rf *o menu
	
