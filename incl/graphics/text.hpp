////////////////////////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2013 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the 
// use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it 
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////////////////////////

// This file has been modified by LIN for WymonOrion.

#ifndef TEXT_HPP
#define TEXT_HPP

#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/String.hpp>
#include <string>
#include <vector>
#include <memory>

//! Type to handle shared fonts.
/*!
* This type is used to deal with shared fonts and delete them once they are no
* longer needed. It uses the std::shared_ptr ability to count the number of
* uses with use_count().
*/
typedef std::shared_ptr<sf::Font> font_ptr;

//! Type to handle constant shared fonts.
/*!
* This type is used with shared fonts, which are not allowed to be modified and
* thus have to be constant. Works like font_ptr.
*/
typedef std::shared_ptr<const sf::Font> const_font_ptr;

//! Class to draw text onto the screen.
/*!
* This class is used to draw string content, thus characters, onto the screen.
* It offers different options to mutate the way the characters are drawn on the
* screen, such as fonts.
*/
class text : public sf::Drawable, public sf::Transformable {

public:

    // Member types.

    //! Enumeration of the text drawing styles.
    enum style {

	//! Regular characters, no style.
        reg    = 0, 
	//! bold characters.
        bold       = 1 << 0,
	//! Italic characters.
        italic     = 1 << 1,
	//! Underlined characters.
        underline = 1 << 2

    };

    // Member functions.

    text();
    text(const sf::String& str, const sf::Font& font,
	const sf::Color& color = sf::Color::Black, unsigned int char_size = 30);
	text(const text& other);
    ~text();

    void str(const sf::String& str);
    void font(const sf::Font& font);
    void font_ptr(const_font_ptr font);
    void char_size(unsigned int size);
    void style(sf::Uint32 styl);
    void color(const sf::Color& clr);

    const sf::String& str() const;
    const sf::Font* font() const;
    const_font_ptr font_ptr() const;
    unsigned int char_size() const;
    sf::Uint32 style() const;
    const sf::Color& color() const;

    sf::Vector2f find_char_pos(std::size_t index) const;

	sf::Vector2f obj_size() const;
    sf::Vector2f size() const;
    sf::FloatRect loc_bound() const;
    sf::FloatRect glob_bound() const;

private :

    // Member functions.

    virtual void draw(sf::RenderTarget& targt, sf::RenderStates stat) const;

    void updt_geom();

    // Member variables.

    //! String to display.
    sf::String m_str;
    //! Font used to display the string.
    const_font_ptr m_font;
    //! Base size of characters in pixel.
    unsigned int m_char_size;
    //! Text style, see style enum. 
    sf::Uint32 m_style;
    //! Text color.
    sf::Color m_color;
    //! Vertex array containing the text's geometry.
    sf::VertexArray m_vertices;
    //! Bounding rectangle of the text (in local coordinates).
    sf::FloatRect m_bound;

};

#endif // TEXT_HPP
