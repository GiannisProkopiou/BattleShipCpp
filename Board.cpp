#include "Board.h"
#include "Tile.h"
#include "TileType.h"
#include "Carrier.h"
#include "dir.h"
#include "Battleship.h"
#include "Cruiser.h"
#include "Submarine.h"
#include "Destroyer.h"
#include "Ship.h"
#include "OversizeException.h"
#include "OverlapTilesException.h"
#include "AdjacentTilesException.h"

using namespace std;

Board::Board(bool hidden)
{
	this->hidden = hidden;
	int row, col;
	for (row = 0; row < 5; row++)
	{
		for (col = 0; col < 5; col++)
		{
			this->board[row][col] = Tile(row, col, TileType::sea);
		}
	}
}

void Board::drawboards(Board *opponentBd)
{
	cout << endl;
	for (int i = 0; i < 45; i++)
	{
		cout << "-";
	}
	cout << endl;
	cout << " - - Y O U - - \t\t - O P P O N E N T -" << endl;
	cout << "  ";
	for (int col = 0; col < 7; col++)
	{
		cout << col << " ";
	}
		cout << " \t   ";
	for (int col = 0; col < 7; col++)
	{
		cout << col << " ";
	}
		cout << endl;
	for (int row = 0; row < 7; row++)
	{
			cout << row << " ";
		for (int col = 0; col < 7; col++)
		{
			if (hidden && board[row][col]->draw() == 's')
			{
				cout << "~ ";
			}
			else
			{
				cout << board[row][col]->draw() << " ";
			}
		}
			cout << " \t ";
			cout << row << " ";
		for (int col = 0; col < 7; col++)
		{
			if (opponentBd->hidden && opponentBd->board[row][col]->draw() == 's')
			{
				cout << "~ ";
			}
			else
			{
				cout << opponentBd->board[row][col]->draw() << " ";
			}
		}
			cout << endl;
	}

	for (int i = 0; i < 45; i++)
	{
		cout << "-";
	}
	cout << endl;
}

void Board::setHidden(bool hidden)
{
	this->hidden = hidden;
}

bool Tile[][5] Board::getBoard()
{
	return board;
}

void Board::setBoard(vector<vector<Tile*>> &nboard)
{
	this->board = nboard;
}

vector<Tile*> Board::getAdjacentTiles(Tile tile)
{
	int myX = tile->X;
	int myY = tile->Y;

	vector<Tile*> adj;

	if (myX == 0 && myY == 0)
	{
		adj.push_back(board[myX][myY + 1]);
		adj.push_back(board[myX + 1][myY]);
	}
	else if (myX == 0 && myY == 6)
	{
		adj.push_back(board[myX][myY - 1]);
		adj.push_back(board[myX + 1][myY]);
	}
	else if (myX == 6 && myY == 0)
	{
		adj.push_back(board[myX][myY + 1]);
		adj.push_back(board[myX - 1][myY]);
	}
	else if (myX == 6 && myY == 6)
	{
		adj.push_back(board[myX][myY - 1]);
		adj.push_back(board[myX - 1][myY]);
	}
	else if (myX == 0)
	{
		adj.push_back(board[myX][myY + 1]);
		adj.push_back(board[myX][myY - 1]);
		adj.push_back(board[myX + 1][myY]);
	}
	else if (myX == 6)
	{
		adj.push_back(board[myX][myY + 1]);
		adj.push_back(board[myX][myY - 1]);
		adj.push_back(board[myX - 1][myY]);
	}
	else if (myY == 0)
	{
		adj.push_back(board[myX][myY + 1]);
		adj.push_back(board[myX + 1][myY]);
		adj.push_back(board[myX - 1][myY]);
	}
	else if (myY == 6)
	{
		adj.push_back(board[myX][myY - 1]);
		adj.push_back(board[myX + 1][myY]);
		adj.push_back(board[myX - 1][myY]);
	}

	else
	{
		adj.push_back(board[myX][myY + 1]);
		adj.push_back(board[myX][myY - 1]);
		adj.push_back(board[myX + 1][myY]);
		adj.push_back(board[myX - 1][myY]);
	}

	return adj;
}

void Board::placeAllShips(Board *bd)
{
	Carrier *carrier = new Carrier(0, 0, dir::horizontal);
	Battleship *battleship = new Battleship(0, 0, dir::horizontal);
	Cruiser *cruiser = new Cruiser(0, 0, dir::horizontal);
	Submarine *submarine = new Submarine(0, 0, dir::horizontal);
	Destroyer *destroyer = new Destroyer(0, 0, dir::horizontal);

	std::vector<Ship*> myships;

	myships.push_back(carrier);
	myships.push_back(battleship);
	myships.push_back(cruiser);
	myships.push_back(submarine);
	myships.push_back(destroyer);

	int randX = 0;
	int randY = 0;
	int randDir = 0;
	bool shipDone;
	int j = 5;
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		shipDone = false;
		while (!shipDone)
		{
			randX = int(rand() % 7);
			myships[i]->setX(randX);
			randY = int(rand() % 7);
			myships[i]->setY(randY);

			randDir = int(rand() % 2);
			if (randDir == 0)
			{
				myships[i]->setDir(dir::horizontal);
			}
			else if (randDir == 1)
			{
				myships[i]->setDir(dir::vertical);
			}

			try {
				shipDone = myships[i]->placeShip(bd, true);
			}
			catch (OversizeException ex1) {}
			catch (OverlapTilesException ex2) {}
			catch (AdjacentTilesException ex3) {}
		}
		j--;
	}
}

bool Board::allShipsSunk()
{
	bool sunk = true;
	for (int row = 0; row < 7; row++)
	{
		for (int col = 0; col < 7; col++)
		{
			if (board[row][col]->type == TileType::ship)
			{
				sunk = false;
				break;
			}
		}
		if (!sunk)
		{
			break;
		}
	}
	return sunk;
}
