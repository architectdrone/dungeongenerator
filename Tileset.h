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
	Tileset(const Tileset &oldTileset); //Copys elements of allTiles, does NOT copy tiles.

	//DESTRUCTOR
	~Tileset();
	/**
	* @post: Deletes all of the tiles from the heap.
	**/
	void destroyTiles(); 
	
	//GETTERS
	/**
	* @return A Tileset containing all walls within the original tileset.
	**/
	Tileset* getAllWalls();
	/**
	* @return A Tileset containing all non-walls within the original tileset.
	**/
	Tileset* getAllNonWalls();
	/**
	* @return a tileset containing all tiles with the given x-coordinate within the original tileset.
	**/
	Tileset* getAllX(int x);
	/**
	* @return a tileset containing all tiles with the given y-coordinate within the original tileset.
	**/
	Tileset* getAllY(int y); 
	/**
	* @pre There is a tile at the specified x and y coordinates
	* @return the tile with the given x and y coordinates.
	* @throw Throws an error if no tile is found at the specified X and Y coordinates
	**/
	Tile* getXY(int x, int y) throw(std::out_of_range);
	/**
	* @pre There is a tile at the specified i.
	* @return the ith tile. Remember, the first tile is at 0, the last is at len-1.
	* @throw Throws error if out of bounds.
	**/
	Tile* getTile(int i) throw(std::out_of_range);
	/**
	* @return the length of the tileset
	**/
	int getLength(); //Returns the length of the tileset.
	/**
	* @return the list of tiles in list format
	**/
	std::list<Tile*>* getTileList() const; 

	//SETTERS
	/**
	* @post All tiles in the tileset are now walls.
	**/
	void setAllWall();
	/**
	* @post All tiles in the tileset are now non-walls.
	**/
	void setAllNonWall(); 

	//TESTERS
	/**
	* @return true if the tile is in the tileset, false otherwise
	**/
	bool isInTileset(Tile *myTile); 
	/**
	* @return true if there is a in the tileset at the given X and Y coordinates, false otherwise
	**/
	bool isInTileset(int x, int y); //Tests to see whether or not the given coord is in the tileset.

	//CLASS SPECIFIC
	/**
	* @param newTile: The tile to add to the Tileset.
	* @post newTile is now a part of the tileset.
	**/
	void add(Tile *newTile);
	/**
	* @param newTileset: The Tileset to add to the Tileset.
	* @post All of the elements of newTileset are now a part of the tileset.
	**/
	void add(Tileset *newTileset); 
	/**
	* @param newTile: The Tileset to add to the Tileset.
	* @post Tile is added to the tileset without checking to see if it already a part of the tileset.
	**/
	void addNoCheck(Tile *newTile);
	/**
	* @param toRemove: The Tile to remove from the Tileset.
	* @post toRemove is now no longer a part of the tileset.
	**/
	void remove(Tile* toRemove);
	/**
	* @param toRemove: The Tileset to remove from the Tileset.
	* @post None of the elements of toRemove are a part of the tileset.
	**/
	void remove(Tileset* toRemove);
};

#endif

