// Unicode.hpp

#ifndef SYSTEM_UNICODE
#define SYSTEM_UNICODE

#include <cstdlib>
#include "Namespace.hpp"

OPEN_WO_SYS

//! Typedef for more code readability
typedef std::size_t key;

//! Unicode handling class
/*!
* This pure static class provides functions and constant
* variables to deal with Unicode characters of the Unicode
* character tables (v6.3).
*/
class Unicode {

public :

	// Member variables

	static const key null;
	static const key backspace;
	static const key horizontalTabulator;
	static const key lineFeed;
	static const key verticalTabulator;
	static const key carriageReturn;
	static const key infoSeparatorOne;

	static const key space;
	static const key number_0;
	static const key number_9;
	static const key letter_A;
	static const key letter_z;

	// 'delete' is a reserved term
	static const key del;

	static const key apc;

	// Member functions

	static bool isAlphabetic(const key &letter);
	static bool isNumeric(const key &letter);
	static bool isPrintable(const key &letter);
	static bool isNewline(const key &letter);

};

CLOSE_WO_SYS

#endif
