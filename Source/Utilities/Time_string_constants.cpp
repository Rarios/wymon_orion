// Time_string - getTimeStr.cpp

#include "Time_string.hpp"

//! Time string format constant.
/*!
* Format: "hh:mm:ss".
*/
const std::string Time_string::TIME = "%H:%M:%S" ;

// Time related constants.

//! Time string format constant.
/*!
* Format: "ss".
*/
const std::string Time_string::SEC = "%S" ;
//! Time string format constant.
/*!
* Format: "mm".
*/
const std::string Time_string::MIN = "%M" ;
//! Time string format constant.
/*!
* Format: "hh".
*/
const std::string Time_string::HOURS = "%H" ;

// Date related constants.

//! Time string format constant.
/*!
* Format: "weekday, dd.mm.yyyy".
*/
const std::string Time_string::DATE = "%A, %d.%m.%Y" ;
//! Time constant.
/*!
* Time when a new calender date starts, "00:00:00".
*/
const std::string Time_string::NEW_DATE = "00:00:00" ;
