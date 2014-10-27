// Textfield
// Textfield.hpp

#ifndef _TEXTFIELD_
#define _TEXTFIELD_

#include <SFML/Graphics.hpp>
#ifndef _TEXT_
#include "text.hpp"
#endif
#ifndef _SPRITE_
#include "sprite.hpp"
#endif
#ifndef _CSTDLIB_
#include <cstdlib>
#endif
#ifndef _UNICODE_
#include "Unicode.hpp"
#endif
#include <string>
#include <list>
#include <array>

const std::size_t default_lim = 4;
const std::size_t default_char_size = 16;

const sf::Color box_bord_color(224, 224, 224 );
const sf::Color outer_box_color(255, 255, 255, 85);
const sf::Color text_box_color(255, 255, 255);

//! Textfield for user input.
/*!
* This class manages user input and its graphical represenation inside a text
* field box.
*/
class Textfield : public sf::Drawable {

private :
	
	// Member variables.

	//! Font used for text field.
	const sf::Font* m_font;
	
	//! Limit of stored submitted texts.
	std::size_t m_lim;

	//! Current text.
	/*!
	* This is the text object holding the unsubmitted text, which is the text
	* the user is currently writing. Note that this variable is used to display
	* the text the user is typing.
	*/
	text m_cur_text;
	//! Holds current text (the text which is not submitted, but written).
	/*!
	* This variable is needed to buffer the user's input text. Without this
	* variable, it would be necessary to get and set the string from the
	* m_cur_text all the time changes have to be made. So the content of this
	* variable and the m_cur_text variable are identical, but as this acts as a
	* buffer, less function calls have to be made.
	*/
	sf::String m_text_buff; 

	//! List holding the texts.
	std::list<text> m_texts;

	//! Box, which holds already submitted text.
	sf::RectangleShape m_outer_box; 
	//! Box, which holds text the user is currently typing.
	sf::RectangleShape m_text_box; 
	
	//! Positions of already submitted texts.
	std::array<sf::Vector2f, default_lim> m_submit_pos;

	//! Spacing between the lines.
	float m_line_spacing;
	//! Height of the text inside the text field.
	float m_text_height;

	// Member functions.

	void store_text(const sf::String& str);
	void upd_text_height();
	void submit_pos();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public :

	// Member functions.
	
	Textfield(const sf::Font* font);
	~Textfield();

	void put_char(const sf::Uint32& character);

	void pos(const sf::Vector2f& pos);

	void draw_box(sf::Vector2u render_size);

	sf::Vector2f size() const;

} ;

#endif
