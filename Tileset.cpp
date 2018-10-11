#include "Tileset.h"
#include "Tile.h"
#include <iterator>

using namespace std;

Tileset::Tileset()
{
	max_x = 0;
	max_y = 0;
	min_x = 32767;
	min_y = 32767;
	allTiles = new list<Tile*>;
}

Tileset::Tileset(const Tileset &oldTileset)
{
	allTiles = new list<Tile*>;

	//Create iterator
	list<Tile*>::iterator it = (oldTileset.getTileList())->begin();

	//Do a for loop, stop when the pointer is the last one.
	for (it; it != (oldTileset.getTileList())->end(); it++)
	{
		add(*it);
	}
}

Tileset::~Tileset()
{
	delete allTiles;
}

void Tileset::destroyTiles()
{
	//Create iterator
	list<Tile*>::iterator it = allTiles->begin();

	//Do a for loop, stop when the pointer is the last one.
	for (it; it != allTiles->end(); it++)
	{
		delete *it;
	}
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

Tile* Tileset::getXY(int x, int y) throw (std::out_of_range)
{
	
	//Create iterator
	list<Tile*>::iterator it = allTiles->begin();

	//Do a for loop, stop when the pointer is the last one.
	for (it; it != allTiles->end(); it++)
	{
		if ((((*it)->getX()) == x) && (((*it)->getY()) == y))
		{
			return *it;
		}
	}
	throw(std::out_of_range("X, Y coordinates not found in tileset."));
}

Tile* Tileset::getTile(int i) throw(std::out_of_range)
{
	int curPos = 0;

	//Create iterator
	list<Tile*>::iterator it = allTiles->begin();

	//Do a for loop, stop when the pointer is the last one.
	for (it; it != allTiles->end(); it++)
	{
		if (curPos == i)
		{
			return *it;
		}
		curPos++;
	}

	throw(std::out_of_range("Out of bounds."));
}

int Tileset::getLength()
{
	return allTiles->size();
}

int Tileset::getMinX()
{
	return min_x;
}

int Tileset::getMinY()
{
	return min_y;
}

int Tileset::getMaxX()
{
	return max_x;
}

int Tileset::getMaxY()
{
	return max_y;
}
list<Tile*>* Tileset::getTileList() const
{
	return allTiles;
}

void Tileset::setAllWall()
{
	//Create iterator
	list<Tile*>::iterator it = allTiles->begin();

	//Do a for loop, stop when the pointer is the last one.
	for (it; it != allTiles->end(); it++)
	{
		(*it)->makeWall();
	}
}

void Tileset::setAllNonWall()
{
	//Create iterator
	list<Tile*>::iterator it = allTiles->begin();

	//Do a for loop, stop when the pointer is the last one.
	for (it; it != allTiles->end(); it++)
	{
		(*it)->makeNonWall();
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

bool Tileset::isInTileset(int x, int y)
{

	//Create iterator
	list<Tile*>::iterator it = allTiles->begin();

	//Do a for loop, stop when the pointer is the last one.
	for (it; it != allTiles->end(); it++)
	{
		if ((((*it)->getX()) == x) && (((*it)->getY()) == y))
		{
			return true;
		}
	}
	return false;
}

void Tileset::add(Tile * newTile )
{
	if (newTile->getX() > max_x)
	{
		max_x = newTile->getX();
	}
	if (newTile->getY() > max_y)
	{
		max_y = newTile->getY();
	}
	if (newTile->getX() < min_x)
	{
		min_x = newTile->getX();
	}
	if (newTile->getY() < min_y)
	{
		min_y = newTile->getY();
	}
	if (!isInTileset(newTile))
	{
		allTiles->push_back(newTile);
	}	
}

void Tileset::addNoCheck(Tile* newTile)
{
	if (newTile->getX() > max_x)
	{
		max_x = newTile->getX();
	}
	if (newTile->getY() > max_y)
	{
		max_y = newTile->getY();
	}
	if (newTile->getX() < min_x)
	{
		min_x = newTile->getX();
	}
	if (newTile->getY() < min_y)
	{
		min_y = newTile->getY();
	}
	allTiles->push_back(newTile);
}

void Tileset::add(Tileset* newTileset)
{
	//Create iterator
	list<Tile*>::iterator it = (newTileset->getTileList())->begin();

	//Do a for loop, stop when the pointer is the last one.
	for (it; it != (newTileset->getTileList())->end(); it++)
	{
		add(*it);
	}
}

void Tileset::remove(Tile* toRemove)
{
	//Create iterator
	list<Tile*>::iterator it = allTiles->begin();

	//Do a for loop, stop when the pointer is the last one.
	for (it; it != allTiles->end(); it++)
	{
		if (*it == toRemove)
		{
			allTiles->erase(it);
			return;

		}
	}
}

void Tileset::remove(Tileset* toRemove)
{
	//Create iterator
	list<Tile*>::iterator it = allTiles->begin();

	//Do a for loop, stop when the pointer is the last one.
	for (it; it != allTiles->end();)
	{

		if (toRemove->isInTileset(*it))
		{
			it = allTiles->erase(it);
		}
		else
		{
			it++;
		}
	}
}
