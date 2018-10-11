/**
* @author Owen Mellema
* @file Tile.h
* @date 10-02-18
* @brief A single tile. A "tile" could be anything, but I think of them as being game objects. Generally, they are boolean values (either "wall" or not "wall" in 2D space.)
**/


#ifndef TILE_H
#define TILE_H

class Tile
{
private:
	bool isWall;
	int x;
	int y;
public:
	//CONSTRUCTOR
	/**
	* @param p_x: The tile's X-Coordinate
	* @param p_y: the Tile's Y-Coordinate
	**/
	Tile(int p_x, int p_y);

	//GETTERS
	/**
	* @return true if it is currently a wall, false if it is not currently a wall.
	**/
	bool getWall();
	/**
	* @return Tile's X-Coordinate
	**/
	int getX();
	/**
	* @return Tile's Y-Coordinate
	**/
	int getY();

	//SETTERS
	/**
	* @param The desired state of the wall (true for wall, false for not wall)
	* @post The status of the wall is now determined by the parameter.
	**/
	void setWall(bool wall); //If wall is true, set the tile to be a wall. If false, set it not to be a wall.

	//MAKERS
	/**
	* @post Tile is a wall
	**/
	void makeWall();
	/**
	* @post Tile is not a wall
	**/
	void makeNonWall(); //Sets the tile to be a non-wall.
};

#endif
