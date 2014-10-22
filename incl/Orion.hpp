// Orion
// Orion.hpp

//#define NDEBUG
#ifndef _ORION_
#define _ORION_

#ifndef SFML_GRAPHICS_HPP
#include <SFML/Graphics.hpp>
#endif
#ifndef _SPRITE_ // <cstdlib>; <string>; <iostream>; "debug.hpp"; "namespace.hpp"; "initVal.hpp"
#include "sprite.hpp"
#endif
#ifndef TEXT_HPP
#include "text.hpp"
#endif
#ifndef _TEXTFIELD_
#include "Textfield.hpp"
#endif
#ifndef _ANIMATION_
#include "animation.hpp"
#endif
#ifndef _WINDOW_
#include "Window.hpp"
#endif
#ifndef _Time_string_
#include "Time_string.hpp"
#endif
#include <iostream>

// Orion //
// Orion is the name of the m_wymon "Terminal". It's a program
// desinged to support the user in his daily work. All of the
// functionalities are combined into this one main class

class Orion {

public :

	// Constructor
	Orion(sf::VideoMode mode , const sf::String& title , sf::Uint32 style = sf::Style::Default ,
			const sf::ContextSettings& settings = sf::ContextSettings ()) ;

	// Destructor
	~Orion( void ) {
	}

	bool setWinIcon(std::string filename) {
	
		return(m_win.setWinIcon(filename)) ;
	
	}

	void processEvents ( void ) ;
	void run( void ) ;

	void drawObjects(void) ;

private :

	Window m_win ; // Window; the render target

	Time_string m_timer ; // Main window date/time handling
	sf::Clock m_clock ; // Main m_clock for animations and smooth movement

	Sprite m_background ;
	animation m_wymon ;

	float m_animFrame ; // Current animation frame of m_wymon

	sf::Font m_font;

	text m_timerText ;
	std::string m_tempTime ; // Temporary storage for time value
	text m_dateText ;
	std::string m_tempDate ; // Temporary storage for date value

	Textfield m_textfield ;

	void render( void ) ;

	void setObjectPos( void ) ;

} ;

#endif
