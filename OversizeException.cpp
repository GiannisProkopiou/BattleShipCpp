#include "OversizeException.h"

using namespace std;

OversizeException::OversizeException(const string message)
{
	this->message = message;
}

string OversizeException::getmessage()
{
	return this->message;
}