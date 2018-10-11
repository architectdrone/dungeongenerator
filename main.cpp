#include <iostream>
#include "Tile.h"
#include "Tileset.h"
#include "Board.h"
#include "generalTools.h"
#include "noiseTools.h"
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

int main()
{

	Board myBoard(10, 10);
	myBoard.addOuterWalls();
	//printBoard(&myBoard);
	
	
	addStraights(&myBoard, 10);
	printBoard(&myBoard);

	int stop;
	cin >> stop;

}
