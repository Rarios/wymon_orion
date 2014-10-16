// Window - run.cpp


#ifndef _ORION_
	#include "Orion.hpp"
#endif


// run
// Runs the window's main loop. Thus all event handling
// and update operations will be executed in this function
void gg::Orion::run ( void ) {

	m_win.clear () ; // Clear the window in case something has already been drawn to it // 84 characters!!!

	// Background.
	m_background.load("res/background.jpg") ;
	m_win.draw ( m_background ) ;

	// m_wymon
	m_wymon.load("res/wymon.png", sf::IntRect(0, 0, 108, 96) ;
	m_wymon.insert(frame(0, 0, 106, 96));
	m_wymon.insert(frame(107, 0, 108, 96));
	//m_animFrame = 0.0f ; // Current anim frame
	m_win.draw ( m_wymon ) ;

	// Textfield

	m_textfield.drawBoxes(sf::Vector2u(m_win.getSize().x , m_win.getSize().y)) ;
	m_win.draw(m_textfield) ;

	// Font.
	if (!m_font.loadFromFile("res/NotoSerif-Regular.ttf")) {
	
		std::cerr << "Could not load Noto font" << std::endl;
	
	}

	// Date.
	m_tempDate = m_timer.time_str ( Time_string::DATE ) ;

	m_dateText.str( m_tempDate , m_font) ;
	m_dateText.char_size( 11 ) ;
	m_win.draw ( m_dateText ) ;

	// m_timerText
	m_tempTime = m_timer.time_str ( Time_string::TIME ) ; // Temporary m_timer to control draw update frequency

	m_timerText.str(m_tempTime, m_font) ;
	m_timerText.char_size( 46 ) ;

	m_win.draw ( m_timerText ) ;

	m_win.display () ;

	// Main loop

	setObjectPos () ;

	while ( m_win.isOpen () ) {
	
		processEvents () ;

		render () ;
		
	}

}
