// Orion - render.cpp


#ifndef _ORION_
	#include "Orion.hpp"
#endif


// render
// Function which processes all
// render specific operations

void gg::Orion::render( void ) {

	if( m_timer.time_str ( Time_string::TIME ) != m_tempTime ) {

		m_tempTime = m_timer.time_str( Time_string::TIME ) ; // Update time text object
		m_timerText.setStr( m_tempTime , gg::Font::arial ) ;

		// Only update the date if time
		// is equal to 00:00:00

		if( m_tempTime == Time_string::NEW_DATE ) { /* WORKS !!!!! */
			
			m_tempDate = m_timer.time_str( Time_string::DATE ) ;
			m_dateText.setStr( m_tempDate , gg::Font::arial ) ;
			
		}

		drawObjects() ;

	}

	// Animate m_wymon Sprite //

	m_animFrame += 1.0f * m_clock.restart().asSeconds() ;

	// Test if animation frame reached end
			
	if( m_animFrame >= 2.0f ) {
			
		m_animFrame -= 2.0f ;
		
	}

	if( !m_wymon.renderUniFrame( m_animFrame ) ) {
	
		//debug( std::cin.get() ) ;

	}

	drawObjects() ;

}