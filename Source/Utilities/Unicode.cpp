// Unicode.cpp - Unicode.hpp

#include <iostream>
#include "Unicode.hpp"

OPEN_WO_SYS

// Constant member variables

//! Null terminator.
/*!
* First non-printable control character of the Unicode character
* tables (v6.3).
*/
const key Unicode::null = 0x00000000;

//! Backspace.
const key Unicode::backspace = 0x00000008;

//! Horizontal tabulator (HT), or character tabulation.
const key Unicode::horizontalTabulator = 0x00000009;

//! Line feed, or End of Line (EOL) character.
const key Unicode::lineFeed = 0x0000000a;

//! Vertical tabulator (VT), or line tabulation. 
const key Unicode::verticalTabulator = 0x0000000b;

//! Carriage return (CR).
const key Unicode::carriageReturn = 0x0000000d;

//! Information separator one, or unit separator (US).
/*!
* Last non-printable control character of the Unicode character 
* tables (v6.3), before the ASCII punctuation and symbols start.
*/
const key Unicode::infoSeparatorOne = 0x0000001f;

//! Whitespace.
/*!
* First printable character of the Unicode character tables (v6.3).
*/
const key Unicode::space = 0x00000020;

//! Number 0.
const key Unicode::number_0 = 0x00000030;

//! Number 9.
const key Unicode::number_9 = 0x00000039;

//! Uppercase latin character "A".
/*!
* First actual latin character of the Unicode character
* tables (v6.3). This character can be refered to as the
* lower bound of a character set called "Alphabetic characters".
*/
const key Unicode::letter_A = 0x00000041;

//! Lowercase latin character "z".
/*!
* Last actual latin character of the Unicode character
* table (v6.3). This character can be refered to as the
* upper bound of a character set called "Alphabetic characters".
*/
const key Unicode::letter_z = 0x0000007a;

//! Delete character.
/*!
* First non-printable control character of the Unicode character 
* tables (v6.3), after the ASCII punctuation and symbols ended.
*/
const key Unicode::del = 0x0000007f;

//! Application programming command.
/*!
* Last non-printable control character of the Unicode character
* tables (v6.3).
*/
const key Unicode::apc = 0x0000009f;

// Static member functions.

//! Returns true if letter is part of the latin alphabet.
/*!
* \param letter Character code of the Unicode character tables (v6.3).
* \return True if the letter is part of the latin alphabet.
*/
bool Unicode::isAlphabetic(const key &letter) {
	
	// Is "letter" bigger than the lower alphabetic
	// bound and bigger than the upper.
	return(letter >= letter_A && letter <= letter_z);
	
}

//! Returns true if letter is within 0 to 9.
/*!
* \param letter Character code of the Unicode character tables (v6.3).
* \return True if letter is within the interval 0 to 9.
*/
bool Unicode::isNumeric(const key &letter) {

	return (number_0 <= letter && number_9 >= letter);

}

//! Returns true if the letter is printable.
/*!
* This function tests whether or not the given letter is inside of
* one of two intervals of command characters. The first one starts at the
* character for "NULL" and ends at the "Information separator one". The
* second starts with the character "DELETE" and ends with the character
* "Application programming command". Then the result of this is inverted,
* such that when it is inside of either one of those intervals, false is 
* returned, and if it is not inside of both, true.
* \param letter Character code of the Unicode character tables (v6.3).
* \return True if the letter is printable (thus not a control character).
*/
bool Unicode::isPrintable(const key &letter) {
	
	/*std::cout << "Printable? ";
	std::cout << !((null <= letter && info_sep_one >= letter) ||
		   (del <= letter && apc >= letter)) << std::endl;*/
	return(!((null <= letter && infoSeparatorOne >= letter) ||
		   (del <= letter && apc >= letter)));
	
}

//! Returns true if letter creates a line break.
/*!
* Different OSes use different represenations of a new line character. Some
* might be using the LF ('\n') character, some the CR ('\r'), or a combination
* of both. Note that this also depends on your settings. This function uses a
* system-independent approach for finding a new line character.
* NOTE: Always use this function to keep the code system-independent.
* \param letter Character code of the Unicode character tables (v6.3).
* \return True if letter creates a new line.
*/
bool Unicode::isNewline(const key &letter) {
	
	// NOTE: as you can see on the wikipedia page:
	// http://en.wikipedia.org/wiki/Newline
	// different OSes use different ways of representing a line feed.
	// Originally, the code used to switch between the OS specific 
	// representation, but since I discovered that my Ubuntu 14.04 also used
	// the CR instead of the LF, I changed the code so it would support both.
	// This might be caused because of a dual boot/keyboard setting.
	return((letter == lineFeed) || (letter == carriageReturn));
	
}

CLOSE_WO_SYS
