#include "OverlapTilesException.h"

using namespace std;

OverlapTilesException::OverlapTilesException(const string message)
{
	this->message = message;
}

string OverlapTilesException::getmessage()
{
	return this->message;
}