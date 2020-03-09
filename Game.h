#include "dir.h"
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

class AdjacentTilesException;
class OverlapTilesException;
class OversizeException;
class Player;

class Game
{
	static void main(vector<string> &args) throw(OversizeException, OverlapTilesException, AdjacentTilesException);

public:
	static vector<int> getInput();

	static vector<int> getRandInput();

	static dir getOrientation();

	static bool randomPlace();

	static void manualPlace(Player *p1, Player *p2);

};
