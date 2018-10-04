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
	Board(int x, int y); //Creates a board of size x_size*y_size
	Board(int size); //Creates a board of size size*size

	//DESTRUCTORS
	~Board();

	//GETTERS
	Tileset* getAllTiles(); //Returns the internal Tileset

	//CLASS SPECIFIC
	void addOuterWalls(); //Adds outer walls to the board

};

#endif