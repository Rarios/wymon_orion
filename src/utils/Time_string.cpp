// Time_string - time_str.cpp

#include "Time_string.hpp"

START_GG

// Member variables

//! Calender time variable.
std::tm *Time_string::m_time_info = NULL ;

//! String buffer.
std::string Time_string::m_str_buff = "" ;

// Member functions

//! Updates calender time variable.
/*!
* Updates the calender time member variable to the
* given point in time.
* \param time_pt Time point used to update calender time variable.
*/
void Time_string::update(std::chrono::time_point<std::chrono::system_clock> time_pt) {

	/*try {

		mRawTime = std::time ( NULL ) ; // Update raw time

			if ( mRawTime == -1 ) { // -1 is std::time's error indicator
			
				throw "#! Time couldn't be read" ; 
			
			}

			mTimeInfo = std::localtime ( &mRawTime ) ;

		} catch ( const char* Exept ) {
		
			debug ( std::cout << __FILE__ << "; " << Exept << std::endl ) ;

			debug ( std::cin.get () ) ;

			std::exit ( EXIT_FAILURE ) ;
		
		}*/
	
	std::time_t temp_time = std::chrono::system_clock::to_time_t(time_pt) ;
	m_time_info = std::localtime(&temp_time) ;

}

//! Returns time point in a given format.
/*!
* This function takes a format string and uses it for the
* output string. However, if the output string's length
* exceeds MAX_STR_BUF, an error will be thrown. 
* In this case, instead of the output
* string being the time, it will be an error message,
* starting with "#!".
* \param format Format used to create the time string. Accepts the "std::strftime()" format strings.
* \param time_pt Time point used for the output string. Default: current time point.
* \return String with time in the given format.
*/
std::string Time_string::time_str(const std::string& format, 
							      std::chrono::time_point<std::chrono::system_clock> time_pt) {

	char char_buff[MAX_STR_BUF]; // Character buffer for the <ctime> functions.

	update(time_pt) ;

	std::size_t num = std::strftime(char_buff, MAX_STR_BUF, format.c_str(), m_time_info) ;

	if (num == 0) { // 0 is std::strftime's error indicator value.
	
		// An error occured, so write an error message.

		m_str_buff = "#! Could not create time string" ;
	
	} else {
	
		m_str_buff.assign(char_buff) ;
	
	}

	/*const std::size_t buff_siz = 64 ;
	char *char_buff = NULL ; // Character buffer for the <ctime> functions.

	// Trial and error time string creation.

	for (unsigned int n = 1; n <= MAX_LOOP_ITER; ++ n) {
	
		// Create a buffer with a size that should be capable
		// of the number of characters needed by the time string
		// format. Every loop iteration this buffer size will
		// be set to the new n-th multiple of the original
		// buffer size.

		char_buff = new char[buff_siz * n] ;
		
		// Update before any operation using the calender time variable
		// is executed.

		update() ;

		std::size_t num = std::strftime(char_buff, buff_siz * n, format.c_str (), m_time_info) ;

		if (num != 0) { // 0 is std::strftime's error indicator value.

			// In this case the buffer has been filled successfully.

			m_str_buff.assign(char_buff) ; // Convert c-string to c++ string.

			break ;

		} else {
		
			// An error occured, so write an error message.

			m_str_buff = "#! Buffer not big enough for format" ;
		}
	
	}

	try {

		std::size_t num_char = std::strftime(char_buff, buff_siz, format.c_str (), m_time_info) ;

		if (num_char == 0) { // 0 is std::strftime's error indicator value.
		
			throw "#! Function strftime() ran over max_size" ;
		
		}

		m_str_buff.assign(char_buff) ; // Convert c-string to c++ string.

		if (char_buff) {
		
			// If buffer is still on heap, release it.
			// (A buffer that has previously been released should
			// have the value "NULL".

			delete[] char_buff ;
			char_buff = NULL ;
		
		}

	} catch (const char* Exept) {
	
		debug(std::cout << __FILE__ << "; " << Exept << std::endl) ;

		m_str_buff.assign("#! max_size") ;

		debug(std::cin.get()) ;

		std::exit(EXIT_FAILURE) ;
	
	}*/

	/*if (char_buff) {
		
		// If buffer is still on heap, release it.
		// (A buffer that has previously been released should
		// have the value "NULL".

		delete[] char_buff ;
		char_buff = NULL ;
	
	}*/

	return (m_str_buff) ;

}

//! Returns time without format.
/*!
* Returns the given time point as a pure value of seconds.
* \param time_pt Time point used for the output string. Default: current time point.
* \return Time point as seconds within a string.
*/
std::string Time_string::raw_time(std::chrono::time_point<std::chrono::system_clock> time_pt) {
	
	return (m_str_buff.assign(std::to_string(
		    std::chrono::system_clock::to_time_t(time_pt)))) ;
	
}

//! Returns passed seconds (0-61).
/*!
* \param time_pt Time point used for the output string. Default: current time point.
* \return String with passed seconds.
*/
std::string Time_string::seconds(std::chrono::time_point<std::chrono::system_clock> time_pt) {

	return (time_str(SEC, time_pt)) ;

}

//! Returns  passed minutes (0-59).
/*!
* \param time_pt Time point used for the output string. Default: current time point.
* \return String with passed minutes.
*/
std::string Time_string::minutes(std::chrono::time_point<std::chrono::system_clock> time_pt) {
	
	return (time_str(MIN, time_pt)) ;
	
}

//! Returns passed hours (0-23).
/*!
* \param time_pt Time point used for the output string. Default: current time point.
* \return String with passed hours.
*/
std::string Time_string::hours(std::chrono::time_point<std::chrono::system_clock> time_pt) {
	
	return (time_str(HOURS, time_pt)) ;
	
}

//! Returns string created with "std::asctime()" format.
/*!
* Returns a string of a time point created with the "std::asctime()" format.
* This will be a standard calender format.
* \param time_pt Time point used for the output string. Default: current time point.
* \return String from "std::asctime()" of given time point.
*/
std::string Time_string::asc_date(std::chrono::time_point<std::chrono::system_clock> time_pt) {

	update(time_pt) ;
	return (m_str_buff.assign(std::asctime(m_time_info))) ;
	
}

END_GG