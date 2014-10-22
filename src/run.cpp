// Window - run.cpp

#ifndef _ORION_
#include "Orion.hpp"
#endif
#include <iostream>

// run
// Runs the window's main loop. Thus all event handling
// and update operations will be executed in this function
void Orion::run ( void ) {

	// Clear the window in case something has already been drawn to it
	m_win.clear () ; 

	// Background.
	if (!m_background.load("res/background.jpg")) {
	
		std::cerr << "Could not load background.jpg\n";
		std::cin.get();
	
	}
	m_win.draw(m_background);

	// m_wymon
	if (!m_wymon.load("res/wymon.png", sf::IntRect(0, 0, 108, 96))) {
	
		std::cerr << "Could not load wymon.png\n";
		std::cin.get();
	
	}
	m_wymon.insert(frame(0, 0, 106, 96));
	m_wymon.insert(frame(107, 0, 108, 96));
	//m_animFrame = 0.0f ; // Current anim frame
	m_win.draw(m_wymon);

	// Textfield
	m_textfield.drawBoxes(sf::Vector2u(m_win.getSize().x , m_win.getSize().y)) ;
	m_win.draw(m_textfield) ;

	// Font.
	if (!m_font.loadFromFile("res/NotoSerif-Regular.ttf")) {
	
		std::cerr << "Could not load Noto font\n";
		std::cin.get();
	
	}

	// Date.
	m_tempDate = m_timer.time_str(Time_string::DATE);

	m_dateText.str(m_tempDate);
	m_dateText.font(m_font);
	m_dateText.char_size(11) ;
	m_win.draw(m_dateText);

	// m_timerText.
	m_tempTime = m_timer.time_str(Time_string::TIME); // Temporary m_timer to control draw update frequency

	m_timerText.str(m_tempTime);
	m_timerText.font(m_font);
	m_timerText.char_size(46) ;
	m_win.draw(m_timerText) ;

	// First display of all objects.
	m_win.display();

	setObjectPos();

	// Main loop
	while (m_win.isOpen()) {
	
		processEvents();
		render();
		
	}

}
