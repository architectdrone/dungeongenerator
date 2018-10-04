#include "Tileset.h"
#include "Tile.h"
#include <iterator>

using namespace std;

Tileset::Tileset()
{
	allTiles = new list<Tile*>;
}

Tileset::~Tileset()
{
	//We must delete all of the tiles individually, since they are merely pointers.

	//Create iterator
	list<Tile*>::iterator it = allTiles->begin();

	//Do a for loop, stop when the pointer is the last one.
	for (it; it != allTiles->end(); it++)
	{
		delete *it;
	}

	//Then delete the list
	delete allTiles;
}

Tileset* Tileset::getAllWalls()
{
	Tileset* toReturn = new Tileset();

	//Create iterator
	list<Tile*>::iterator it = allTiles->begin();

	//Do a for loop, stop when the pointer is the last one.
	for (it; it != allTiles->end(); it++)
	{

	}
}

void Tileset::add(Tile & newTile)
{
	allTiles -> insert(newTile, 0 );
}