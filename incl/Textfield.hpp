// Textfield
// Textfield.hpp

#ifndef _TEXTFIELD_
#define _TEXTFIELD_

#ifndef _TEXT_
#include "text.hpp" // <SFML/Grafics.hpp>; <iostream>; "debug.hpp"; "namespace.hpp"
#endif
#ifndef _SPRITE_
#include "sprite.hpp"
#endif
#ifndef _CSTDLIB_
#include <cstdlib>
#endif
#ifndef _VECTOR_
#include <vector>
#endif
#ifndef _MEMORY_
#include <memory>
#endif
#ifndef _UNICODE_
#include "Unicode.hpp"
#endif

START_GG

const std::size_t defaultLimit = 4 ;

const sf::Color boxBorder ( 224 , 224 , 224 ) ;

const sf::Color outerBox ( 255 , 255 , 255 , 85 ) ;

const sf::Color textBox ( 255 , 255 , 255 ) ;

// Textfield
// Textfield is a class providing a text input handling
// mechanism; it also offers a gui interface

class Textfield : public sf::Drawable {

public :

	// Constructor

	Textfield( void ) ;

	Textfield( std::size_t limit ) ;

	// Destructor

	~Textfield( void ) {
	}

	void putChar( sf::Uint32 character ) ;
	
	void drawBoxes( sf::Vector2u renderSize ) ;

	void setSize(sf::Vector2u siz) ;

	sf::Vector2f size(void) ;

	void setPos(const sf::Vector2f& pos) ;

private :

	text sizeTextIndic ; // Size indicator for text objects

	std::size_t m_limit ; // Limit for the number of storeable text object

	text m_curText ; // Text which the user has not yet submitted

	std::vector<text> m_textArray ; // Array which stores the actual text elements

	std::vector<std::shared_ptr<Text>> m_textPtrList ; // List for accessing different text objects in the array (better performance)

	sf::String m_string ; // Holds current text (the text which is not entered, but already written)

	sf::RectangleShape m_outerBox ; // Box which holds already entered text

	sf::RectangleShape m_textBox ; // Box which holds current text the user is typing
	
	std::vector<sf::Vector2f> m_posWritten ; // Positions of already written text

	float m_lineSpacing ;

	float m_textHeight ;

	Unicode unicode ;

	void initList( void ) ;

	void draw( sf::RenderTarget& target , sf::RenderStates states ) const ;

	void createText(const sf::String& str) ;

	void setPosWritten() ;

} ;

END_GG

#endif
