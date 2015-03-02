// Textfield - constructor

#include "Textfield.hpp"
#include <iostream>

//! Font constructor.
/*!
* Creates text field with the given font.
*/
Textfield::Textfield(const sf::Font* font) :
m_font(),
m_lim(default_lim),
m_cur_text(sf::String(L""), nullptr, sf::Color::Black, default_char_size), 
m_texts(m_lim, wo::gfx::Text(sf::String(L""), nullptr, sf::Color::Black, default_char_size)),
m_app_text(sf::String(L">> "), nullptr, sf::Color::Black, default_char_size),
m_app_w{24.f},
m_outer_box(), m_text_box(), 
m_submit_pos(),  
m_line_spacing(2.f), m_col_spacing(2.f),
m_text_height{} {

	m_font = font;

	m_cur_text.setFont(m_font);
	m_app_text.setFont(m_font);
	m_cur_text.setPosition(sf::Vector2f(100.f , 100.f));
	
	m_text_height = static_cast<float>(2 * m_line_spacing + default_char_size);

}

//! Default destructor.
Textfield::~Textfield() {
}

//! Store given string at the beginning of the array.
/*!
* Stores the given string as text object at the beginning of the text array,
* which holds all the text that has been submitted. Shifts each text backwards
* and removes the last one. Also, before storing the text, it adds funny arrows
* at the start.
* \param str String to store.
*/
void Textfield::store_text(const sf::String& str) {

	// Insert user specific text at start of line.
	auto tmp_str = str;
	tmp_str.insert(0 , m_app_text.getString());

	// Push new text, remove last one.
	m_texts.push_front(wo::gfx::Text(tmp_str, m_font, sf::Color::Black, 
							default_char_size));
	m_texts.pop_back();
	
	// Renew the positions
	submit_pos();

}

//! Set the submitted text's position.
/*!
* This function sets all members of m_texts, which are all the texts already
* submitted by the user, to the position calculated in calc_pos().
*/
void Textfield::submit_pos(void) {

	auto text_it = m_texts.begin();
	auto pos_it = m_submit_pos.begin();
	while(text_it != m_texts.end()) {
		
		// One clear assumtion is made here:
		// m_texts.size() == m_submit_pos.size()
		// Note that due to the way those two containers are initialized, this
		// assumtion should always hold true.
		text_it->setPosition(*pos_it);

		++ text_it;
		++ pos_it;
	
	}

}

//! Test unsubmitted text width.
/*!
* This functions tests whether or not the unsubmitted text would be too wide if
* it was submitted. Too wide means that the width of the text in submitted form
* (with m_app_text at the beginning) exeeds the width of the text box itself.
*/
bool Textfield::is_too_wide() {

	return ((m_cur_text.getObjectSize().x + m_app_w + m_col_spacing)
			 > 
			 m_text_box.getSize().x);

}

//! Draw to render target.
/*!
* This function draws all objects to the given render target.
* \param target Render target to draw to.
* \param states Render states used while drawing.
*/
void Textfield::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(m_outer_box, states);
	target.draw(m_text_box, states);
	// Unsubmitted text.
	target.draw(m_cur_text, states);

	// Draw all the submitted texts.
	for(const auto& text : m_texts) {
	
		target.draw(text, states);

	}

}

//! Acts according to the given character.
/*!
* This function acts to the given character. If it is a graphically
* representable one, it is store at the end of the text buffer, for example.
* \param character Character, which decides how the buffer should be changed.
*/
void Textfield::put_char(const sf::Uint32& character) {

	// Check if the character is graphically representable.
	if(wo::sys::Unicode::isPrintable(character)) {
	
		// Store the letter inside buffer and hand it over to the text object,
		// so it can be displayed as not submitted text.
		m_text_buff += character;
		m_cur_text.setString(m_text_buff);

		if (is_too_wide()) {
		
			m_text_buff.erase(m_text_buff.getSize() - 1);
			m_cur_text.setString(m_text_buff);
		
		}

	} else if(wo::sys::Unicode::isNewline(character)) {

		// Text is submitted, store it inside the submitted text array and
		// clear the content from the buffer and current text.
		m_text_buff += character;
		store_text(m_text_buff);

		m_text_buff.clear();
		m_cur_text.setString(m_text_buff);

	} else {

		// Check the intput for function keys (like "enter" or "f1", etc.)
		// NOTE: Only backspace is supported at the moment.
		if(character == wo::sys::Unicode::backspace && !(m_text_buff.isEmpty())) {

			// Delete last character.
			m_text_buff.erase(m_text_buff.getSize()-1);
			m_cur_text.setString(m_text_buff);
	
		}
	
	}

}

//! Set all innner object's position.
/*!
* This function sets the position of all inner objects, such as texts and text
* box. It calculates the position relative to the outer box.
*/
void Textfield::pos(const sf::Vector2f& pos) {

	// Center everything relative to the outer box, which itself is centered
	// relative to the rest of the window elsewhere.
	m_outer_box.setPosition(pos);
	
	sf::Vector2f text_box_pos;
	// Position of unsubmitted text.
	sf::Vector2f text_pos;

	// Calculate position of text box.
	// + pos.x because the first part only calculates pos relative to outer box
	// Add "+pos", because the first part only calculates the position
	// relative to the outer box. To translate it into global coordinates, add
	// the outer box position offset (pos.x or pos.y).
	text_box_pos.x = pos.x + padding;
	text_box_pos.y = pos.y + 2 * padding + m_lim * m_text_height;
	/*text_box_pos.x = outer_box_size.x / 2 - text_box_size.x / 2 + pos.x;
	text_box_pos.y = outer_box_size.y - text_box_size.y - bottom_off + 
					 pos.y - margin;*/

	// Adjust position of text to text box.
	text_pos.x = text_box_pos.x + m_col_spacing;
	text_pos.y = text_box_pos.y + m_line_spacing;

	// Calc position of already submitted text.
	for(auto it = m_submit_pos.begin(); it != m_submit_pos.end(); ++ it) {
	
		if(it == m_submit_pos.begin()) {
		
			it->x = text_pos.x;
			// Only the first one has to take the border into account.
			it->y = text_pos.y - m_text_height - 
					m_text_box.getOutlineThickness() - padding;

		} else {
		
			it->x = text_pos.x;
			// Go one text size higher, relative to previous y-position.
			it->y = (it - 1)->y - m_text_height;
		
		}

	}

	m_text_box.setPosition(text_box_pos);
	m_cur_text.setPosition(text_pos);
	submit_pos();

}

void Textfield::draw_box(sf::Vector2u render_size) {

	// Multiply by the number of submitted texts (m_lim) plus one for the 
	// unsubmitted one. 3x padding, one for the space between bottom and text
	// box, one for the space between text box and submitted text and one for
	// the space between submitted text and upper border.
	sf::Vector2f outer_box_size(
	static_cast<float>(render_size.x - 2 * border - 2 * margin), 
	static_cast<float>((m_lim + 1) * m_text_height + 3 * padding));
	m_outer_box.setSize(outer_box_size);

	m_text_box.setSize(sf::Vector2f(outer_box_size.x - 2 * padding, 
									m_text_height));

	// Render shape, outer box.
	m_outer_box.setOutlineThickness(border);
	m_outer_box.setOutlineColor(box_bord_color);
	m_outer_box.setFillColor(outer_box_color);

	// Render shape, text box.
	m_text_box.setOutlineThickness(1.f);
	m_text_box.setOutlineColor(text_bord_color);
	m_text_box.setFillColor(text_box_color);

}

//! Return size of text field.
/*!
* Returns the size of the text field, which is actually the size of the outer
* box.
*
* NOTE: This function does not take the border (outline thickness) into
* account!
* \return Size of the text field.
*/
sf::Vector2f Textfield::size() const {

	return(m_outer_box.getSize());

}
