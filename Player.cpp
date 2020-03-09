#include "Player.h"
#include "Board.h"
#include "AdjacentTilesException.h"
#include "OverlapTilesException.h"
#include "OversizeException.h"
#include "Ship.h"
#include "Tile.h"
#include "TileType.h"

using namespace std;

Player::Player()
{
	Board *playersBoard = new Board(false);
	this->playersBoard = playersBoard;
}

void Player::placeAllShips() throw(OversizeException, OverlapTilesException, AdjacentTilesException)
{ playersBoard->placeAllShips(playersBoard); }

bool Player::placeShip(Ship *myShip, int X, int Y, dir direction) throw(OversizeException, OverlapTilesException, AdjacentTilesException)
{
	myShip->setX(X);
	myShip->setY(Y);
	myShip->setDir(direction);
	return myShip->placeShip(playersBoard, true);
}

void Player::fire(Board *opBoard, std::vector<int> &coord)
{
	vector<vector<Tile*>> gameBoard = opBoard->getBoard();
	TileType shot = gameBoard[coord[0]][coord[1]]->getType();
	shots++;
	if (shot == TileType::ship)
	{
		gameBoard[coord[0]][coord[1]]->setType(TileType::hit);
		cout << "Hit!" << endl;
		hit++;
	}
	else if (shot == TileType::sea)
	{
		gameBoard[coord[0]][coord[1]]->setType(TileType::miss);
		cout << "Miss!" << endl;
		miss++;
	}
	else if (shot == TileType::hit)
	{
		cout << "Already hit!" << endl;
		reps++;
	}
	else if (shot == TileType::miss)
	{
		cout << "Already hit!" << endl;
		reps++;
	}
}

void Player::getStats()
{
	cout << "Shots fired: " << shots << endl;
	cout << "Shots hit: " << hit << endl;
	cout << "Shots missed: " << miss << endl;
	cout << "Repeated shots: " << reps << endl;
}
