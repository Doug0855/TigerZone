#this target will compile all files
all: TigerZone

TigerZone: main.o TileStack.o Face.o Block.o  Board.o Tile.o
	g++ main.o TileStack.o Face.o Block.o Board.o Tile.o -o tiger.out

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

Board.o: Board.cpp
	g++ -std=c++11 -c Board.cpp

#Game.o: Game.cpp
#	g++ -std=c++11 -c Game.cpp

#Player.o: Player.cpp
#	g++ -std=c++11 -c Player.cpp

#Meeple.o: Meeple.cpp
#	g++ -std=c++11 -c Meeple.cpp

Tile.o: Tile_Structure/Tile.cpp
	g++ -std=c++11 -c Tile_Structure/Tile.cpp

TileStack.o: Tile_Structure/TileStack.cpp
	g++ -std=c++11 -c Tile_Structure/TileStack.cpp

Face.o: Tile_Structure/Face.cpp
	g++ -std=c++11 -c Tile_Structure/Face.cpp

Block.o: Tile_Structure/Block.cpp
	g++ -std=c++11 -c Tile_Structure/Block.cpp

clean:
	rm -rf *o tiger.out
