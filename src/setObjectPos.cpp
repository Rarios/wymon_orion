// Orion - initObjectPos.cpp

#ifndef _ORION_
#include "Orion.hpp"
#endif

// setObjectPos
// Sets the position of all objects on the screen

void Orion::setObjectPos( void ) {

	// Size vars for calculations

	sf::Vector2u renderSize = m_win.getSize(); // Size of the render region of the window (excluding borders, etc.)
	sf::Vector2f wymonSize = m_wymon.max_obj_size();
	sf::Vector2f timerSize = m_timerText.size();
	sf::Vector2f dateSize = m_dateText.size();
	sf::Vector2f textfieldSize = m_textfield.size();

	float a = 20.0f ;
	float b = static_cast<float>( renderSize.y ) / 10.0f ;

	/*// Debug with size output

	debug( std::cout << "NAME: " << "WIDTH, HEIGHT" << std::endl ) ;
	debug( std::cout << "renderSize: " << renderSize.x << ", " << renderSize.y << std::endl ) ;
	debug( std::cout << "wymonSize: " << wymonSize.x << ", " << wymonSize.y << std::endl ) ;
	debug( std::cout << "timerSize: " << timerSize.x << ", " << timerSize.y << std::endl ) ;
	debug( std::cout << "dateSize: " << dateSize.x << ", " << dateSize.y << std::endl ) ;
	debug(std::cout << "textfieldSize: " << textfieldSize.x << ", " << textfieldSize.y << std::endl) ;*/

	// Position vars; calculated later on

	sf::Vector2f wymonPos ;
	sf::Vector2f timerPos ;
	sf::Vector2f datePos ;
	sf::Vector2f textfieldPos ;

	// Calculation the positions of the objects

	// Wymon

	wymonPos.x = static_cast<float>( renderSize.x / 2 - ( wymonSize.x + a + 
								   ( ( timerSize.x > dateSize.x ) ? timerSize.x : dateSize.x ) ) / 2 ) ; // Center rule

	wymonPos.y = b ;

	//debug( std::cout << "wymonPos:" << wymonPos.x << ", " << wymonPos.y << std::endl ) ;

	// Timer

	timerPos.x = wymonPos.x + wymonSize.x + a ;

	timerPos.y = wymonPos.y + ( wymonSize.y / 2 - timerSize.y / 2 ) ; // Center rule

	// Date

	datePos.x = timerPos.x ;

	datePos.y = timerPos.y + timerSize.y ;

	// Textfield
	float outerBottomOffset = 20.0f ; // Space between window bottom and outer box bottom

	textfieldPos.x = renderSize.x / 2 - textfieldSize.x / 2 ;
	textfieldPos.y = renderSize.y - textfieldSize.y - outerBottomOffset ;

	/*debug(std::cout << "textfieldPos calc = " << renderSize.x / 2 - textfieldPos.x / 2 << std::endl) ;
	debug(std::cout << "textfieldPos: " << textfieldPos.x << ", " << textfieldPos.y << std::endl) ;*/

	// Set all positions

	m_wymon.setPosition( wymonPos ) ;
	m_timerText.setPosition( timerPos ) ;
	m_dateText.setPosition( datePos ) ;
	m_textfield.setPos(textfieldPos) ;

}
