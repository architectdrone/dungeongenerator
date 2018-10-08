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
				
				if (!((x+1) < toTest->getXSize()))
				{
					continue;
				}
				Tile* myTile = toTest->getAllTiles()->getXY(x + 1, y);
				if (!(myTile->getWall()))
				{
					toReturn.add(*it);
				}
			}
			else
			{
				
				if (!((y+1) < toTest->getYSize()))
				{
					continue;
				}
				Tile* myTile = toTest->getAllTiles()->getXY(x, y + 1);
				if (!(myTile->getWall()))
				{
					toReturn.add(*it);
				}
			}
		}
		
	}
	return toReturn;
}

Tileset straightGenerator(Board* theBoard, Tile* startTile, bool goingRight)
{
	/**
	* @param startTile: The tile that we are starting at.
	* @param goingRight: Whether the straight will be going rightwards or downwards.
	* @param theBoard: The board containing all of the tiles.
	* @return A tileset containing a new straight
	**/
	int x = startTile->getX();
	int y = startTile->getY();
	Tileset toReturn;

	while (true)
	{
		if ((x >= theBoard->getXSize()) || (y >= theBoard->getYSize()))
		{
			break;
		}

		Tile* myTile;
		if (goingRight)
		{
			myTile = theBoard->getAllTiles()->getXY(x + 1, y);
			x++;
		}
		else
		{
			myTile = theBoard->getAllTiles()->getXY(x, y + 1);
			y++;
		}

		if (!(myTile->getWall()))
		{
			toReturn.add(myTile);
		}
		else
		{
			break;
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
