#include "Tileset.h"
#include "Tile.h"
#include <list>
#include <iostream>
using namespace std;

Tileset* createBoard(int x_size, int y_size) //Creates a board of size x_size*y_size
{
	Tileset* toReturn = new Tileset;
	for (int y = 0; y < y_size; y++)
	{
		for (int x = 0; x < x_size; x++)
		{
			Tile* newTile = new Tile(x,y);
			toReturn->add(newTile);
		}
	}
}

Tileset* createBoard(int size) //Creates a board of size size*size
{
	return createBoard(size, size);
}