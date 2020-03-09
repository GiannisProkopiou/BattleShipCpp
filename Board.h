#include <vector>
#include <iostream>
#include "Tile.h"
#include "TileType.h"


using namespace std;

class Tile;

class Board
{
private:
	 Tile board[5][5];
	//board = new Tile*[7];
	bool hidden = false;

public:

	//vector<vector<Tile*> > board = RectangularVectors::ReturnRectangularTileVector(7, 7);

	Board(bool hidden);

	virtual void drawboards(Board *opponentBd);

	virtual void setHidden(bool hidden);

	virtual Tile[][5] getBoard();

	virtual void setBoard(Tile* **nboard);

	virtual vector<Tile*> getAdjacentTiles(Tile tile);

	virtual void placeAllShips(Board *bd);

	virtual bool allShipsSunk();
};
