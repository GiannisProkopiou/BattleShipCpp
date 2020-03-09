#include <vector>
#include "Tile.h"

using namespace std;

class RectangularVectors
{
public:
    static vector<vector<Tile*> > ReturnRectangularTileVector(int size1, int size2)
    {
        vector<vector<Tile*> > newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = vector<Tile*>(size2);
        }

        return newVector;
    }
};
