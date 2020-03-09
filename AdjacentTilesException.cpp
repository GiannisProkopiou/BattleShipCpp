#include "AdjacentTilesException.h"

using namespace std;

AdjacentTilesException::AdjacentTilesException(const string message) 
{ this->message = message; }

string AdjacentTilesException::getmessage()
{ return this->message; }
