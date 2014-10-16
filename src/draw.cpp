// Textfield - draw.cpp

#include "Textfield.hpp"

void gg::Textfield::draw( sf::RenderTarget& target , sf::RenderStates states ) const {

	target.draw(m_outerBox , states) ;
	target.draw( m_textBox , states ) ;
	target.draw(m_curText , states) ; // Not submitted text

	// Draw all text objects
	for(std::size_t i = 0 ; i < m_limit ; ++ i) {
	
		target.draw(*(m_textPtrList.at(i)) , states) ;

	}

}