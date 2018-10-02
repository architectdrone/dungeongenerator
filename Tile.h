#ifndef TILE_H
#define TILE_H

class Tile
{
private:
	bool isWall;
	int x;
	int y;
	Board* parentBoard;
public:
	//CONSTRUCTOR
	Tile(int p_x, int p_y, Board* newBoard);

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
