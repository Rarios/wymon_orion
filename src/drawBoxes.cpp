// Textfield - drawBoxes.cpp

#ifndef _TEXTFIELD_
#include "Textfield.hpp"
#endif

void Textfield::drawBoxes(sf::Vector2u renderSize) {

	unsigned int a = 10 ; // Space between outer and text box
	unsigned int b = 5 ; // Space between bottom text and bottom outer box
	unsigned int c = 20 ; // Space between window border and outer box border (sides)

	sf::Vector2f outerBoxSiz(static_cast<float>(renderSize.x - 2 * c) , 5.0f * m_textHeight + 10.0f) ; // 5x m_textHeight -> four visible 
																									   // written messages + 1 not submitted; 10.0
																									   // is the offset at the bottom of the text box
																									   // -> this might be done better later on
	m_outerBox.setSize(outerBoxSiz) ;

	sf::Vector2f textBoxSiz(outerBoxSiz.x - 2 * a , m_textHeight) ;
	m_textBox.setSize(textBoxSiz) ;

	// Draw shape, outerBox
	m_outerBox.setOutlineThickness(1.0f) ;
	m_outerBox.setOutlineColor(boxBorder) ;
	m_outerBox.setFillColor(outerBox) ;

	// Draw shape, textBox
	m_textBox.setOutlineThickness(1.0f) ;
	m_textBox.setOutlineColor(boxBorder) ;
	m_textBox.setFillColor(textBox) ;

}
