#include <iostream>
#include "Tile.h"
#include "Tileset.h"
#include "Board.h"
#include "generalTools.cpp"
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
	}
}

int main()
{
	Board myBoard(10);
	myBoard.addOuterWalls();
	printBoard(&myBoard);
}
