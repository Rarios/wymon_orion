// Orion
// Orion.hpp

//#define NDEBUG
#ifndef _ORION_
#define _ORION_

#include <iostream>
#ifndef SFML_GRAPHICS_HPP
#include <SFML/Graphics.hpp>
#endif
#ifndef GRAPHICS_SPRITE
#include "Sprite.hpp"
#endif
#ifndef GRAPHICS_TEXT
#include "Text.hpp"
#endif
#ifndef _TEXTFIELD_
#include "Textfield.hpp"
#endif
#ifndef GRAPHICS_ANIMATION
#include "Animation.hpp"
#endif
#ifndef _Time_string_
#include "Time_string.hpp"
#endif

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
	wo::gfx::Sprite m_background;

	//! Wymon animation.
	wo::gfx::Animation m_wymon;
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
	wo::gfx::Text m_time_text;
	//! Text displaying the current date.
	wo::gfx::Text m_date_text;

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
