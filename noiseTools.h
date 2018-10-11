#ifndef NOISETOOLS_H
#define NOISETOOLS_H
#include "Tile.h"
#include "Tileset.h"
#include "Board.h"

/**
* @pre Board has outer walls.
* @pre Board is empty except for outer walls.
* @param theBoard: The board to add straights to.
* @param number: The upper limit of straights to add.
* @post A number of straights (0 < #newStraights <= number) has been added to the board. The reason it isn't equal is because of an algorithim bug.
**/
void addStraights(Board* theBoard, int number);
/**
* @param startTile: The tile that we are starting at.
* @param goingRight: Whether the straight will be going rightwards or downwards.
* @param theBoard: The board containing all of the tiles.
* @return A tileset containing a new straight
**/
Tileset* straightGenerator(Board* theBoard, Tile* startTile, bool goingRight);


#endif