#include "Tile.h"

Tile::Tile(){}

Tile::Tile(int X, int Y, TileType type)
{
	this->X = X;
	this->Y = Y;
	this->type = type;
}

int Tile::getX()
{
	return this->X;
}

void Tile::setX(int x)
{
	this->X = x;
}

int Tile::getY()
{
	return this->Y;
}

void Tile::setY(int y)
{
	this->Y = y;
}

TileType Tile::getType()
{
	return this->type;
}

void Tile::setType(TileType type)
{
	this->type = type;
}

char Tile::draw()
{
	char ty = 'N';
	switch (this->type)
	{
		case TileType::sea:
			ty = '~';
			break;
		case TileType::ship:
			ty = 's';
			break;
		case TileType::hit:
			ty = 'X';
			break;
		case TileType::miss:
			ty = 'o';
			break;
	}
	return ty;
}
