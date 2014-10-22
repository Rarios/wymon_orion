////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <cassert>
#include "text.hpp"

// Member functions.

//! Default constructor.
/*!
* Creates an empty text.
*/
text::text() : m_str(), m_font(nullptr), m_char_size(30), m_style(reg),
m_color(sf::Color::Black), m_vertices(sf::Quads), m_bound() {
}

//! Text member constructor.
/*!
* Constructs the text object with a string, a font and a character size.
* \param string String holding characters which are drawn on the screen.
* \param font Font which is used to draw the string.
* \param color Color used to draw the string.
* \param char_size Character size for drawing, in pixel.
*/
text::text(const sf::String& str, const sf::Font& font, const sf::Color& color,
		   unsigned int char_size) :
m_str(str), m_font(&font), m_char_size(char_size), 
m_style(reg), m_color(color), m_vertices(sf::Quads), m_bound() {

    updt_geom();

}

//! Text copy constructor.
/*!
* Constructs the text object from another one.
* \param other Other text object from which this one is constructed.
*/
text::text(const text& other) : m_str(other.str()), m_font(other.font()),
m_char_size(other.char_size()), m_style(other.style()), m_color(other.color()),
m_vertices(sf::Quads), m_bound() {
}

//! Default destructor.
text::~text() {
}

//! Set internal string.
/*!
* Set a new string which holds data to be displayed on the screen.
* \param str New string to be displayed.
*/
void text::str(const sf::String& str) {

    m_str = str;
    updt_geom();

}


//! Set font.
/*!
* Sets the font for drawing the text to the given font. Note that the fibt must
* exist as long as the text uses it, because the text instance does not save a
* copy of the font, just a pointer to it. If the text tries to access a font
* that does not exist anymore, the behaviour is undefined.
* \param font New font which is used for drawing.
*/
void text::font(const sf::Font& font) {

    if (m_font.get() != &font) {

        m_font = std::make_shared<const sf::Font>(font);
        updt_geom();

    }

}

//! Set reference counted font.
/*!
* This function sets the interally used font pointer to the shared and
* reference counted font. This is the recommended method of giving a text a new
* font, because it enables the font repository to keep track of used and
* unused fonts and deletes them if necessary.
* \param font New reference counted font.
*/
void text::font_ptr(const_font_ptr font) {

    m_font = font;

}

//! Set the character size.
/*!
* Sets a new character size for the text. The default character size is 30, in 
* pixel.
* \param size New character size, in pixel.
*/
void text::char_size(unsigned int size) {

    if (m_char_size != size) {

        m_char_size = size;
        updt_geom();

    }

}

//! Set the text's style.
/*!
* Set a new text style. You can also pass different cominations of styles, such
* as text::bold | text::italic. The default style is text::regular.
* \param style New text style.
*/
void text::style(sf::Uint32 styl) {

    if (m_style != styl) {
        m_style = styl;
        updt_geom();
    }

}

//! Set the text's color.
/*!
* Set a new color for the text. By default, the text color is opaque white.
* \param color New text color.
*/
void text::color(const sf::Color& clr) {

    if (clr != m_color) {
        m_color = clr;
        for (unsigned int i = 0; i < m_vertices.getVertexCount(); ++i)
            m_vertices[i].color = m_color;
    }
    
}

//! Get internal string.
/*!
* Get the internal string holding the displayed data.
* \return Internal string.
*/
const sf::String& text::str() const {

    return m_str;

}

//! Get text's font.
/*!
* This function returns a plain pointer to the font the text is using. Since
* the returned pointer is const, you cannot modify a font you get from this
* function. If there is not font currently in use by the text, a NULL pointer
* is returned.
* \return Plain pointer to the text's font.
*/
const sf::Font* text::font() const {

    return m_font.get();

}

//! Get reference counted font.
/*!
* Get the internal reference counted pointer to the used font.
* \return Reference counted font.
*/
const_font_ptr text::font_ptr() const {

    return m_font;

}

//! Get character size.
/*!
* Get the character size currently in use by the text.
* \return Current character size.
*/
unsigned int text::char_size() const {

    return m_char_size;

}

//! Get the text's style.
/*!
* Get the style currently in use by the texture.
* \return Current text style.
*/
sf::Uint32 text::style() const {
	
    return m_style;

}

//! Get global color of the text.
/*!
* Get the color currently in use by the text.
* \return Current text color.
*/
const sf::Color& text::color() const {

    return m_color;

}

//! Return position of index-th character.
/*!
* This function computes the visual position of the character at position
* index. The returned position is in global coordinates, so transformations,
* rotations and the like are applied. If index is out of range, the position of
* the last character in the string is returned.
* \param index Index of character for which to compute.
* \return Visual position of index-th character.
*/
sf::Vector2f text::find_char_pos(std::size_t index) const {

    // Make sure that we have a valid font.
    if (m_font) {

        return sf::Vector2f();

    }

    // Adjust the index if it's out of range.
    if (index > m_str.getSize()) {

        index = m_str.getSize();

    }

    // Precompute the variables needed by the algorithm.
    bool bold = (m_style & bold) != 0;
    float h_space = static_cast<float>(m_font->getGlyph(L' ', m_char_size, bold).advance);
    float v_space = static_cast<float>(m_font->getLineSpacing(m_char_size));

    // Compute the position.
    sf::Vector2f pos;
    sf::Uint32 prev_char = 0;
    for (std::size_t i = 0; i < index; ++i) {

	sf::Uint32 cur_char = m_str[i];

        // Apply the kerning offset.
        pos.x += static_cast<float>(m_font->getKerning(prev_char, cur_char, m_char_size));
        prev_char = cur_char;

        // Handle special characters.
        switch (cur_char) {

            case ' ' :  pos.x += h_space; continue;
            case '\t' : pos.x += h_space * 4; continue;
            case '\n' : pos.y += v_space; pos.x = 0; continue;
            case '\v' : pos.y += v_space * 4; continue;

        }

        // For regular characters, add the advance offset of the glyph.
        pos.x += static_cast<float>(m_font->getGlyph(cur_char, m_char_size, bold).advance);

    }

    // Transform the position to global coordinates.
    pos = getTransform().transformPoint(pos);

    return pos;

}

//! Get local size of the object.
/*!
* Get the local size of the text. This is a convenience function for
* loc_bound().
* \return Visual size of text.
*/
sf::Vector2f text::obj_size() const {

    // Bounds of text without transformations.
    auto bound = loc_bound();

    return sf::Vector2f(bound.width, bound.height);

}

//! Get global size of the object.
/*!
* This returns the global size of the text. It is a conveniece function for
* glob_bound(), so that only the size can be requested.
* \return global size of the object
*/
sf::Vector2f text::size() const {

    // Bounds of text with transformations.
    auto bound = glob_bound();

    return sf::Vector2f(bound.width, bound.height);

}

//! Get local bounding rectangle of the object.
/*!
* This returns the bounds of the entity in local coordinates, thus ignoring all
* transformations, rotations and the like.
* \return Local bounding rectangle of the object.
*/
sf::FloatRect text::loc_bound() const {

    return m_bound;

}

//! Get the global bounding rectangle of the object.
/*!
* This returns the bounds of the entity in global coordinates, thus taking all
* transformations, rotations and the like into account. It is basically the
* bounding of the object in the 2D world's coordinate system.
* \return Global bounding rectangle of the object.
*/
sf::FloatRect text::glob_bound() const {

    return getTransform().transformRect(loc_bound());

}

//! Draw the text.
/*!
* Draws the text to a render target.
* \param target Render target to draw to.
* \param states Current render states used while drawing.
*/
void text::draw(sf::RenderTarget& targt, sf::RenderStates stat) const {

    if (m_font) {

        stat.transform *= getTransform();
        stat.texture = &(m_font->getTexture(m_char_size));
        targt.draw(m_vertices, stat);

    }

}

//! Update the text's geometry.
// \todo Update this function for coding conventions.
void text::updt_geom() {

    // Clear the previous geometry.
    m_vertices.clear();
    m_bound = sf::FloatRect();

    // No font: nothing to draw.
    if (!m_font) {

        return;
    }

    // No text: nothing to draw.
    if (m_str.isEmpty())
        return;

    // Compute values related to the text style.
    bool bold = (m_style & bold) != 0;
    // Underline.
    bool unln = (m_style & underline) != 0;
    // Italic.
    float ital = (m_style & italic) ? 0.208f : 0.f; // 12 degrees.
    // Underline offset.
    float unln_offst= m_char_size * 0.1f;
    // Underline thickness.
    float unln_thick = m_char_size * (bold ? 0.1f : 0.07f);

    // Precompute the variables needed by the algorithm.
    float h_space = static_cast<float>(m_font->getGlyph(L' ', m_char_size, bold).advance);
    float v_space = static_cast<float>(m_font->getLineSpacing(m_char_size));
    float x = 0.f;
    float y = static_cast<float>(m_char_size);

    // Create one quad for each character.
    float min_x = static_cast<float>(m_char_size);
    float min_y = static_cast<float>(m_char_size);
    float max_x = 0.f;
    float max_y = 0.f;
    sf::Uint32 prev_char = 0;
    for (std::size_t i = 0; i < m_str.getSize(); ++i) {

        sf::Uint32 cur_char = m_str[i];

        // Apply the kerning offset.
        x += static_cast<float>(m_font->getKerning(prev_char, cur_char, m_char_size));
        prev_char = cur_char;

        // If we're using the underlined style and there's a new line, draw a line.
        if (underline && (cur_char == L'\n')) {

            float top = y + unln_offst;
            float bot = top + unln_thick;

            m_vertices.append(sf::Vertex(sf::Vector2f(0, top), m_color, sf::Vector2f(1, 1)));
            m_vertices.append(sf::Vertex(sf::Vector2f(x, top), m_color, sf::Vector2f(1, 1)));
            m_vertices.append(sf::Vertex(sf::Vector2f(x, bot), m_color, sf::Vector2f(1, 1)));
            m_vertices.append(sf::Vertex(sf::Vector2f(0, bot), m_color, sf::Vector2f(1, 1)));

        }

        // Handle special characters.
        if ((cur_char == ' ') || (cur_char == '\t') || (cur_char == '\n') || (cur_char == '\v')) {

            // Update the current bounds (min coordinates).
            min_x = std::min(min_x, x);
            min_y = std::min(min_y, y);

            switch (cur_char) {

                case ' ' :  x += h_space; break;
                case '\t' : x += h_space * 4; break;
                case '\n' : y += v_space; x = 0; break;
                case '\v' : y += v_space * 4; break;

            }

            // Update the current bounds (max coordinates).
            max_x = std::max(max_x, x);
            max_y = std::max(max_y, y);

            // Next glyph, no need to create a quad for whitespace.
            continue;

        }

        // Extract the current glyph's description.
        const sf::Glyph& glyph = m_font->getGlyph(cur_char, m_char_size, bold);

        int left = glyph.bounds.left;
        int top = glyph.bounds.top;
        int right = glyph.bounds.left + glyph.bounds.width;
        int bot = glyph.bounds.top  + glyph.bounds.height;

        float u1 = static_cast<float>(glyph.textureRect.left);
        float v1 = static_cast<float>(glyph.textureRect.top);
        float u2 = static_cast<float>(glyph.textureRect.left + glyph.textureRect.width);
        float v2 = static_cast<float>(glyph.textureRect.top  + glyph.textureRect.height);

        // Add a quad for the current character.
        m_vertices.append(sf::Vertex(sf::Vector2f(x + left  - ital * top,    y + top),    m_color, sf::Vector2f(u1, v1)));
        m_vertices.append(sf::Vertex(sf::Vector2f(x + right - ital * top,    y + top),    m_color, sf::Vector2f(u2, v1)));
        m_vertices.append(sf::Vertex(sf::Vector2f(x + right - ital * bot, y + bot), m_color, sf::Vector2f(u2, v2)));
        m_vertices.append(sf::Vertex(sf::Vector2f(x + left  - ital * bot, y + bot), m_color, sf::Vector2f(u1, v2)));

        // Update the current bounds.
        min_x = std::min(min_x, x + left - ital * bot);
        max_x = std::max(max_x, x + right - ital * top);
        min_y = std::min(min_y, y + top);
        max_y = std::max(max_y, y + bot);

        // Advance to the next character.
        x += glyph.advance;

    }

    // If we're using the underlined style, add the last line.
    if (unln) {

        float top = y + unln_offst;
        float bot = top + unln_thick;

        m_vertices.append(sf::Vertex(sf::Vector2f(0, top), m_color, sf::Vector2f(1, 1)));
        m_vertices.append(sf::Vertex(sf::Vector2f(x, top), m_color, sf::Vector2f(1, 1)));
        m_vertices.append(sf::Vertex(sf::Vector2f(x, bot), m_color, sf::Vector2f(1, 1)));
        m_vertices.append(sf::Vertex(sf::Vector2f(0, bot), m_color, sf::Vector2f(1, 1)));

    }

    // Update the bounding rectangle.
    m_bound.left = min_x;
    m_bound.top = min_y;
    m_bound.width = max_x - min_x;
    m_bound.height = max_y - min_y;

}
