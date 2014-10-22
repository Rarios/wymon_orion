// Textfield - setPos.cpp

#include "Textfield.hpp"
#ifndef _DEBUG_
#include "debug.hpp"
#endif
#include <iostream>

// setPos
// Takes the position of the outermost box
// and calculates the position of all other objects
void Textfield::setPos(const sf::Vector2f& pos) {

	// Center text box relative to outer box (which itself is centered relative to the window
	m_outerBox.setPosition(pos) ; // pos equals the position of the outermost object of textfield
	
	sf::Vector2f sizeOuterBox = m_outerBox.getSize() ;
	sf::Vector2f sizeTextBox = m_textBox.getSize() ;
	sf::Vector2f posTextBox ;

	// Calculate position of text box
	float textBoxOffset = 10.0f ; // Offset to bottom of outer box

	posTextBox.x = sizeOuterBox.x / 2 - sizeTextBox.x / 2 + pos.x ; // + pos.x because the first part only calculates pos relative to outer box
																	// and after that the x (or y) coordinate has to be added to set it relative to
																	// the window
	posTextBox.y = sizeOuterBox.y - sizeTextBox.y - textBoxOffset + pos.y ;

	// Calculate the positions of the text objects
	float colSpacing = m_lineSpacing ; // Offset to the left of text to text box 

	sf::Vector2f posText ; // Position of not submitted text

	// Adjust position of text to text box
	posText.x = posTextBox.x + colSpacing ;
	posText.y = posTextBox.y + m_lineSpacing ;

	// Calc pos of already written text
	for(auto it = m_posWritten.begin() ; it != m_posWritten.end() ; ++ it) {
	
		if(it == m_posWritten.begin()) {
		
			// First one different
			it->x = posText.x ;
			it->y = posText.y - m_textHeight - m_textBox.getOutlineThickness() ; // 2 line spaces higher and including the thickness of the border

			debug(std::cout << "Position of text: " << it->x << ", " << it->y << std::endl) ;
		
		} else {
		
			// Previous one + line spacing for both (top and bottom)
			it->x = (it - 1)->x ;
			it->y = (it - 1)->y - m_textHeight ;

			debug(std::cout << "Position of text: " << it->x << ", " << it->y << std::endl) ;
		
		}

	}

	// Set all positions
	m_textBox.setPosition(posTextBox) ;
	m_curText.setPosition(posText) ;
	setPosWritten() ;

}

// setm_posWritten
// Set the position of the written text
void Textfield::setPosWritten(void) {

	for(std::size_t it = 0 ; it < m_textPtrList.size() ; ++ it) {
	
		m_textPtrList[it]->setPosition(m_posWritten[it]) ;

		debug(std::cout << "Vector2f with position: " << m_posWritten[it].x << ", " << m_posWritten[it].y << std::endl) ;
		debug(std::cout << "Position of text objects after setting: " << m_textPtrList[it]->getPosition().x << ", " << m_textPtrList[it]->getPosition().y << std::endl) ;
	
	}

}
