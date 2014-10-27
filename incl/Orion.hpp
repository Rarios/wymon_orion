// Orion
// Orion.hpp

//#define NDEBUG
#ifndef _ORION_
#define _ORION_

#ifndef SFML_GRAPHICS_HPP
#include <SFML/Graphics.hpp>
#endif
#ifndef _SPRITE_
#include "sprite.hpp"
#endif
#ifndef TEXT_HPP
#include "text.hpp"
#endif
#ifndef _TEXTFIELD_
#include "Textfield.hpp"
#endif
#ifndef _ANIMATION_
#include "animation.hpp"
#endif
#ifndef _Time_string_
#include "Time_string.hpp"
#endif
#include <iostream>

// Orion //
// Orion is the name of the m_wymon "Terminal". It's a program
// desinged to support the user in his daily work. All of the
// functionalities are combined into this one main class

//! Orion class.
/*!
* This class holds the main entry point for the program, as well as all the
* data needed by the program, such as background, animation, etc.
*/
class Orion {

private :

	//! Window used as a render target.
	sf::RenderWindow m_win;
	//! Window icon.
	sf::Image m_win_icon;

	//! Window time and date string handling.
	Time_string m_time_str;

	//! Window background.
	Sprite m_background;

	//! Wymon animation.
	animation m_wymon;
	//! Clock for the Animation
	sf::Clock m_clock;
	//! Elapsed time since last frame.
	/*!
	* This variable stores the time that has been passed since the last time
	* the animation rendered a frame. If this hits a limit, the animation
	* should render again.
	*/
	sf::Time m_elap_time;

	//! Font used for all text inside the window.
	sf::Font m_font;
	//! Path to the font used in this class.
	std::string m_fontname;

	//! Text displaying the current time.
	text m_time_text;
	//! Text displaying the current date.
	text m_date_text;

	//! Input field for the user.
	Textfield m_textfield ;

	void obj_pos();
	void render();

public :

	Orion(sf::VideoMode mode , const sf::String& title , sf::Uint32 style = sf::Style::Default ,
			const sf::ContextSettings& settings = sf::ContextSettings ());
	~Orion();

	bool win_icon(const std::string& filename);

	void proc_events();
	void draw_obj() ;
	void run();

} ;

#endif
