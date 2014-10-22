// Orion.cpp

#include "Orion.hpp"
#ifndef _INITVAL_
#include "initVal.hpp"
#endif

// Constructor
Orion::Orion(sf::VideoMode mode , const sf::String& title , sf::Uint32 style ,
				 const sf::ContextSettings& settings) : m_win(mode , title , style , settings) ,
m_timer() , m_clock() , m_background() , m_wymon() , m_animFrame(INIT_FLOAT) , m_font() , m_timerText() ,
m_tempTime() , m_dateText() , m_tempDate() , m_textfield() {
}

// drawObjects
// Includes all drawObjects
void Orion::drawObjects(void) {

	m_win.clear() ;

	m_win.draw( m_background ) ;	
	m_win.draw( m_timerText ) ;
	m_win.draw( m_wymon ) ;
	m_win.draw( m_dateText ) ;
	m_win.draw( m_textfield ) ;

	m_win.display() ;

}
