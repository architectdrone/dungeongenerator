#include "Tileset.h"
#include "Tile.h"
#include "Board.h"

Board::Board(int x, int y) 
{
	x_size = x;
	y_size = y;
	Tileset* toReturn = new Tileset;
	for (int y = 0; y < y_size; y++)
	{
		for (int x = 0; x < x_size; x++)
		{
			Tile* newTile = new Tile(x, y);
		}
	}
}

Board::Board(int size) 
{
	x_size = size;
	y_size = size;
	for (int y = 0; y < y_size; y++)
	{
		for (int x = 0; x < x_size; x++)
		{
			Tile* newTile = new Tile(x, y);
		}
	}
}