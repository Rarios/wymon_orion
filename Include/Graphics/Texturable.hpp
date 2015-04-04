////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2013 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
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

// The code of the "Sprite" class has been copied from the SFML2.1
// and altered in case it was needed.

#ifndef GRAPHICS_TEXTURABLE
#define GRAPHICS_TEXTURABLE

#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Rect.hpp>
#ifndef WO_NAMESPACE
	#include "Namespace.hpp"
#endif
#ifndef GRAPHICS_TEXTUREMANAGER
	#include "TextureManager.hpp"
#endif

// Only temporarily during integration of coding conventions.
using namespace sf;

OPEN_WO_GFX

//! Base class for texture handling.
/*!
* This abstract base class has functions to handle textures
* at the very basic level, like loading a sprite for instance.
* Its purpose is to be inherited and extended, like the Sprite
* class will do.
*/
class Texturable : public Drawable, public Transformable {

public :

	// Member functions.

	virtual ~Texturable(void) {
	}

	void setTexture(const TexturePointer& texture, bool resetRect = false);
	//! Set the render rectangle, which the sprite will display.
	/*!
	* ATTENTION: This is a pure virtual function. The classes
	* inheriting by this one should implement this funtion.
	*/
	virtual void setTextureRect(const IntRect& rect) = 0;
    void setColor(const Color& color);

	const TexturePointer& getTexture() const;
	const IntRect& getTextureRect() const;
    const Color& getColor() const;
	//! Get the local boundaries rectangle.
	/*!
	* ATTENTION: This is a pure virtual function. The classes
	* inheriting by this one should implement this funtion.
	*/
	virtual FloatRect getLocalBounds() const = 0;
	FloatRect getGlobalBounds() const;
	Vector2f getObjectSize() const;
    Vector2f getSize() const;

protected :

	void updatePosition();
	//! Update the vertices' texture coordinates.
	/*!
	* ATTENTION: This is a pure virtual function. The classes
	* inheriting by this one should implement this funtion.
	*/
    virtual void updateTextureCoordinates() = 0;

	void applyDisplayRect(const IntRect& displ_rect);

	//! Draw the sprite to a render target.
	/*!
	* ATTENTION: This is a pure virtual function. The classes
	* inheriting by this one should implement this funtion.
	* \param target Render target to draw to.
	* \param states Current render states.
	*/
	virtual void draw(RenderTarget& target,
                      RenderStates states) const = 0;

	// Member variables.

	//! Vertices defining the sprite's geometry
	/*!
	* The geometry of a sprite is defined by an array of
	* four vertices, which means it is of type "Quads".
	*/
    Vertex mVertices[4];
	//! Pointer to the texture of the sprite.
    TexturePointer mTexture;
	//! Texture rectangle.
	/*!
	* Rectangle defining the area of the source texture to
	* display.
	*/
    IntRect mTextureRect;

};

CLOSE_WO_GFX

#endif // GRAPHICS_TEXTURABLE
