#include "Ship.h"
#include "AdjacentTilesException.h"
#include "Board.h"
#include "OverlapTilesException.h"
#include "OversizeException.h"
#include "Tile.h"
#include "TileType.h"

using namespace std;

Ship::Ship(int X, int Y, dir direction, int size)
{
	this->X = X;
	this->Y = Y;
	this->direction = direction;
	this->size = size;
}

void Ship::setX(int X)
{
	this->X = X;
}

void Ship::setY(int Y)
{
	this->Y = Y;
}

void Ship::setDir(dir direction)
{
	this->direction = direction;
}

bool Ship::placeShip(Board *b, bool verbose) throw(OversizeException, OverlapTilesException, AdjacentTilesException)
{
	Tile myboard[][] = b.getBoard();

	bool valid = false;

		if (this->direction == dir::horizontal)
		{
			if ((this->Y + this->size) > 7)
			{
				if (verbose == true)
				{
					throw OversizeException("This ship doesn't fit to the board!");
				}
			}
			else
			{
				valid = true;
			}

			if (valid)
			{
				for (int i = 0; i < this->size; i++)
				{
					if (myboard[this->X][this->Y + i]->type == TileType::ship)
					{
						if (verbose == true)
						{
							throw new OverlapTilesException("There is another ship in this area!");
						}
						valid = false;
						break;
					}
				}

				for (int j = 0; j < this->size; j++)
				{
					vector<Tile*> myadj;
					myadj = b->getAdjacentTiles(myboard[this->X][this->Y + j]);

					for (auto obj : myadj)
					{
						if (obj->type == TileType::ship)
						{
							if (verbose == true)
							{
								throw new AdjacentTilesException("The ship must not adjent to an existing ship!");
							}
							valid = false;
							break;
						}
					}
				}
			}
		}
		else if (this->direction == dir::vertical)
		{
			if ((this->X + this->size) > 7)
			{
				if (verbose == true)
				{
					throw new OversizeException("This ship doesn't fit to the board!");
				}
			}
			else
			{
				valid = true;
			}

			if (valid)
			{
				for (int i = 0; i < this->size; i++)
				{
					if (myboard[this->X + i][this->Y]->type == TileType::ship)
					{
						if (verbose == true)
						{
							throw new OverlapTilesException("There is another ship in this area!");
						}
						valid = false;
						break;
					}
				}

				for (int j = 0; j < this->size; j++)
				{
					vector<Tile*> myadj;
					myadj = b->getAdjacentTiles(myboard[this->X + j][this->Y]);

					for (auto obj : myadj)
					{
						if (obj->type == TileType::ship)
						{
							if (verbose == true)
							{
								throw new AdjacentTilesException("The ship must not adjent to an existing ship!");
							}
							valid = false;
							break;
						}
					}
				}
			}
		}


	if (valid == true)
	{
		if (this->direction == dir::horizontal)
		{
			for (int i = 0; i < this->size; i++)
			{
				myboard[this->X][this->Y + i]->setType(TileType::ship);
			}
		}
		else if (this->direction == dir::vertical)
		{
			for (int i = 0; i < this->size; i++)
			{
				myboard[this->X + i][this->Y]->setType(TileType::ship);
			}
		}
		b->setBoard(myboard);
		return true;
	}
	else
	{
		return false;
	}
}
