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
		if ((*it) -> getWall())
		{
			toReturn->add(*it);
		}
	}
	return toReturn;
}

Tileset* Tileset::getAllNonWalls()
{
	Tileset* toReturn = new Tileset();

	//Create iterator
	list<Tile*>::iterator it = allTiles->begin();

	//Do a for loop, stop when the pointer is the last one.
	for (it; it != allTiles->end(); it++)
	{
		if (!((*it)->getWall()))
		{
			toReturn->add(*it);
		}
	}
	return toReturn;
}

Tileset* Tileset::getAllX(int x)
{
	Tileset* toReturn = new Tileset();

	//Create iterator
	list<Tile*>::iterator it = allTiles->begin();

	//Do a for loop, stop when the pointer is the last one.
	for (it; it != allTiles->end(); it++)
	{
		if (((*it)->getX()) == x)
		{
			toReturn->add(*it);
		}
	}
	return toReturn;
}

Tileset* Tileset::getAllY(int y)
{
	Tileset* toReturn = new Tileset();

	//Create iterator
	list<Tile*>::iterator it = allTiles->begin();

	//Do a for loop, stop when the pointer is the last one.
	for (it; it != allTiles->end(); it++)
	{
		if (((*it)->getY()) == y)
		{
			toReturn->add(*it);
		}
	}
	return toReturn;
}


void Tileset::add(Tile * newTile )
{
	if (!isInTileset(newTile))
	{
		allTiles->push_back(newTile);
	}
	
}

bool Tileset::isInTileset(Tile *myTile)
{
	//Create iterator
	list<Tile*>::iterator it = allTiles->begin();

	//Do a for loop, stop when the pointer is the last one.
	for (it; it != allTiles->end(); it++)
	{
		if (myTile == *it)
		{
			return true;
		}
	}
	return false;
}
