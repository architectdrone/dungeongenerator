#include <iostream>
#include "Tile.h"
#include "Tileset.h"
#include "Board.h"
using namespace std;

void printBoard(Board* myBoard)
{
	int x_size = myBoard->getXSize();
	int y_size = myBoard->getYSize();
	Tile* currentTile;
	Tileset* currentTileset = myBoard->getAllTiles();
	string toPrint = "";
	for (int y = 0; y < y_size; y++)
	{
		for (int x = 0; x < x_size; x++)
		{
			currentTile = currentTileset->getXY(x, y);
			if (currentTile->getWall())
			{
				toPrint = toPrint + "#";
			}
			else
			{
				toPrint = toPrint + " ";
			}
		}
		printf("%s\n", toPrint.c_str());
		toPrint = "";
	}
}

Tileset edgeTiles(Board* toTest, bool goingRight)
{
	/**
	* @param toTest: The board where we are looking for edge tiles.
	* @param goingRight: If true, the function will look for non-wall tiles to the right of every given tile. If false, it will look for them on the bottom of every given tile.
	* @return the Tileset containing all wall tiles bordered by a non-wall tile either to thier left or on the bottom, depending upon the value of goingRight
	**/

	//The pointer to the list of tiles being looked at.
	list<Tile*>* myList = ((toTest->getAllTiles())->getTileList()); 

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
				Tile* myTile = toTest->getAllTiles()->getXY(x + 1, y);
				if (!(x < toTest->getXSize()))
				{
					continue;
				}
				if (!(myTile->getWall()))
				{
					toReturn.add(*it);
				}
			}
			else
			{
				Tile* myTile = toTest->getAllTiles()->getXY(x, y - 1);
				if (!(y < toTest->getYSize()))
				{
					continue;
				}
				if (!(myTile->getWall()))
				{
					toReturn.add(*it);
				}
			}
		}
		
	}
	return toReturn;
}

int main()
{

	Board myBoard(30, 10);
	myBoard.addOuterWalls();
	printBoard(&myBoard);

	int stop;
	cin >> stop;
}
