// Ranom
// main.cpp

#include <iostream>
#include <cstdlib>
#ifndef _ORION_
#include "Orion.hpp"
#endif
#ifndef _DEBUG_
#include "debug.hpp"
#endif


signed int main ( void ) {

	// Create Window
	Orion Win(sf::VideoMode ( 600 , 450 ), "WymonOrion - angad 0.0.0" ) ;

	// Create Icon
	if (!(Win.setWinIcon("res/wymonIcon.png"))) {
	
		debug ( std::cout << __FILE__ << "#! Couldn't load icon" << std::endl ) ;
		debug ( std::cin.get () ) ;
		return EXIT_FAILURE;
	
	}

	Win.run();

	return EXIT_SUCCESS;

}
