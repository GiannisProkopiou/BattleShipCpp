#include "dir.h"
#include <vector>

using namespace std;

class AdjacentTilesException;
class Board;
class OverlapTilesException;
class OversizeException;

class Ship
{
private:
	int X = 0, Y = 0;
	int size = 0;

	dir direction = static_cast<dir>(0);

public:
	Ship(int X, int Y, dir direction, int size);

	virtual void setX(int X);

	virtual void setY(int Y);

	virtual void setDir(dir direction);

	virtual bool placeShip(Board *b, bool verbose) throw(OversizeException, OverlapTilesException, AdjacentTilesException);
};
