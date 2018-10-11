/**
* @author Owen Mellema
* @file Board.h
* @date 10-04-18
* @brief A grid of tiles encompassing a certain range in the 2D plane
**/

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
	/**
	* @pre X and Y are greater than 0
	* @param X:  X is the size of the board in the X direction
	* @param Y: Y is the size of the board in the X direction
	**/
	Board(int x, int y);
	/**
	* @pre size are greater than 0
	* @param size:  size is the size of the board in the X and Y directions
	**/
	Board(int size);

	//DESTRUCTORS
	/**
	* @post Board is deleted, AND all tiles inside are destroyed.
	**/
	~Board();

	//GETTERS
	/**
	* @return A tileset containing all tiles within the board.
	**/
	Tileset* getAllTiles();
	/**
	* @return A tileset containing all tiles in the outside wall, EVEN IF IT HAS NOT BEEN CREATED YET!
	**/
	Tileset* getOuterWall();
	/**
	* @return Size in the X direction
	**/
	int getXSize();
	/**
	* @return Size in the Y direction
	**/
	int getYSize();

	//CLASS SPECIFIC
	/**
	* @post Walls now encompass the board.
	**/
	void addOuterWalls(); //Adds outer walls to the board

};

#endif
