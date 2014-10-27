// Unicode.hpp

#ifndef _UNICODE_
#define _UNICODE_

#ifndef _CSTDLIB_
#include <cstdlib>
#endif

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

	static const key null ;
	
	static const key backspace ;

	static const key h_tab ;

	static const key line_feed ;

	static const key v_tab ;
	
	static const key carriage_return ;

	static const key info_sep_one ;

	static const key space ;
	static const key num_0 ;
	static const key num_9 ;
	static const key letter_A ;
	static const key letter_z ;

	static const key del ;

	static const key apc ;

	// Member functions

	static bool is_alphabetic(const key &letter) ;
	static bool is_numeric(const key &letter) ;
	static bool is_printable(const key &letter) ;
	static bool is_newline(const key &letter) ;

} ;

#endif
