#include <string>
#include <stdexcept>
#include <exception>

using namespace std;

class OverlapTilesException : public exception
{
public:
	string message;
	OverlapTilesException(const string message);
	string getmessage();
};

