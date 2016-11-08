#this target will compile all files
all: TigerZone

TigerZone: main.o Game.o TileStack.o Face.o Block.o Player.o Board.o Tile.o Meeple.o
	g++ -o main.o Game.o TileStack.o Face.o Block.o Player.o Board.o Tile.o Meeple.o

main.o: main.cpp
	g++ main.cpp

Game.o: Game.cpp
	g++ -c Game.cpp 

TileStack.o: TileStack.cpp
	g++ -c TileStack.cpp

Face.o: Face.cpp
	g++ -c Face.cpp

Block.o: Block.cpp
	g++ -c Block.cpp

Player.o: Player.cpp
	g++ -c Player.cpp

Board.o: Board.cpp
	g++ -c Board.cpp

Tile.o: Tile.cpp
	g++ -c Tile.cpp

Meeple.o: Meeple.cpp
	g++ -c Meeple.cpp

clean:
	rm -rf *o menu
	
