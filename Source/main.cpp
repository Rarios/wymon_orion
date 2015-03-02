// Ranom
// main.cpp

#include <iostream>
#include <cstdlib>
#ifndef _ORION_
#include "Orion.hpp"
#endif

signed int main ( void ) {

	// Create Window
	Orion Win(sf::VideoMode(600, 450), "WymonOrion - kismed 2015_02_19");

	// Create Icon
	if (!(Win.win_icon("Resources/wymonIcon.png"))) {
	
		std::cerr << "Could not load window icon";
		std::cin.get();
		return EXIT_FAILURE;
	
	}

	Win.run();

	return EXIT_SUCCESS;

}
