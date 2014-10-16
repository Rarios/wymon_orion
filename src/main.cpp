// Ranom
// main.cpp


#ifndef _IOSTREAM_
	#include <iostream>
#endif
#ifndef _CSTDLIB_
	#include <cstdlib>
#endif
#ifndef _ORION_
	#include "Orion.hpp"
#endif
#ifndef _DEBUG_
	#include "debug.hpp"
#endif


signed int main ( void ) {

	// Create Window

	gg::Orion Win ( sf::VideoMode ( 600 , 450 ) , "Ranom - Orion - indev 0.2.0" ) ;

	// Create Icon

	if ( !(Win.setWinIcon ( "resources/wymonIcon.png" ) ) ) {
	
		debug ( std::cout << __FILE__ << "#! Couldn't load icon" << std::endl ) ;
		debug ( std::cin.get () ) ;
		return ( EXIT_FAILURE ) ;
	
	}

	Win.run () ;

	return ( EXIT_SUCCESS ) ;

}