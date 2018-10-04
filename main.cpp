#include <iostream>
#include "Tile.h"
#include "Tileset.h"
#include "Board.h"
#include "generalTools.cpp"
using namespace std;

int main()
{
	Board myBoard(10);
	myBoard.addOuterWalls();
	printBoard(&myBoard);
}
