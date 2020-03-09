#include "dir.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Board;
class AdjacentTilesException;
class OverlapTilesException;
class OversizeException;
class Ship;

class Player
{
private:
	string name;
	int hit = 0, miss = 0, shots = 0, reps = 0;
public:
	Board *playersBoard;

	Player();

	virtual void placeAllShips() throw(OversizeException, OverlapTilesException, AdjacentTilesException);

	virtual bool placeShip(Ship *myShip, int X, int Y, dir direction) throw(OversizeException, OverlapTilesException, AdjacentTilesException);

	virtual void fire(Board *opBoard, vector<int> &coord);

	virtual void getStats();
};
