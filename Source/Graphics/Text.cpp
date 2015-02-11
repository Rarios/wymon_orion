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

#include <cassert>
#include <iostream>
#include <Graphics/Texture.hpp>
#include <Graphics/RenderTarget.hpp>
#include "Text.hpp"

OPEN_WO_GFX

// Member functions.

//! Custom deleter for font pointers.
/*! 
* This function first test whether or not the font pointer is valid. If it is,
* it deletes the pointer. If not it returns without doing anything.
*
* NOTE: There has been some strange error with the "free()" function involved
* with the fonts. The solution to this error was to create this custom deleter
* function. This might not be the best way, so this problem should be review
* later on again. 
* \param fontPtr Raw font pointer to delete.
*/

void deleteFontPointer(const Font* fontPtr) {

	//std::cout << "Calling the font pointer deleter function." << std::endl;

	if (fontPtr) {
	
		//std::cout << "Font pointer is already nullptr." << std::endl;
		return;
	
	}

	delete fontPtr;
	//std::cout << "Deleted the font pointer." << std::endl;

}

//! Default constructor.
/*!
* Creates an empty text.
*/
Text::Text() : mString(), mFont(nullptr, &deleteFontPointer), 
mCharacterSize(30), mStyle(REGULAR), mColor(Color::Black), mVertices(Quads),
mBounds() {

	updateGeometry();

}

//! Text member constructor.
/*!
* Constructs the text object with a string, a font and a character size.
* \param string String holding characters which are drawn on the screen.
* \param font Font which is used to draw the string.
* \param color Color used to draw the string.
* \param characterSize Character size for drawing, in pixel.
*/
Text::Text(const String& string, const Font* font, const Color& color,
		   unsigned int characterSize) :
mString(string), mFont(font, &deleteFontPointer), mCharacterSize(characterSize), 
mStyle(REGULAR), mColor(color), mVertices(Quads), mBounds() {

    updateGeometry();

}

//! Text copy constructor.
/*!
* Constructs the text object from another one.
* \param other Other text object from which this one is constructed.
*/
Text::Text(const Text& other) : mString(other.getString()), 
mFont(other.getFont(), &deleteFontPointer), 
mCharacterSize(other.getCharacterSize()), mStyle(other.getStyle()),
mColor(other.getColor()), mVertices(Quads), mBounds() {
		
	updateGeometry();

}

//! Default destructor.
Text::~Text() {
}

//! Set internal string.
/*!
* Set a new string which holds data to be displayed on the screen.
* \param string New string to be displayed.
*/
void Text::setString(const String& string) {

    mString = string;
    updateGeometry();

}


//! Set font.
/*!
* Sets the font for drawing the text to the given font. Note that the fibt must
* exist as long as the text uses it, because the text instance does not save a
* copy of the font, just a pointer to it. If the text tries to access a font
* that does not exist anymore, the behaviour is undefined.
* \param font New font which is used for drawing.
*/
void Text::setFont(const Font* font) {

    if (mFont.get() != font) {

        mFont.reset(font, &deleteFontPointer);
        updateGeometry();

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
void Text::setFontPointer(ConstFontPointer font) {

    mFont = font;

}

//! Set the character size.
/*!
* Sets a new character size for the text. The default character size is 30, in 
* pixel.
* \param size New character size, in pixel.
*/
void Text::setCharacterSize(unsigned int size) {

    if (mCharacterSize != size) {

        mCharacterSize = size;
        updateGeometry();

    }

}

//! Set the text's style.
/*!
* Set a new text style. You can also pass different cominations of styles, such
* as Text::bold | Text::italic. The default style is Text::regular.
* \param style New text style.
*/
void Text::setStyle(Uint32 style) {

    if (mStyle != style) {
        mStyle = style;
        updateGeometry();
    }

}

//! Set the text's color.
/*!
* Set a new color for the text. By default, the text color is opaque white.
* \param color New text color.
*/
void Text::setColor(const Color& color) {

    if (color != mColor) {
        mColor = color;
        for (unsigned int i = 0; i < mVertices.getVertexCount(); ++i)
            mVertices[i].color = mColor;
    }
    
}

//! Get internal string.
/*!
* Get the internal string holding the displayed data.
* \return Internal string.
*/
const String& Text::getString() const {

    return mString;

}

//! Get text's font.
/*!
* This function returns a plain pointer to the font the text is using. Since
* the returned pointer is const, you cannot modify a font you get from this
* function. If there is not font currently in use by the text, a NULL pointer
* is returned.
* \return Plain pointer to the text's font.
*/
const Font* Text::getFont() const {

    return mFont.get();

}

//! Get reference counted font.
/*!
* Get the internal reference counted pointer to the used font.
* \return Reference counted font.
*/
ConstFontPointer Text::getFontPointer() const {

    return mFont;

}

//! Get character size.
/*!
* Get the character size currently in use by the text.
* \return Current character size.
*/
unsigned int Text::getCharacterSize() const {

    return mCharacterSize;

}

//! Get the text's style.
/*!
* Get the style currently in use by the texture.
* \return Current text style.
*/
Uint32 Text::getStyle() const {
	
    return mStyle;

}

//! Get global color of the text.
/*!
* Get the color currently in use by the text.
* \return Current text color.
*/
const Color& Text::getColor() const {

    return mColor;

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
Vector2f Text::findCharacterPosition(std::size_t index) const {

    // Make sure that we have a valid font.
    if (mFont) {

        return Vector2f();

    }

    // Adjust the index if it's out of range.
    if (index > mString.getSize()) {

        index = mString.getSize();

    }

    // Precompute the variables needed by the algorithm.
    bool bold = (mStyle & this->BOLD) != 0;
    float hSpace = static_cast<float>(mFont->getGlyph(L' ', mCharacterSize, bold).advance);
    float vSpace = static_cast<float>(mFont->getLineSpacing(mCharacterSize));

    // Compute the position.
    Vector2f position;
    Uint32 previousCharacter = 0;
    for (std::size_t i = 0; i < index; ++i) {

		Uint32 currentCharacter = mString[i];

        // Apply the kerning offset.
        position.x += static_cast<float>(mFont->getKerning(previousCharacter, currentCharacter, mCharacterSize));
        previousCharacter = currentCharacter;

        // Handle special characters.
        switch (currentCharacter) {

            case ' ' :  position.x += hSpace; continue;
            case '\t' : position.x += hSpace * 4; continue;
            case '\n' : position.y += vSpace; position.x = 0; continue;
            case '\v' : position.y += vSpace * 4; continue;

        }

        // For regular characters, add the advance offset of the glyph.
        position.x += static_cast<float>(mFont->getGlyph(currentCharacter, mCharacterSize, bold).advance);

    }

    // Transform the position to global coordinates.
    position = getTransform().transformPoint(position);

    return position;

}

//! Get local size of the object.
/*!
* Get the local size of the text. This is a convenience function for
* getLocalBounds().
* \return Visual size of text.
*/
Vector2f Text::getObjectSize() const {

    // Bounds of text without transformations.
    auto bound = getLocalBounds();

    return Vector2f(bound.width, bound.height);

}

//! Get global size of the object.
/*!
* This returns the global size of the text. It is a conveniece function for
* getGlobalBounds(), so that only the size can be requested.
* \return global size of the object
*/
Vector2f Text::getSize() const {

    // Bounds of text with transformations.
    auto bound = getGlobalBounds();

    return Vector2f(bound.width, bound.height);

}

//! Get local bounding rectangle of the object.
/*!
* This returns the bounds of the entity in local coordinates, thus ignoring all
* transformations, rotations and the like.
* \return Local bounding rectangle of the object.
*/
FloatRect Text::getLocalBounds() const {
	
    return mBounds;

}

//! Get the global bounding rectangle of the object.
/*!
* This returns the bounds of the entity in global coordinates, thus taking all
* transformations, rotations and the like into account. It is basically the
* bounding of the object in the 2D world's coordinate system.
* \return Global bounding rectangle of the object.
*/
FloatRect Text::getGlobalBounds() const {

    return getTransform().transformRect(getLocalBounds());

}

//! Draw the text.
/*!
* Draws the text to a render target.
* \param target Render target to draw to.
* \param states Current render states used while drawing.
*/
void Text::draw(RenderTarget& target, RenderStates states) const {

    if (nullptr != mFont) {

        states.transform *= getTransform();
        states.texture = &mFont->getTexture(mCharacterSize);
        target.draw(mVertices, states);

    }

}

//! Update the text's geometry.
// \todo Update this function for coding conventions.
void Text::updateGeometry() {

    // Clear the previous geometry.
    mVertices.clear();
    mBounds = FloatRect();

    // No font: nothing to draw.
    if (!mFont) {
        return;
    }

    // No text: nothing to draw.
    if (mString.isEmpty()) {
        return;
	}

    // Compute values related to the text style.
    bool bold = (mStyle & this->BOLD) != 0;
    // Underline.
    bool underline = (mStyle & UNDERLINED) != 0;
    // Italic.
    float italic = (mStyle & ITALIC) ? 0.208f : 0.f; // 12 degrees.
    // Underline offset.
    float underlineOffset = mCharacterSize * 0.1f;
    // Underline thickness.
    float underlineThickness = mCharacterSize * (bold ? 0.1f : 0.07f);

    // Precompute the variables needed by the algorithm.
    float hSpace = static_cast<float>(mFont->getGlyph(L' ', mCharacterSize, bold).advance);
    float vSpace = static_cast<float>(mFont->getLineSpacing(mCharacterSize));
    float x = 0.f;
    float y = static_cast<float>(mCharacterSize);

    // Create one quad for each character.
    float minX = static_cast<float>(mCharacterSize);
    float minY = static_cast<float>(mCharacterSize);
    float maxX = 0.f;
    float maxY = 0.f;
    Uint32 previousCharacter = 0;
    for (std::size_t i = 0; i < mString.getSize(); ++i) {

        Uint32 currentCharacter = mString[i];

        // Apply the kerning offset.
        x += static_cast<float>(mFont->getKerning(previousCharacter, currentCharacter, mCharacterSize));
        previousCharacter = currentCharacter;

        // If we're using the underlined style and there's a new line, draw a line.
        if (underline && (currentCharacter == L'\n')) {

            float top = y + underlineOffset;
            float bottom = top + underlineThickness;

            mVertices.append(Vertex(Vector2f(0, top), mColor, Vector2f(1, 1)));
            mVertices.append(Vertex(Vector2f(x, top), mColor, Vector2f(1, 1)));
            mVertices.append(Vertex(Vector2f(x, bottom), mColor, Vector2f(1, 1)));
            mVertices.append(Vertex(Vector2f(0, bottom), mColor, Vector2f(1, 1)));

        }

        // Handle special characters.
        if ((currentCharacter == ' ') || (currentCharacter == '\t') || (currentCharacter == '\n') || (currentCharacter == '\v')) {

            // Update the current bounds (min coordinates).
            minX = std::min(minX, x);
            minY = std::min(minY, y);

            switch (currentCharacter) {

                case ' ' :  x += hSpace; break;
                case '\t' : x += hSpace * 4; break;
                case '\n' : y += vSpace; x = 0; break;
                case '\v' : y += vSpace * 4; break;

            }

            // Update the current bounds (max coordinates).
            maxX = std::max(maxX, x);
            maxY = std::max(maxY, y);

            // Next glyph, no need to create a quad for whitespace.
            continue;

        }

        // Extract the current glyph's description.
        const Glyph& glyph = mFont->getGlyph(currentCharacter, mCharacterSize, bold);

        int left = glyph.bounds.left;
        int top = glyph.bounds.top;
        int right = glyph.bounds.left + glyph.bounds.width;
        int bottom = glyph.bounds.top  + glyph.bounds.height;

        float u1 = static_cast<float>(glyph.textureRect.left);
        float v1 = static_cast<float>(glyph.textureRect.top);
        float u2 = static_cast<float>(glyph.textureRect.left + glyph.textureRect.width);
        float v2 = static_cast<float>(glyph.textureRect.top  + glyph.textureRect.height);

        // Add a quad for the current character.
        mVertices.append(Vertex(Vector2f(x + left  - italic * top,    y + top),    mColor, Vector2f(u1, v1)));
        mVertices.append(Vertex(Vector2f(x + right - italic * top,    y + top),    mColor, Vector2f(u2, v1)));
        mVertices.append(Vertex(Vector2f(x + right - italic * bottom, y + bottom), mColor, Vector2f(u2, v2)));
        mVertices.append(Vertex(Vector2f(x + left  - italic * bottom, y + bottom), mColor, Vector2f(u1, v2)));

        // Update the current bounds.
        minX = std::min(minX, x + left - italic * bottom);
        maxX = std::max(maxX, x + right - italic * top);
        minY = std::min(minY, y + top);
        maxY = std::max(maxY, y + bottom);

        // Advance to the next character.
        x += glyph.advance;

    }

    // If we're using the underlined style, add the last line.
    if (underline) {

        float top = y + underlineOffset;
        float bottom = top + underlineThickness;

        mVertices.append(Vertex(Vector2f(0, top), mColor, Vector2f(1, 1)));
        mVertices.append(Vertex(Vector2f(x, top), mColor, Vector2f(1, 1)));
        mVertices.append(Vertex(Vector2f(x, bottom), mColor, Vector2f(1, 1)));
        mVertices.append(Vertex(Vector2f(0, bottom), mColor, Vector2f(1, 1)));

    }

    // Update the bounding rectangle.
    m_bound.left = minX;
    m_bound.top = minY;
    m_bound.width = maxX - minX;
    m_bound.height = maxY - minY;

}

CLOSE_WO_GFX
