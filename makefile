#this target will compile all files
all: TigerZone

TigerZone: main.o Adapter.o Network.o Game.o Board.o Player.o Meeple.o TileStack.o Tile.o Face.o Block.o Structure.o
	g++ main.o Adapter.o Game.o Network.o Board.o Player.o Meeple.o TileStack.o Tile.o Face.o Block.o Structure.o -o tiger.out

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

Adapter.o: Adapter.cpp
	g++ -std=c++11 -c Adapter.cpp

Network.o: Network.cpp
	g++ -std=c++11 -c Network.cpp

Game.o: Game.cpp
	g++ -std=c++11 -c Game.cpp

Board.o: Board.cpp
	g++ -std=c++11 -c Board.cpp

Player.o: Player.cpp
	g++ -std=c++11 -c Player.cpp

Meeple.o: Meeple.cpp
	g++ -std=c++11 -c Meeple.cpp

TileStack.o: Tile_Structure/TileStack.cpp
	g++ -std=c++11 -c Tile_Structure/TileStack.cpp

Tile.o: Tile_Structure/Tile.cpp
	g++ -std=c++11 -c Tile_Structure/Tile.cpp

Face.o: Tile_Structure/Face.cpp
	g++ -std=c++11 -c Tile_Structure/Face.cpp

Block.o: Tile_Structure/Block.cpp
	g++ -std=c++11 -c Tile_Structure/Block.cpp

Structure.o: Tile_Structure/Structure.cpp
	g++ -std=c++11 -c Tile_Structure/Structure.cpp

clean:
	rm -rf *o tiger.out
