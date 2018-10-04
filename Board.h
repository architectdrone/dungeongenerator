#ifndef BOARD_H
#define BOARD_H
#include "Tileset.h"
#include "Tile.h"

class Board
{
private:
	Tileset* boardTileset;
	Tileset* outerWalls;
	int x_size;
	int y_size;

public:
	//CONSTRUCTORS
	Board(int x, int y);

	//DESTRUCTORS
	~Board();

	//GETTERS
	Tileset* getAllTiles();

	//CLASS SPECIFIC
	void addOuterWalls();

};

#endif