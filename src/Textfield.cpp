// Textfield - constructor

#ifndef _TEXTFIELD_
#include "Textfield.hpp"
#endif
#include <iostream>

// Default constructor
// The init character "W" is used for calculation of the height
// of the textfield
Textfield::Textfield( void ) : m_limit( defaultLimit ) ,
m_textArray(m_limit, text(std::string(""), sf::Font(), sf::Color::Black, 16)), 
m_textPtrList(m_limit),
m_string(), m_outerBox(), m_textBox(), 
m_curText(std::string(""), sf::Font(), sf::Color::Black, 16), 
sizeTextIndic("W", sf::Font(), sf::Color::Black, 16) , m_lineSpacing(2.0f) ,
m_posWritten(m_limit), m_font() {

	// Load font for the Textfield.
	if (!m_font.loadFromFile("res/NotoSerif-Regular.ttf")) {
	
		std::cerr << "Could not load Noto font, Textfield\n";
		std::cin.get();
	
	}
	
	// Set the font which previously could not be done.
	m_curText.font(m_font);
	sizeTextIndic.font(m_font);

	initList() ;

	m_curText.setPosition(sf::Vector2f(100.0f , 100.0f)) ;

	m_textHeight = sizeTextIndic.obj_size().y + 2 * m_lineSpacing ; // Height of the text + 2x line spacing (top and bottom)

}

// Limit set constructor
Textfield::Textfield( std::size_t limit ) : m_limit( limit ) ,
m_textArray(m_limit, text(std::string(""), sf::Font(), sf::Color::Black, 16)), 
m_textPtrList(m_limit),
m_string(), m_outerBox(), m_textBox(), 
m_curText(std::string(""), sf::Font(), sf::Color::Black, 16),  
sizeTextIndic("W", sf::Font(), sf::Color::Black , 16), m_lineSpacing(2.0f),
m_posWritten(m_limit), m_font() {
	
	// Load font for the Textfield.
	if (!m_font.loadFromFile("res/NotoSerif-Regular.ttf")) {
	
		std::cerr << "Could not load Noto font, Textfield\n";
		std::cin.get();
	
	}
	
	// Set the font which previously could not be done.
	m_curText.font(m_font);
	sizeTextIndic.font(m_font);

	initList() ;

	m_curText.setPosition(sf::Vector2f(100.0f , 100.0f)) ;

	m_textHeight = sizeTextIndic.obj_size().y + 2 * m_lineSpacing ; // Height of the text + 2x line spacing (top and bottom)

}

// initList
// Initialize the list of pointers to Text objects

void Textfield::initList( void ) {

	auto lIt = m_textPtrList.begin() ; // List iterator

	for( auto vIt = m_textArray.begin() ; vIt != m_textArray.end() && lIt != m_textPtrList.end() ; ++ vIt , ++ lIt ) {
	
		// Set the pointer to the address of the nth Text object

		*lIt = std::make_shared<text>(*vIt) ;

	}

}

// createText
// Takes a sf::String and Stores it inside
// the next possible gg::Text object without
// creating a new one
void Textfield::createText(const sf::String& str) {

	// Insert ">> " at start of the line
	sf::String tempStr = str ;
	tempStr.insert(0 , sf::String(">> ")) ;

	// Push back new text object in text array
	m_textArray.push_back(text(tempStr.toAnsiString(), m_font, sf::Color::Black, 16)) ;

	// Rearrange pointers
	// Delete last and insert current element as pointer on front
	m_textPtrList.pop_back() ;
	m_textPtrList.emplace(m_textPtrList.begin() , std::make_shared<text>(m_textArray.back())) ;

	// Renew the positions
	setPosWritten() ;

}

// size
// Returns the maximum size of the textfield object
sf::Vector2f Textfield::size(void) {

	return(m_outerBox.getSize()) ;

}
