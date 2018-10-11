#include <iostream>
#include "Tile.h"
#include "Tileset.h"
#include "Board.h"
#include <ctime>
using namespace std;

void printBoard(Board* myBoard)
{
	int x_size = myBoard->getXSize();
	int y_size = myBoard->getYSize();
	Tile* currentTile;
	Tileset* currentTileset = myBoard->getAllTiles();
	list<Tile*>::iterator it = currentTileset->getTileList()->begin();
	string toPrint = "";
	for (int y = 0; y < y_size; y++)
	{
		for (int x = 0; x < x_size; x++)
		{
			currentTile = *it;
			if (currentTile->getWall())
			{
				toPrint = toPrint + "#";
			}
			else
			{
				toPrint = toPrint + " ";
			}
			it++;
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
	Tileset* currentTileset = toTest->getAllTiles()->getAllWalls();
	list<Tile*>* myList = currentTileset -> getTileList(); 

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
				
				if (!(currentTileset->isInTileset(x+1,y)))
				{
					toReturn.addNoCheck(*it);
				}
			}
			else
			{
				
				if (!((y+1) < toTest->getYSize()))
				{
					continue;
				}
				if (!(currentTileset->isInTileset(x, y+1)))
				{
					toReturn.addNoCheck(*it);
				}
			}
		}
		
	}
	return toReturn;
}

Tileset* straightGenerator(Board* theBoard, Tile* startTile, bool goingRight)
{
	/**
	* @param startTile: The tile that we are starting at.
	* @param goingRight: Whether the straight will be going rightwards or downwards.
	* @param theBoard: The board containing all of the tiles.
	* @return A tileset containing a new straight
	**/
	int x = startTile->getX();
	int y = startTile->getY();
	Tileset* toReturn = new Tileset;

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
			toReturn->add(myTile);
			
		}
		else
		{
			break;
		}
	}	return toReturn;
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
	return low+rand()%(high-low+1);
}

Tile* getRandomTile(Tileset* myTileset)
{
	/**
	* @param myTileset: The tileset to get a random tile from.
	* @return A random tile from the tileset.
	**/
	return (myTileset->getTile(getRandomNumber(0, (myTileset->getLength()) - 1)));
}

void addStraights(Board* theBoard, int number)
{
	/**
	* @pre Board has outer walls.
	* @pre Board is empty except for outer walls.
	* @param theBoard: The board to add straights to.
	* @param number: The upper limit of straights to add.
	* @post A number of straights (0 < #newStraights <= number) has been added to the board. The reason it isn't equal is because of an algorithim bug.
	**/

	/*
	How it works:
	First, consider the previous solution. Before implementing this version, the previous straight placer would check every wall tile to see if it was a suitable edge.
	By "suitable edge", I mean that if we were looking to place a horizontal straight, we would check every wall to see if the tile to it's left was a non-wall. The same goes for vertical (it would check the bottom of each wall).
	Then, from the set of suitable edges, we select one at random, and build a straight off of it, and go back to the beginning until we are done.

	While this gets the job done, it is very slow. Even after very cleverly tuning the edgeTiles function, it still took around a minute to generate straights on a 100x100 board (like I was using).
	This certainly isn't bad (previously it took upwards of eight minutes!), but isn't great either.

	So I made this (quite clever, in my humble opinion) adjustment to the algorithim. Instead of generating a new Tileset of edges each time we needed one, I kept two tilesets - one for vertical, one for horizontal - and continually added to them.
	How did I know what to add? Well, since every wall on the board was either placed by the straight-placer itself, or the outside walls, I reasoned that each time I created a straight, I also created an edge.
	Now, for example, consider the rightward-facing case. If I place a straight in the rightward direction, each wall will have a wall to it's left and to it's right. (except for the endpoints) Thus, we know it doesn't generate any edges in the rightward direction. However, the bottom of each tile is unaccounted for.
	Thus, I would add each newly placed wall to the edges that were valid in the vertical direction.

	Sidebar - Removing the capability for neighboring straights:
	There was an algorithim error that involved the problem of neighboring straights. Essentially, two straights, when placed next to each other, caused some problems.
	Fixing this, I determined, without changing the way the algorithim looks, would not only be a pain in the butt, but also put a tax on resource usage. Additionally, I didn't really like neighboring straights. See "optimized dungeon" in the readme.
	So, I made a change to the output of the straights. Now, none of them will border. To do this, I removed from the edge-trackers any tile that would start a straight next to the current one.

	Critical Assumptions, Limitations, and Algorithim Errors:
	+ A very important assumption that limits the functionality of this algorithim is that the board must be assumed to only have outer-walls. Otherwise, we can't accept that every wall is an outerwall at the start
		+ Easily fix this by using edgeTiles, but introduces some lag.
	+ There is the problem of assuming that there isn't going to be any tiles below the ones placed (in the horizontal case)

	TODO:
	+ Fix memory leaks.
	*/

	bool horizontal = true;
	Tileset horizontalEdges = edgeTiles(theBoard, true);
	Tileset verticalEdges = edgeTiles(theBoard, false);
	Tileset* currentEdges = nullptr;
	Tileset* nonCurrentEdges = nullptr;
	Tileset* newStraight;
	Tileset* toRemoveFromCurrentEdges = nullptr;;
	Tileset* toRemoveFromNonCurrentEdges = nullptr;;
	//X and Y position of starting tile
	int x;
	int y;
	for (int i = 0; i < number; i++)
	{
		//Toggle horizontal and vertical
		if (horizontal)
		{
			horizontal = false; 
			currentEdges = &verticalEdges;
			nonCurrentEdges = &horizontalEdges;
		}
		else
		{
			horizontal = true;
			currentEdges = &horizontalEdges;
			nonCurrentEdges = &verticalEdges;
		}
		//Get a random tile from the Tileset.
		Tile* myTile = getRandomTile(currentEdges);
		//Create a new straight starting from the tile that we chose.
		newStraight = straightGenerator(theBoard, myTile, horizontal);
		//Make them all walls.
		newStraight->setAllWall();
		//See algorithim notes. 
		nonCurrentEdges->add(newStraight);

		//Remove the capability to have straights next to each other (in theory)
		x = myTile->getX();
		y = myTile->getY();
		toRemoveFromCurrentEdges = new Tileset;
		toRemoveFromNonCurrentEdges = new Tileset;
		if (horizontal)
		{
			
			/*
			#     #
			C     #
			CN###N#
			C     #
			#     #

			C represents those things to be removed from the currentEdge
			N represents those things to be removed from the nonCurrentEdge

			C:
			(x, y)
			(x, y+1)
			(x, y-1)
			N:
			(x+1, y)
			({Largest X in straight tileset}, y)

			Everything is wrapped in a try/catch block so that if it is out of range, nothing will happen.
			*/
			toRemoveFromCurrentEdges->add((theBoard->getAllTiles()->getXY(x, y)));
			
			if (theBoard->getAllTiles()->getMaxY() > y + 1)
			{
				toRemoveFromCurrentEdges->add((theBoard->getAllTiles()->getXY(x, y+1)));
			}
			if (theBoard->getAllTiles()->getMinY() < y - 1)
			{
				toRemoveFromCurrentEdges->add((theBoard->getAllTiles()->getXY(x, y - 1)));
			}
			if (theBoard->getAllTiles()->getMaxX() > x + 1)
			{
				toRemoveFromNonCurrentEdges->add((theBoard->getAllTiles()->getXY(x+1, y )));
			}
			toRemoveFromNonCurrentEdges->add(newStraight->getXY(newStraight->getMaxX(), y));
		}
		else
		{
			/*
			#CCC#
			  N  
			  #
			  N
			#####
			
			C represents those things to be removed from the currentEdge
			N represents those things to be removed from the nonCurrentEdge

			C:
			(x-1, y)
			(x, y)
			(x+1, y)
			N:
			(x, y+1)
			(x, {Largest Y in Straight})
			*/

			toRemoveFromCurrentEdges->add((theBoard->getAllTiles()->getXY(x, y)));
			if (theBoard->getAllTiles()->getMinX() < x-1)
			{
				toRemoveFromCurrentEdges->add((theBoard->getAllTiles()->getXY(x-1, y)));
			}
			if (theBoard->getAllTiles()->getMaxX() > x + 1)
			{
				toRemoveFromCurrentEdges->add((theBoard->getAllTiles()->getXY(x + 1, y)));
			}
			if (theBoard->getAllTiles()->getMaxY() > y+1)
			{
				toRemoveFromNonCurrentEdges->add((theBoard->getAllTiles()->getXY(x, y+1)));
			}
			toRemoveFromNonCurrentEdges->add(newStraight->getXY(x, newStraight->getMaxY()));
		}
		currentEdges->remove(toRemoveFromCurrentEdges);
		nonCurrentEdges->remove(toRemoveFromNonCurrentEdges);
	}

	
}

int main()
{

	Board myBoard(100, 100);
	myBoard.addOuterWalls();
	//printBoard(&myBoard);

	addStraights(&myBoard, 50);
	printBoard(&myBoard);

	int stop;
	cin >> stop;
}
