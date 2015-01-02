// ATTENTION: NOT THE ORIGINAL USED IN THE WymonOrion PROJECT!!


#ifndef _TIME_STRING_
#define _TIME_STRING_

#ifndef _CTIME_
	#include <ctime>
#endif
#ifndef _CHRONO_
	#include <chrono>
#endif
#ifndef _STRING_
	#include <string>
#endif
#ifndef _CSTDLIB_
	#include <cstdlib>
#endif

//! Maximum size of a string buffer.
/*!
* This constant is used as a maximum value for string
* buffers. If this value is exceeded, normally the
* executing function will throw an error.
*/
const std::size_t MAX_STR_BUF = 64 ;

//! Time string handling class
/*!
* This class provides static member functions to get time
* strings from any kind of time-related type (in the STL). It is furthermore
* possible to get them in a special format.
*/
class Time_string {

private :

	/*time_t mRawTime ; // Raw time in seconds since 00:00 1.1.1970*/

	static std::tm *m_time_info ;

	static std::string m_str_buff ;

	static void update(std::chrono::time_point<std::chrono::system_clock> time_pt) ;

public :

	// Member variables
	
	static const std::string TIME ;

	// Time related

	static const std::string SEC ;
	static const std::string MIN ;
	static const std::string HOURS ;

	// Date related

	static const std::string NEW_DATE ;
	static const std::string DATE ;

	// Member functions

	//! Default constructor
	Time_string ( void ) {

		/*update () ; // Get first values

		mStrBuff = "" ; // Initialize string buffer*/
	
	}

	//! Default Destructor
	~Time_string ( void ) {
	}

	static std::string time_str(const std::string& format, 
							    std::chrono::time_point<std::chrono::system_clock> time_pt =
								std::chrono::system_clock::now()) ;

	static std::string raw_time(std::chrono::time_point<std::chrono::system_clock> time_pt =
							    std::chrono::system_clock::now()) ;

	static std::string seconds(std::chrono::time_point<std::chrono::system_clock> time_pt =
							   std::chrono::system_clock::now()) ;
	static std::string minutes(std::chrono::time_point<std::chrono::system_clock> time_pt =
							   std::chrono::system_clock::now()) ;
	static std::string hours(std::chrono::time_point<std::chrono::system_clock> time_pt =
							 std::chrono::system_clock::now()) ;

	static std::string asc_date(std::chrono::time_point<std::chrono::system_clock> time_pt =
							    std::chrono::system_clock::now()) ;

} ;

#endif
