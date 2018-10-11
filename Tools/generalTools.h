#ifndef GENERALTOOLS_H
#define GENERALTOOLS_H
#include "../Classes/Board.h"
#include "../Classes/Tileset.h"
#include "../Classes/Board.h"

Tileset edgeTiles(Board* toTest, bool goingRight);
int getRandomNumber(int low, int high);
Tile* getRandomTile(Tileset* myTileset);

#endif