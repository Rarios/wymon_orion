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

#ifndef GRAPHICS_SPRITE
#define GRAPHICS_SPRITE

#ifndef WO_NAMESPACE
	#include "Namespace.hpp"
#endif
#ifndef GRAPHICS_TEXTURABLE
	#include "Texturable.hpp"
#endif

// Only temporarily during integration of conding conventions.
using namespace sf;

OPEN_WO_GFX

//! Drawable representation of a texture, with its own transformations, color, etc.
/*!
* This class has been copied and modified from the original SFML2.1 "Sprite"
* class.
*
* It holds a reference to a "Texture" object, which itself holds
* the data of an image. With this class it is possible to transform the
* representation of the image (how it is drawn), without dealing with the
* texture, a heavy object in terms of data, itself.
*/
class Sprite : public Texturable {

public:

	Sprite(void);
    explicit Sprite(const TexturePointer& texture);
    Sprite(const TexturePointer& texture, const IntRect& rect);
	~Sprite(void);

	void setTextureRect(const IntRect& rect);
	FloatRect getLocalBounds() const;

private:
	
	void updateTextureCoordinates();

	void draw(RenderTarget& target,
              RenderStates states = RenderStates::Default) const;

};

CLOSE_WO_GFX

#endif
