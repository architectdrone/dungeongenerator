/**
* @author Owen Mellema
* @file Tile.h
* @date 10-02-18
* @brief A set of tiles. (See tiles.h)
**/

#ifndef TILESET_H
#define TILESET_H
#include "Tile.h"
#include <list>
#include <iostream>

class Tileset
{
private:
	std::list <Tile*> * allTiles;

public:
	//CONSTRUCTOR
	Tileset();
	//Copy constructor here

	//DESTRUCTOR
	~Tileset();
	void destroyTiles(); //Deletes all tiles within the tileset. Careful: This deletes all tiles within, even those used by other tilesets!

	//GETTERS
	Tileset* getAllWalls(); //Returns a tileset containing all walls within the original tileset.
	Tileset* getAllNonWalls(); //Returns a tileset containing all non-walls within the original tileset.
	Tileset* getAllX(int x); //Returns a tileset containing all tiles with the given x-coordinate within the original tileset.
	Tileset* getAllY(int y); //Returns a tileset containing all tiles with the given y-coordinate within the original tileset.
	Tile* getXY(int x, int y) throw(std::out_of_range); //Returns the tile with the given x and y coordinates. If none is found, throw an error.
	Tile* getTile(int i) throw(std::out_of_range); //Gets the ith tile. Remember, the first tile is at 0, the last is at len-1. Throws error if out of bounds.
	int getLength(); //Returns the length of the tileset.
	std::list<Tile*>* getTileList(); //Returns the tiles in list format. 

	//SETTERS
	void setAllWall(); //Sets all tiles in the tileset to be walls.
	void setAllNonWall(); //Sets all tiles in the tileset to be non-walls.

	//TESTERS
	bool isInTileset(Tile *myTile); //Tests to see whether or not the given tile is in the tileset.
	bool isInTileset(int x, int y); //Tests to see whether or not the given coord is in the tileset.

	//CLASS SPECIFIC
	void add(Tile *newTile); //Adds the newTile to tileset.
	void add(Tileset *newTileset); //Adds the entirety of the tileset to the original tileset.
};

#endif

