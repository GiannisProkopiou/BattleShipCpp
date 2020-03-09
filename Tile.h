#include "TileType.h"

class Tile
{
private:
	int X = 0, Y = 0;
	TileType type = TileType::sea;

public:
	Tile();

	Tile(int X, int Y, TileType type);

	virtual int getX();

	virtual void setX(int x);

	virtual int getY();

	virtual void setY(int y);

	virtual TileType getType();

	virtual void setType(TileType type);

	virtual char draw();
};
