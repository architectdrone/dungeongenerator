#include "generalTools.h"
#include <ctime>
using namespace std;

Tileset edgeTiles(Board* toTest, bool goingRight)
{
	/**
	* @param toTest: The board where we are looking for edge tiles.
	* @param goingRight: If true, the function will look for non-wall tiles to the right of every given tile. If false, it will look for them on the bottom of every given tile.
	* @return the Tileset containing all wall tiles bordered by a non-wall tile either to thier left or on the bottom, depending upon the value of goingRight
	**/

	//The pointer to the list of tiles being looked at.
	Tileset* currentTileset = toTest->getAllTiles()->getAllWalls();
	list<Tile*>* myList = currentTileset->getTileList();

	//The tileset to return
	Tileset toReturn;

	//Create iterator
	list<Tile*>::iterator it = myList->begin();

	//Do a for loop, stop when the pointer is the last one.
	for (it; it != myList->end(); it++)
	{
		int x = (*it)->getX();
		int y = (*it)->getY();
		if ((*it)->getWall())
		{
			if (goingRight)
			{

				if (!((x + 1) < toTest->getXSize()))
				{
					continue;
				}

				if (!(currentTileset->isInTileset(x + 1, y)))
				{
					toReturn.addNoCheck(*it);
				}
			}
			else
			{

				if (!((y + 1) < toTest->getYSize()))
				{
					continue;
				}
				if (!(currentTileset->isInTileset(x, y + 1)))
				{
					toReturn.addNoCheck(*it);
				}
			}
		}

	}
	delete currentTileset;
	return toReturn;
}
int getRandomNumber(int low, int high)
{
	/**
	* @pre high > low
	* @throw an error if high < low
	* @param low: The lowest number that can be generated.
	* @param high: The highest number that can be generated.
	* @return a random number in the range [low, high]
	**/

	if (high < low)
	{
		throw(std::out_of_range("High must be greater than low."));
	}
	srand((unsigned)time(0));
	return low + rand() % (high - low + 1);
}

Tile* getRandomTile(Tileset* myTileset)
{
	/**
	* @param myTileset: The tileset to get a random tile from.
	* @return A random tile from the tileset.
	**/
	return (myTileset->getTile(getRandomNumber(0, (myTileset->getLength()) - 1)));
}
