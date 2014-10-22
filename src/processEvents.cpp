// Window - processEvents.cpp

#ifndef _ORION_
#include "Orion.hpp"
#endif

void Orion::processEvents ( void ) {

	sf::Event Events ; // Event structure

	while ( m_win.pollEvent ( Events ) ) {
		
		switch ( Events.type ) {
			
			case sf::Event::TextEntered : {
				   
				m_textfield.putChar(Events.text.unicode) ;

			} break ;

			case sf::Event::Resized : {

				m_win.setView ( sf::View( sf::FloatRect( 0.0f , 0.0f , static_cast<float>( m_win.getSize().x ) , static_cast<float>( m_win.getSize().y ) ) ) ) ;
					
				/*m_background.changeFrame (0 , sf::IntRect( 1856 , 1255 , static_cast<signed int>( m_win.getSize().x ) ,
									   static_cast<signed int>( m_win.getSize().y ) ) ) ;*/

				setObjectPos() ;
									  
			} break ;

			case sf::Event::Closed : {

				// Close Window
				m_win.close () ;
											
			} break ;
			
		}
		
	}

} // processEvents
