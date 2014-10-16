// Unicode.cpp - Unicode.hpp

#include "Unicode.hpp"

// Constant member variables

//! Null terminator.
/*!
* First non-printable control character of the Unicode character
* tables (v6.3).
*/
const key Unicode::null = 0x00000000 ;

//! Backspace.
const key Unicode::backspace = 0x00000008 ;

//! Horizontal tabulator (HT), or character tabulation.
const key Unicode::h_tab = 0x00000009 ;

//! Line feed, or End of Line (EOL) character.
const key Unicode::line_feed = 0x0000000a ;

//! Vertical tabulator (VT), or line tabulation. 
const key Unicode::v_tab = 0x0000000b ;

//! Carriage return (CR).
const key Unicode::carriage_return = 0x0000000d ;

//! Information separator one, or unit separator (US).
/*!
* Last non-printable control character of the Unicode character 
* tables (v6.3), befor the ASCII punctuation and symbols start.
*/
const key Unicode::info_sep_one = 0x0000001f ;

//! Whitespace.
/*!
* First printable character of the Unicode character tables (v6.3).
*/
const key Unicode::space = 0x00000020 ;

//! Number 0.
const key Unicode::num_0 = 0x00000030 ;

//! Number 9.
const key Unicode::num_9 = 0x00000039 ;

//! Uppercase latin character "A".
/*!
* First actual latin character of the Unicode character
* tables (v6.3). This character can be refered to as the
* lower bound of a character set called "Alphabetic characters".
*/
const key Unicode::letter_A = 0x00000041 ;

//! Lowercase latin character "z".
/*!
* Last actual latin character of the Unicode character
* table (v6.3). This character can be refered to as the
* upper bound of a character set called "Alphabetic characters".
*/
const key Unicode::letter_z = 0x0000007a ;

//! Delete character.
/*!
* First non-printable control character of the Unicode character 
* tables (v6.3), after the ASCII punctuation and symbols ended.
*/
const key Unicode::del = 0x0000007f ;

//! Application programming command.
/*!
* Last non-printable control character of the Unicode character
* tables (v6.3).
*/
const key Unicode::apc = 0x0000009f ;

// Static member functions.

//! Returns true if letter is part of the latin alphabet.
/*!
* \param letter Character code of the Unicode character tables (v6.3).
* \return True if the letter is part of the latin alphabet.
*/
bool Unicode::is_alphabetic(const key &letter) {
	
	// Is "letter" bigger than the lower alphabetic
	// bound and bigger than the upper.
	return(letter >= letter_A && letter <= letter_z) ;
	
}

//! Returns true if letter is within 0 to 9.
/*!
* \param letter Character code of the Unicode character tables (v6.3).
* \return True if letter is within the interval 0 to 9.
*/
bool Unicode::is_numeric(const key &letter) {

	return (num_0 <= letter && num_9 >= letter) ;

}

//! Returns true if the letter is printable.
/*!
* This function test whether or not the given letter is inside of
* one of two intervals of command characters. The first one starts at the
* character for "NULL" and ends at the "Information separator one". The
* second starts with the character "DELETE" and ends with the character
* "Application programming command". Then the result of this is inverted,
* such that when it is inside of either one of those intervals, false is 
* returned, and if it is not inside of both, true.
* \param letter Character code of the Unicode character tables (v6.3).
* \return True if the letter is printable (thus not a control character).
*/
bool Unicode::is_printable(const key &letter) {
	
	return(!((null <= letter && info_sep_one >= letter) ||
		   (del <= letter && apc >= letter))) ;
	
}

//! Returns true if letter creates a line break.
/*!
* A new line is created differently depending on the OS. On Windows, first
* there is a line feed ('\n') and then comes a carriage return ('\r').
* Other OSes might just write a line feed. However, it is the last character
* written, which should be checked. This function handles this automatically.
* \param letter Character code of the Unicode character tables (v6.3).
* \return True if letter creates a new line.
*/
bool Unicode::is_newline(const key &letter) {
	
	#ifdef _MSC_VER // Only defined on MS Visual Studio, so only works on Windows!
		// Only for windows operation systems.
		return(letter == carriage_return) ;
	#else
		// Other OSes, like Unix based.
		return(letter == lineFeed) ;
	#endif
	
}