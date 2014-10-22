// Orion - render.cpp

#ifndef _ORION_
#include "Orion.hpp"
#endif

// render
// Function which processes all
// render specific operations
void Orion::render( void ) {

	if(m_timer.time_str(Time_string::TIME) != m_tempTime) {

		m_tempTime = m_timer.time_str(Time_string::TIME) ; // Update time text object
		m_timerText.str(m_tempTime) ;
		m_timerText.font(m_font);

		// Only update the date if time
		// is equal to 00:00:00

		if (m_tempTime == Time_string::NEW_DATE) { /* WORKS !!!!! */
			
			m_tempDate = m_timer.time_str(Time_string::DATE) ;
			m_dateText.str(m_tempDate) ;
			m_dateText.font(m_font);
			
		}

		drawObjects() ;

	}

	// Animate m_wymon animation.
	sf::Time elap_time;
	elap_time = m_clock.restart();
	
	// Update elapsed time and check if limit is reached. If yes, render frame
	// and restart the clock.
	elap_time = m_clock.getElapsedTime();
	if (500.f <= elap_time.asMilliseconds()) {
	
		m_wymon.render();
		m_clock.restart();
	
	}

	/*m_animFrame += 1.0f * m_clock.restart().asSeconds() ;

	// Test if animation frame reached end
			
	if( m_animFrame >= 2.0f ) {
			
		m_animFrame -= 2.0f ;
		
	}

	if( !m_wymon.renderUniFrame( m_animFrame ) ) {
	
		//debug( std::cin.get() ) ;

	}*/

	drawObjects();

}
