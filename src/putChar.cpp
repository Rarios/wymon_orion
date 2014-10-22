// Textfield - putChar.cpp

#include "Textfield.hpp"
#include <iostream>
#ifndef _DEBUG_
#include "debug.hpp"
#endif

// putChar
// Takes a character; if it is an alphabetic one,
// it is cached; if it is a newline, the cached text
// is saved inside a text object; other characters are
// treated differently
void Textfield::putChar(sf::Uint32 character) {

	/*debug(std::cout << "@putchar(): text entered: " << character << std::endl) ;*/

	// Quick check if its a alphabetic letter
	if(Unicode::is_printable(character)) {
	
		// Character is a letter
		// Cache letter inside sf::String object
		// and store it into temporary text to display
		m_string += character ;
		m_curText.str(m_string) ;

		/*debug(std::cout << "@putChar(): character is alphabetic!" << std::endl) ;*/
		/*debug(std::cout << "@putChar(): Currently cached string is: " << m_string.toAnsiString() << std::endl) ;*/
		/*debug(std::cout << "@putChar(): Size of the text object: " << m_curText.getSize().x << ", " << m_curText.getSize().y << std::endl) ;*/
	
	} else if(Unicode::is_newline(character)) {

		// Enter has been pressed, create
		// a text object holding the current cached
		// string + a newline
		m_string += '\n' ;
		createText(m_string) ;
		// Reset old string and text
		m_string.clear() ;
		m_curText.str(m_string) ;

		debug(std::cout << "@putChar(): new gg::Text!" << std::endl) ;	
	
	} else {

		// Check the intput for function keys (like "enter" or "f1", etc.)
		if(character == Unicode::backspace && !(m_string.isEmpty())) {

			// Delete last character
			m_string.erase(m_string.getSize()-1) ;
			m_curText.str(m_string) ;
	
			// Delete last character
			debug(std::cout << "@putChar(): delete last character!" << std::endl) ;

		}
	
	}

}
