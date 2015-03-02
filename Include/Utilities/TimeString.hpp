// ATTENTION: NOT THE ORIGINAL USED IN THE WymonOrion PROJECT!!

#ifndef SYSTEM_TIMESTRING
#define SYSTEM_TIMESTRING

#include <ctime>
#include <chrono>
#include <string>
#include <cstdlib>
#include "Namespace.hpp"

OPEN_WO_SYS

//! Maximum size of a string buffer.
/*!
* This constant is used as a maximum value for string
* buffers. If this value is exceeded, normally the
* executing function will throw an error.
*/
const std::size_t MAXIMUM_STRING_BUFFER = 64;

//! Time string handling class
/*!
* This class provides static member functions to get time
* strings from any kind of time-related type (in the STL). It is furthermore
* possible to get them in a special format.
*/
class TimeString {

private :

	/*time_t mRawTime; // Raw time in seconds since 00:00 1.1.1970*/

	static std::tm* mTimeInfo;

	static std::string mStringBuffer;

	static void update(std::chrono::time_point<std::chrono::system_clock> timePoint);

public :

	// Member variables
	
	static const std::string TIME;

	// Time related

	static const std::string SECONDS;
	static const std::string MINUTES;
	static const std::string HOURS;

	// Date related

	static const std::string NEW_DATE;
	static const std::string DATE;

	// Member functions

	//! Default constructor
	TimeString() {

		/*update (); // Get first values

		mStringBuffer = ""; // Initialize string buffer*/
	
	}

	//! Default Destructor
	~TimeString() {
	}

	static std::string getTimeString(const std::string& format, 
							    std::chrono::time_point<std::chrono::system_clock> timePoint =
								std::chrono::system_clock::now());

	static std::string getRawTime(std::chrono::time_point<std::chrono::system_clock> timePoint =
							    std::chrono::system_clock::now());

	static std::string getSeconds(std::chrono::time_point<std::chrono::system_clock> timePoint =
							   std::chrono::system_clock::now());
	static std::string getMinutes(std::chrono::time_point<std::chrono::system_clock> timePoint =
							   std::chrono::system_clock::now());
	static std::string getHours(std::chrono::time_point<std::chrono::system_clock> timePoint =
							 std::chrono::system_clock::now());

	static std::string getAsciiDate(std::chrono::time_point<std::chrono::system_clock> timePoint =
							    std::chrono::system_clock::now());

};

CLOSE_WO_SYS

#endif
