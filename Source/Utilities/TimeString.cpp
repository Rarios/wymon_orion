// Time_string - TimeString.cpp

#include "TimeString.hpp"

OPEN_WO_SYS

// Member constants.

//! Time string format constant.
/*!
* Format: "hh:mm:ss".
*/
const std::string TimeString::TIME = "%H:%M:%S";

// Time related constants.

//! Time string format constant.
/*!
* Format: "ss".
*/
const std::string TimeString::SECONDS = "%S";
//! Time string format constant.
/*!
* Format: "mm".
*/
const std::string TimeString::MINUTES = "%M";
//! Time string format constant.
/*!
* Format: "hh".
*/
const std::string TimeString::HOURS = "%H";

// Date related constants.

//! Time string format constant.
/*!
* Format: "weekday, dd.mm.yyyy".
*/
const std::string TimeString::DATE = "%A, %d.%m.%Y";
//! Time constant.
/*!
* Time when a new calender date starts, "00:00:00".
*/
const std::string TimeString::NEW_DATE = "00:00:00";

// Member variables.

//! Calender time variable.
std::tm* TimeString::mTimeInfo = NULL;

//! String buffer.
std::string TimeString::mStringBuffer = "";

// Member functions

//! Updates calender time variable.
/*!
* Updates the calender time member variable to the
* given point in time.
* \param timePoint Time point used to update calender time variable.
*/
void TimeString::update(std::chrono::time_point<std::chrono::system_clock> timePoint) {
	
	std::time_t tempTime = std::chrono::system_clock::to_time_t(timePoint);
	mTimeInfo = std::localtime(&tempTime);

}

//! Returns time point in a given format.
/*!
* This function takes a format string and uses it for the
* output string. However, if the output string's length
* exceeds MAXIMUM_STRING_BUFFER, an error will be thrown. 
* In this case, instead of the output
* string being the time, it will be an error message,
* starting with "#!".
* \param format Format used to create the time string. Accepts the "std::strftime()" format strings.
* \param timePoint Time point used for the output string. Default: current time point.
* \return String with time in the given format.
*/
std::string TimeString::getTimeString(const std::string& format, 
							      std::chrono::time_point<std::chrono::system_clock> timePoint) {

	char characterBuffer[MAXIMUM_STRING_BUFFER]; // Character buffer for the <ctime> functions.

	update(timePoint);

	std::size_t characterNumber = std::strftime(characterBuffer, MAXIMUM_STRING_BUFFER, format.c_str(), mTimeInfo);

	if (0 == characterNumber) { // 0 is std::strftime's error indicator value.
	
		// An error occured, so write an error message.

		mStringBuffer = "#! Could not create time string";
	
	} else {
	
		mStringBuffer.assign(characterBuffer);
	
	}

	return (mStringBuffer);

}

//! Returns time without format.
/*!
* Returns the given time point as a pure value of seconds.
* \param timePoint Time point used for the output string. Default: current time point.
* \return Time point as seconds within a string.
*/
std::string TimeString::getRawTime(std::chrono::time_point<std::chrono::system_clock> timePoint) {
	
	return (mStringBuffer.assign(std::to_string(
		    std::chrono::system_clock::to_time_t(timePoint))));
	
}

//! Returns passed seconds (0-61).
/*!
* \param timePoint Time point used for the output string. Default: current time point.
* \return String with passed seconds.
*/
std::string TimeString::getSeconds(std::chrono::time_point<std::chrono::system_clock> timePoint) {

	return (getTimeString(SECONDS, timePoint));

}

//! Returns  passed minutes (0-59).
/*!
* \param timePoint Time point used for the output string. Default: current time point.
* \return String with passed minutes.
*/
std::string TimeString::getMinutes(std::chrono::time_point<std::chrono::system_clock> timePoint) {
	
	return (getTimeString(MINUTES, timePoint));
	
}

//! Returns passed hours (0-23).
/*!
* \param timePoint Time point used for the output string. Default: current time point.
* \return String with passed hours.
*/
std::string TimeString::getHours(std::chrono::time_point<std::chrono::system_clock> timePoint) {
	
	return (getTimeString(HOURS, timePoint));
	
}

//! Returns string created with "std::asctime()" format.
/*!
* Returns a string of a time point created with the "std::asctime()" format.
* This will be a standard calender format.
* \param timePoint Time point used for the output string. Default: current time point.
* \return String from "std::asctime()" of given time point.
*/
std::string TimeString::getAsciiDate(std::chrono::time_point<std::chrono::system_clock> timePoint) {

	update(timePoint);
	return (mStringBuffer.assign(std::asctime(mTimeInfo)));
	
}

CLOSE_WO_SYS
