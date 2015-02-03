// Ranom
// main.cpp

#include <iostream>
#include <cstdlib>
#ifndef _ORION_
#include "Orion.hpp"
#endif

signed int main ( void ) {

	// Create Window
	Orion Win(sf::VideoMode(600, 450), "WymonOrion - angad 0.0.0");

	// Create Icon
	if (!(Win.win_icon("res/wymonIcon.png"))) {
	
		std::cerr << "Could not load window icon";
		std::cin.get();
		return EXIT_FAILURE;
	
	}

	Win.run();

	return EXIT_SUCCESS;

}
