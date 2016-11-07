#this target will compile all files
all : TigerZone

TigerZone: Game.o TileStack.o Face.o Block.o Player.o Board.o Tile.o Meeple.o

g++ Game.o TileStack.o Face.o Block.o Player.o Board.o Tile.o Meeple.o

Game.o: Game.cpp
	g++ -c Game.o 

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
	
