#include <iostream>
#include "Classes/Tile.h"
#include "Classes/Tileset.h"
#include "Classes/Board.h"
#include "Tools/generalTools.h"
#include "Tools/noiseTools.h"
#include "Tools/roomTools.h"
#include <ctime>
#include <string>
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

void printBoardWithRooms(Board* myBoard, list<Tileset*> rooms)
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
				int index = -1;
				list<Tileset*>::iterator room = rooms.begin();
				for (room; room != rooms.end(); room++)
				{
					index++;
					if ((*room)->isInTileset(x, y))
					{
						break;
					}
				}
				if (index != -1)
				{
					toPrint = toPrint + to_string(index % 10);
				}
				else
				{
					toPrint = toPrint + "?";
				}
				
			}
			it++;
		}

		printf("%s\n", toPrint.c_str());
		toPrint = "";
	}
}

int main()
{

	Board myBoard(50, 50);
	myBoard.addOuterWalls();
	//printBoard(&myBoard);
	
	addStraights(&myBoard, 1000);
	printBoard(&myBoard);

	list<Tileset*> allRooms = roomSweep(&myBoard);
	printBoardWithRooms(&myBoard, allRooms);

	int stop;
	cin >> stop;

}
