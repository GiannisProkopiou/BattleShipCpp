#include <string>
#include <stdexcept>
#include <exception>

using namespace std;

class OversizeException : public exception
{
public:
	string message;
	OversizeException(const string message);
	string getmessage();
};


