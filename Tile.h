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
	Tile(int p_x, int p_y);

	//GETTERS
	bool getWall(); //Returns true if the tile is currently a wall, returns false otherwise.
	int getX(); //Returns the X coordinate of the tile.
	int getY(); //Returns the Y coordinate of the tile.

	//SETTERS
	void setWall(bool wall); //If wall is true, set the tile to be a wall. If false, set it not to be a wall.

	//MAKERS
	void makeWall(); //Sets the tile to be a wall.
	void makeNonWall(); //Sets the tile to be a non-wall.
};

#endif 
