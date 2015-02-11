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

#ifndef GRAPHICS_TEXT
#define GRAPHICS_TEXT

#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/String.hpp>
#ifndef WO_NAMESPACE
	#include "Namespace.hpp"
#endif

// Only temporarily during integration of conding conventions.
using namespace sf;

OPEN_WO_GFX

//! Type to handle shared fonts.
/*!
* This type is used to deal with shared fonts and delete them once they are no
* longer needed. It uses the std::shared_ptr ability to count the number of
* uses with use_count().
*/
typedef std::shared_ptr<Font> FontPointer;

//! Type to handle constant shared fonts.
/*!
* This type is used with shared fonts, which are not allowed to be modified and
* thus have to be constant. Works like FontPointer.
*/
typedef std::shared_ptr<const Font> ConstFontPointer;

//! Class to draw text onto the screen.
/*!
* This class is used to draw string content, thus characters, onto the screen.
* It offers different options to mutate the way the characters are drawn on the
* screen, such as fonts.
*/
class Text : public Drawable, public Transformable {

public:

    // Member types.

    //! Enumeration of the text drawing styles.
    enum Style {

	//! Regular characters, no style.
        REGULAR = 0, 
	//! bold characters.
        BOLD = 1 << 0,
	//! Italic characters.
        ITALIC = 1 << 1,
	//! Underlined characters.
        UNDERLINED = 1 << 2

    };

    // Member functions.

    Text();
    Text(const String& string, const Font* font,
		 const Color& color = Color::Black, unsigned int characterSize = 30);
	Text(const Text& other);
    ~Text();

    void setString(const String& string);
    void setFont(const Font* font);
    void setFontPointer(ConstFontPointer font);
    void setCharacterSize(unsigned int size);
    void setStyle(Uint32 style);
    void setColor(const Color& color);

    const String& getString() const;
    const Font* getFont() const;
    ConstFontPointer getFontPointer() const;
    unsigned int getCharacterSize() const;
    Uint32 getStyle() const;
    const Color& getColor() const;

    Vector2f findCharacterPosition(std::size_t index) const;

	Vector2f getObjectSize() const;
    Vector2f getSize() const;
    FloatRect getLocalBounds() const;
    FloatRect getGlobalBounds() const;

private :

    // Member functions.

    virtual void draw(RenderTarget& target, RenderStates states) const;

    void updateGeometry();

    // Member variables.

    //! String to display.
    String mString;
    //! Font used to display the string.
    ConstFontPointer mFont;
    //! Base size of characters in pixel.
    unsigned int mCharacterSize;
    //! Text style, see style enum. 
    Uint32 mStyle;
    //! Text color.
    Color mColor;
    //! Vertex array containing the text's geometry.
    VertexArray mVertices;
    //! Bounding rectangle of the text (in local coordinates).
    FloatRect mBounds;

};

CLOSE_WO_GFX

#endif // GRAPHICS_TEXT
