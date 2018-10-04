#include "Tileset.h"
#include "Tile.h"
#include "Board.h"
#include <iostream>
using namespace std;

Board::Board(int x, int y) 
{
	outerWalls = new Tileset;
	boardTileset = new Tileset;
	x_size = x;
	y_size = y;
	for (int y = 0; y < y_size; y++)
	{
		for (int x = 0; x < x_size; x++)
		{
			Tile* newTile = new Tile(x, y);
			boardTileset->add(newTile);
		}
	}
}

Board::Board(int size) 
{
	outerWalls = new Tileset;
	boardTileset = new Tileset;
	x_size = size;
	y_size = size;
	for (int y = 0; y < y_size; y++)
	{
		for (int x = 0; x < x_size; x++)
		{
			Tile* newTile = new Tile(x, y);
			boardTileset->add(newTile);
		}
	}
}

Board::~Board()
{
	boardTileset->destroyTiles();
	delete boardTileset;
}

Tileset* Board::getAllTiles()
{
	return boardTileset;
}

int Board::getXSize()
{
	return x_size;
}

int Board::getYSize()
{
	return y_size;
}

Tileset* Board::getOuterWall()
{
	return outerWalls;
}
void Board::addOuterWalls()
{
	outerWalls->add(boardTileset->getAllY(0));
	outerWalls->add(boardTileset->getAllY(y_size-1));
	outerWalls->add(boardTileset->getAllX(0));
	outerWalls->add(boardTileset->getAllX(x_size - 1));
	outerWalls->setAllWall();
}