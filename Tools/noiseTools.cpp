#include "noiseTools.h"
#include "generalTools.h"
using namespace std;

Tileset* straightGenerator(Board* theBoard, Tile* startTile, bool goingRight)
{
	/**
	* @param startTile: The tile that we are starting at.
	* @param goingRight: Whether the straight will be going rightwards or downwards.
	* @param theBoard: The board containing all of the tiles.
	* @return A tileset containing a new straight
	**/


	int x = 0;
	int y = 0;
	bool started = false;
	Tileset* axis = nullptr;
	Tileset* toReturn = new Tileset;

	if (goingRight)
	{
		x = 0;
		y = startTile->getY();
		axis = theBoard->getAllTiles()->getAllY(y);
		
	}
	else
	{
		x = startTile->getX();
		y = 0;
		axis = theBoard->getAllTiles()->getAllX(x);
	}

	if ((x == startTile->getX()) && (y == startTile->getY()))
	{
		started = true;
	}

	list<Tile*>::iterator it = axis->getTileList()->begin();
	it++;

	while (true)
	{

		if (goingRight)
		{
			x++;
		}
		else
		{
			y++;
		}

		if ((x >= theBoard->getXSize()) || (y >= theBoard->getYSize()))
		{
			break;
		}

		//Start
		if ((x == startTile->getX()) && (y == startTile->getY()))
		{
			started = true;
		}

		if (!started)
		{
			it++;
			continue;
		}
		
		Tile* myTile = *it;


		//Stop
		if ((myTile->getWall()))
		{
			if  (!((x == startTile->getX()) && (y == startTile->getY())))
			{
				break;
			}
		}
			

		toReturn->add(myTile);
		it++;
	}
	delete axis;
	return toReturn;
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

	*/

	bool horizontal = true;
	Tileset horizontalEdges = edgeTiles(theBoard, true);
	Tileset verticalEdges = edgeTiles(theBoard, false);
	Tileset* currentEdges = nullptr;
	Tileset* nonCurrentEdges = nullptr;
	Tileset* newStraight;
	Tileset* toRemoveFromCurrentEdges = nullptr;
	Tileset* toRemoveFromNonCurrentEdges = nullptr;
	//X and Y position of starting tile
	int x;
	int y;

	//This is to alleviate algorithim error regarding walls right next to each other. Long story short, the straight placer thinks that it can place walls in corners unless I do this. (For various reasons)
	horizontalEdges.remove(horizontalEdges.getXY(0, 1)); //Rightward, upper left corner
	horizontalEdges.remove(horizontalEdges.getXY(0, theBoard->getYSize() - 2)); //Rightward, bottom left corner
	verticalEdges.remove(verticalEdges.getXY(1, 0)); //Downward, upper left corner
	verticalEdges.remove(verticalEdges.getXY(theBoard->getYSize() - 2, 0)); //Downward, upper right corner

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

		//Are we done yet?
		if (((currentEdges->getLength() == 0)) && ((nonCurrentEdges->getLength() == 0)))
		{
			break;
		}
		else if (currentEdges->getLength() == 0)
		{
			continue;
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
				toRemoveFromCurrentEdges->add((theBoard->getAllTiles()->getXY(x, y + 1)));
			}
			if (theBoard->getAllTiles()->getMinY() < y - 1)
			{
				toRemoveFromCurrentEdges->add((theBoard->getAllTiles()->getXY(x, y - 1)));
			}
			if (theBoard->getAllTiles()->getMaxX() > x + 1)
			{
				toRemoveFromNonCurrentEdges->add((theBoard->getAllTiles()->getXY(x + 1, y)));
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
			if (theBoard->getAllTiles()->getMinX() < x - 1)
			{
				toRemoveFromCurrentEdges->add((theBoard->getAllTiles()->getXY(x - 1, y)));
			}
			if (theBoard->getAllTiles()->getMaxX() > x + 1)
			{
				toRemoveFromCurrentEdges->add((theBoard->getAllTiles()->getXY(x + 1, y)));
			}
			if (theBoard->getAllTiles()->getMaxY() > y + 1)
			{
				toRemoveFromNonCurrentEdges->add((theBoard->getAllTiles()->getXY(x, y + 1)));
			}
			toRemoveFromNonCurrentEdges->add(newStraight->getXY(x, newStraight->getMaxY()));
		}
		currentEdges->remove(toRemoveFromCurrentEdges);
		nonCurrentEdges->remove(toRemoveFromNonCurrentEdges);

		delete toRemoveFromCurrentEdges;
		delete toRemoveFromNonCurrentEdges;
		delete newStraight;

	}


}