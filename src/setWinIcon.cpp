// Window - setWinIcon.cpp


#ifndef _WINDOW_
	#include "Window.hpp"
#endif


const std::size_t MAX_ICON_SIZE = 32 ; // Max. exceptable size of an icon

// setWinIcon //
// Sets the window icon to the image given by
// the file name.
// Returns true if everything was succesful.
// Error is returned either if file wasn't loaded
// of the size of the image extends MAX_ICON_SIZE.

bool gg::Window::setWinIcon ( const std::string& Filename ) {

	if ( !( mWinIcon.loadFromFile ( Filename ) ) ) {
	
		debug ( std::cout << __FILE__ << "!# Couldn't load Icon" << std::endl ) ;

		// Loading operation failed

		return ( false ) ;
	
	}

	sf::Vector2u IconSize = mWinIcon.getSize () ;

	if ( IconSize.x > MAX_ICON_SIZE || IconSize.y > MAX_ICON_SIZE ) {
	
		debug ( std::cout << __FILE__ << "!# Icon size too big" << std::endl ) ;

		return ( false ) ;
	
	}

	this->setIcon ( IconSize.x , IconSize.y , mWinIcon.getPixelsPtr () ) ;

	return ( true ) ;

} // setWinIcon