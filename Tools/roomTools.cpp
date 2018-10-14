#include <iostream>
#include "../Classes/Tileset.h"
#include "../Classes/Tile.h"
#include "../Classes/Board.h"
#include "roomTools.h"
#include <list>
using namespace std;

struct tileInfo
{
	int x;
	int y;
	Tile* theTile;
	Tileset* theRoom;
};



tileInfo* doOneSweep(Board* theBoard, tileInfo* previous, int current_x)
{
	/**
	* @pre if current_x !=, previous must point to an array of length y_size.
	* @param theBoard The board that we are sweeping on.
	* @param previous The array of tileInfos that hold all information about the tiles to the left.
	* @param current_x The current x range we are testing on.
	* @return a list of all of the x's in the range, with rooms assigned to them.
	**/
	tileInfo* toReturn = new tileInfo[theBoard->getYSize()];

	Tileset* allX = theBoard->getAllTiles()->getAllX(current_x);
	list<Tile*>::iterator it = allX->getTileList()->begin();

	Tileset* currentRoom = nullptr;

	int y = -1;
	bool prevWasWall = false;

	for (it; it != allX->getTileList()->end(); it++)
	{
		y++;


		tileInfo newTI;
		newTI.x = current_x;
		newTI.y = y;
		newTI.theTile = *it;


		//If thi is a wall, do nothing.
		if ((*it)->getWall())
		{
			newTI.theRoom = nullptr;
			toReturn[y] = newTI;
			prevWasWall = true;
			continue;
		}

		//Creation of new rooms.
		if (prevWasWall)
		{
			currentRoom = new Tileset;
		}

		//If we are attached to another room, we find out.
		if (current_x != 0)
		{
			if (!(previous[y].theTile->getWall()))
			{
				if (previous[y].theRoom != currentRoom)
				{
					Tileset* interim;
					interim = currentRoom;
					currentRoom = previous[y].theRoom;
					currentRoom->add(interim);
					delete interim;
				}
			}
		}

		prevWasWall = false;
		currentRoom->add(*it);
		newTI.theRoom = currentRoom;
		toReturn[y] = newTI;
	}

	delete allX;
	return toReturn;
}

list<Tileset*> getEnclosed(tileInfo* previous, tileInfo* current, int y_size)
{
	/**
	* @pre previous and current both point to an array of length y_size.
	* @param previous A list of all X's to the left.
	* @param current A list of all X's that we are currently looking at.
	* @param y_size Size of the y diection.
	* @return a list of all rooms from previous that do not appear in current, and thus are completely done.
	**/
	list<Tileset*> allInPrevious;
	Tileset* last = nullptr;

	for (int y = 0; y < y_size; y++)
	{
		if (previous[y].theRoom != last)
		{
			if (previous[y].theRoom != nullptr)
			{
				allInPrevious.push_back(previous[y].theRoom);
				last = previous[y].theRoom;
			}
		}
	}

	list<Tileset*> allInCurrent;
	last = nullptr;

	for (int y = 0; y < y_size; y++)
	{
		if (current[y].theRoom != last)
		{
			if (current[y].theRoom != nullptr)
			{
				allInCurrent.push_back(current[y].theRoom);
				last = current[y].theRoom;
			}
		}
	}

	list<Tileset*>::iterator p_it = allInPrevious.begin();
	list<Tileset*>::iterator c_it = allInCurrent.begin();
	list<Tileset*> toReturn;
	bool isIn;
	for (p_it; p_it != allInPrevious.end(); p_it++)
	{
		isIn = false;
		for (c_it; c_it != allInCurrent.end(); c_it++)
		{
			if (*p_it == *c_it)
			{
				isIn = true;
				break;
			}
		}

		if ((!isIn))
		{
			toReturn.push_back(*p_it);
		}
		isIn = false;
	}
	return toReturn;
}

list<Tileset*> roomSweep(Board *theBoard)
{
	/**
	* @return A list of contiguous areas (aka rooms) within the given board.
	* @param theBoard The Board we are looking at.
	**/
	/*
	What it does:
	Room sweep is an algorithim that divides the rooms into connected regions - ie, rooms.

	How it works:
	A the name implies, it sweeps across the board, from left to right, top to bottom. If the tile we are looking at has a wall above it, but it is, itself, not a wall, we create a new room.
	Every tile also checks the one it is bordering to its left. If a non-wall is bordering a non-wall to its left, all tiles in the current room are added to the room that the non-wall on it's left are included in.
	*/
	list<Tileset*> toReturn;

	tileInfo* current = new tileInfo[theBoard->getYSize()];
	tileInfo* previous = new tileInfo[theBoard->getYSize()];

	for (int cur_x = 0; cur_x < theBoard->getXSize(); cur_x++)
	{
		current = doOneSweep(theBoard, previous, cur_x);

		if (cur_x != 0)
		{
			list<Tileset*> allEnclosed = getEnclosed(previous, current, theBoard->getYSize());
			list<Tileset*>::iterator it = allEnclosed.begin();
			for (it; it != allEnclosed.end(); it++)
			{
				toReturn.push_front(*it);
			}
		}
		

		delete [] previous;
		previous = current;
	}

	cout << toReturn.size() << endl;
	return toReturn;
}
