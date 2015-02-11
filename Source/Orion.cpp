// Orion.cpp

#include "Orion.hpp"
#include <iostream>

//! Value constructor.
/*!
* Construct Orion class instance from given values.
* \param mode Video mode that should be used.
* \param title Window title.
* \param style Style the window should have.
* \param settings Context settings for the window.
*/
Orion::Orion(sf::VideoMode mode, const sf::String& title , sf::Uint32 style ,
			 const sf::ContextSettings& settings) : 
m_win(mode, title, style, settings), m_win_icon(), m_time_str(), m_background(),
m_wymon(), m_clock(), m_elap_time(), m_font(), m_time_text(), m_date_text(), 
m_textfield(&m_font) {
}

//! Default destructor.
Orion::~Orion() {
}

//! Set window icon.
/*!
* Loads the the (normal graphic) from the file specified by the parameter and
* sets it as the window's icon. Note that only 16x16 and 32x32 icons are
* allowed. The size will not be checked, wrong size will lead to undefined
* behaviour.
* \param filename Name of the graphic that should be the window's icon.
* \return True if icon could be set.
*/
bool Orion::win_icon(const std::string& filename) {
	
	if (!m_win_icon.loadFromFile(filename)) {
	
		std::cerr << "Could not load icon: " << filename;
		return false;
	
	}
	
	auto icon_size = m_win_icon.getSize();
	m_win.setIcon(icon_size.x, icon_size.y, m_win_icon.getPixelsPtr());

	return true;
	
}

//! Set the position of the objects.
/*!
* Set the position of all graphical objects on the screen.
*/
void Orion::obj_pos() {

	// Size variables for calculations.
	// Size of the render region of the window (excluding borders, etc.)
	sf::Vector2u render_size = m_win.getSize();
	sf::Vector2f wymon_size = m_wymon.getMaximumObjectSize();
	sf::Vector2f time_size = m_time_text.getSize();
	sf::Vector2f date_size = m_date_text.getSize();
	sf::Vector2f textfield_size = m_textfield.size();

	float a = 20.0f ;
	float b = static_cast<float>(render_size.y) / 10.0f ;

	// Variables for the positions, calculated later.
	sf::Vector2f wymon_pos;
	sf::Vector2f time_pos;
	sf::Vector2f date_pos;
	sf::Vector2f textfield_pos;

	// Calculate the positions for the objects.
	// Wymon, using the "Center rule".
	wymon_pos.x = static_cast<float>(render_size.x / 2 - (wymon_size.x + a + 
				 ((time_size.x > date_size.x) ? time_size.x : date_size.x))/ 2);
	wymon_pos.y = b;

	// Time, using the "Center rule".
	time_pos.x = wymon_pos.x + wymon_size.x + a ;
	time_pos.y = wymon_pos.y + (wymon_size.y / 2 - time_size.y / 2);

	// Date.
	date_pos.x = time_pos.x;
	date_pos.y = time_pos.y + time_size.y + date_size.y;

	// Textfield.
	textfield_pos.x = render_size.x / 2 - textfield_size.x / 2 ;
	textfield_pos.y = render_size.y - textfield_size.y - border - margin;

	// Set all positions.
	m_wymon.setPosition(wymon_pos);
	m_time_text.setPosition(time_pos);
	m_date_text.setPosition(date_pos);
	m_textfield.pos(textfield_pos);

}

//! Render all objects.
/*!
* Updates and renders all objects that change with time.
*/
void Orion::render() {

	if(m_time_str.time_str(Time_string::TIME) != m_time_text.getString()) {

		// Update time text object.
		m_time_text.setString(m_time_str.time_str(Time_string::TIME));

		// Only update the date if time
		// is equal to 00:00:00.
		if (m_time_text.getString() == Time_string::NEW_DATE) { /* WORKS !!!!! */
			
			m_date_text.setString(m_time_str.time_str(Time_string::DATE));
			
		}

	}

	// Animate m_wymon animation.
	// Update elapsed time and check if limit is reached. If yes, render frame
	// and restart the clock.
	m_elap_time = m_clock.getElapsedTime();
	if (850.f <= m_elap_time.asMilliseconds()) {
	
		m_wymon.render();
		m_clock.restart();
	
	}

	draw_obj();

}

//! Process all pending events.
/*!
* Polls and processes all pending events, basically holds the event loop.
*/
void Orion::proc_events() {

	sf::Event event;
	while (m_win.pollEvent(event)) {
		
		switch(event.type) {
			
			case sf::Event::TextEntered : 
					
				m_textfield.put_char(event.text.unicode);

			break;

			case sf::Event::Resized : {

				// Reset the view of the window to the new size.
				m_win.setView(sf::View(sf::FloatRect(0.f, 0.f,
							  static_cast<float>(m_win.getSize().x), 
							  static_cast<float>(m_win.getSize().y))));
				// Set the position of the background, so that the window is
				// in the middle of it.
				/*auto max_win_size = sf::VideoMode::getDesktopMode();
				auto win_size = m_win.getSize();
				auto background_size = m_background.size();
				m_background.setOrigin(background_size.x / 2,
									   background_size.y / 2);
				m_background.move(-1 * (max_win_size.width / 2),
								  -1 * (max_win_size.height / 2));*/
				obj_pos();

			} break;

			case sf::Event::Closed : 

				m_win.close();
											
			break;
			
		}
		
	}

}

//! Draw all objects.
/*!
* This function calls the draw function for all members.
*/
void Orion::draw_obj() {

	m_win.clear();

	m_win.draw(m_background);	
	m_win.draw(m_time_text);
	m_win.draw(m_wymon);
	m_win.draw(m_date_text);
	m_win.draw(m_textfield);

	m_win.display();

}

//! Runs the window's main loop.
/*!
* Runs the main and the event loop of the window. Everything that has to happen
* right before or inside these to loops is inside this function. The graphical
* object members are initialized in here.
*/
void Orion::run() {

	// Clear the window in case something is already in there.
	m_win.clear(); 

	// Font.
	if (!m_font.loadFromFile("Resources/NotoSerif-Regular.ttf")) {
	
		std::cerr << "Could not load Noto font\n";
		std::cin.get();
		return;
	
	}

	// Background.
	if (!m_background.loadFromFile("Resources/background.jpg")) {
	
		std::cerr << "Could not load background.jpg\n";
		std::cin.get();
		return;
	
	}
	// Scale background so it fits the maximum desktop size.
	auto max_win_size = sf::VideoMode::getDesktopMode();
	auto background_size = m_background.getObjectSize();
	m_background.setScale(sf::Vector2f(max_win_size.width / background_size.x,
						  max_win_size.height / background_size.y));
	m_win.draw(m_background);

	// Wymon animation.
	if (!m_wymon.loadFromFile("Resources/wymon.png", sf::IntRect(0, 0, 106, 96))) {
	
		std::cerr << "Could not load wymon.png\n";
		std::cin.get();
		return;
	
	}
	m_wymon.insert(wo::gfx::Frame(0, 0, 106, 96));
	m_wymon.insert(wo::gfx::Frame(107, 0, 108, 96));
	m_win.draw(m_wymon);

	// Textfield
	m_textfield.draw_box(sf::Vector2u(m_win.getSize().x , m_win.getSize().y));
	m_win.draw(m_textfield);
	
	// Date.
	m_date_text.setString(m_time_str.time_str(Time_string::DATE));
	m_date_text.setFont(&m_font);
	m_date_text.setCharacterSize(11) ;
	m_win.draw(m_date_text);

	// Time.
	m_time_text.setString(m_time_str.time_str(Time_string::TIME));
	m_time_text.setFont(&m_font);
	m_time_text.setCharacterSize(46) ;
	m_win.draw(m_time_text);

	// First display of all objects.
	m_win.display();

	obj_pos();

	// Initialize the elapsed time variable.
	m_elap_time = m_clock.restart();

	// Main loop.
	while (m_win.isOpen()) {
	
		// Event loop.
		proc_events();
		render();
		
	}

}
