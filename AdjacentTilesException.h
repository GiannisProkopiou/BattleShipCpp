#include <string>
#include <stdexcept>
#include <exception>

using namespace std;

class AdjacentTilesException : public exception
{
public:
	string message;
	AdjacentTilesException(const string message);
	string getmessage();
};
