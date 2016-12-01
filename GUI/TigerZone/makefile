#this target will compile all files
all: TigerZone

TigerZone: main.o Game.o Board.o Player.o Meeple.o Farmer.o Monk.o TileStack.o Tile.o Face.o Block.o
	g++ main.o Game.o Board.o Player.o Meeple.o Farmer.o Monk.o TileStack.o Tile.o Face.o Block.o -o tiger.out

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

Game.o: Game.cpp
	g++ -std=c++11 -c Game.cpp

Board.o: Board.cpp
	g++ -std=c++11 -c Board.cpp

Player.o: Player.cpp
	g++ -std=c++11 -c Player.cpp

Meeple.o: Meeple.cpp
	g++ -std=c++11 -c Meeple.cpp

Farmer.o: Farmer.cpp
	g++ -std=c++11 -c Farmer.cpp

Monk.o: Monk.cpp
	g++ -std=c++11 -c Monk.cpp

TileStack.o: Tile_Structure/TileStack.cpp
	g++ -std=c++11 -c Tile_Structure/TileStack.cpp

Tile.o: Tile_Structure/Tile.cpp
	g++ -std=c++11 -c Tile_Structure/Tile.cpp

Face.o: Tile_Structure/Face.cpp
	g++ -std=c++11 -c Tile_Structure/Face.cpp

Block.o: Tile_Structure/Block.cpp
	g++ -std=c++11 -c Tile_Structure/Block.cpp

clean:
	rm -rf *o tiger.out
