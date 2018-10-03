#include "Tile.h"

Tile::Tile(int p_x, int p_y)
{
	x = p_x;
	y = p_y;
	isWall = false;
}

bool Tile::getWall()
{
	return isWall;
}

int Tile::getX()
{
	return x;
}

int Tile::getY()
{
	return y;
}

void Tile::setWall(bool wall)
{
	isWall = wall;
}

void Tile::makeWall()
{
	isWall = true;
}

void Tile::makeNonWall()
{
	isWall = false;
}