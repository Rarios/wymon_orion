//////////////////////////////////////////////////////////////
////
//// SFML - Simple and Fast Multimedia Library
//// Copyright (C) 2007-2013 Laurent Gomila (laurent.gom@gmail.com)
////
//// This software is provided 'as-is', without any express or implied warranty.
//// In no event will the authors be held liable for any damages arising from the use of this software.
////
//// Permission is granted to anyone to use this software for any purpose,
//// including commercial applications, and to alter it and redistribute it freely,
//// subject to the following restrictions:
////
//// 1. The origin of this software must not be misrepresented;
////    you must not claim that you wrote the original software.
////    If you use this software in a product, an acknowledgment
////    in the product documentation would be appreciated but is not required.
////
//// 2. Altered source versions must be plainly marked as such,
////    and must not be misrepresented as being the original software.
////
//// 3. This notice may not be removed or altered from any source distribution.
////
//////////////////////////////////////////////////////////////

#include <iostream>
#include "Sprite.hpp"

OPEN_WO_GFX

//! Default constructor.
/*!
* Creates an empty sprite with no source texture.
*/
Sprite::Sprite() {

	mTexture = nullptr;
	mTextureRect = IntRect();

}

//! Construct sprite from a source texture.
/*!
* Constructs a sprite with the given source texture.
* \param texture Source texture.
* \sa setTexture
*/
Sprite::Sprite(const Texture& texture) {

	mTexture = nullptr;
	mTextureRect = IntRect();
    setTexture(texture) ;

}

//! Construct sprite from a source texture with a given render rectangle.
/*!
* Constructs a sprite with the given source texture. Additionally uses
* the given rectangle to determine which part of the texture is shown
* on screen.
* \param texture Source texture.
* \param rect Rectangle which defines the visible part of the texture.
*/
Sprite::Sprite(const Texture& texture, const IntRect& rect) {

	mTexture = NULL;
	mTextureRect = IntRect();
    setTexture(texture) ;
    setTextureRect(rect) ;

}

//! Texture destructing destructor.
/*!
* The purpose of this destructor is to delete the reference to
* the texture held by this object. Afterwards call the texture
* destructing function.
*/
Sprite::~Sprite(void) {

	TextureRepository::tidy();

}

//! Set the render rectangle, which the sprite will display.
/*!
* The texture rect is useful in cases in which not the whole,
* but rather a part of the texture should be drawn. By default,
* the rectangle is equal to the size of the texture.
* \param rect Rectangle defining the visible region of the texture.
*/
void Sprite::setTextureRect(const IntRect& rect) {

    if (rect != mTextureRect) {

        mTextureRect = rect;
        updatePosition();
        updateTextureCoordinates();

    }

}

//! Get the local boundaries rectangle.
/*!
* The returned rectangle is in local coordinates. This means that
* it ignores the transformations (translation, rotation, scale, ...)
* that are applied to the entity. To put it in other words, the
* bounds of the entity in the entitiy's coordinate system are returned.
* \return Local boundaries rectangle.
*/
FloatRect Sprite::getLocalBounds() const {

    float width = static_cast<float>(std::abs(mTextureRect.width)) ;
    float height = static_cast<float>(std::abs(mTextureRect.height)) ;

    return FloatRect(0.f, 0.f, width, height) ;

}

//! Update the vertices' texture coordinates.
/*!
* The coordinates are retrieved by the texture rect member and
* assigned anticlockwise.
*/
void Sprite::updateTextureCoordinates() {

    float left   = static_cast<float>(mTextureRect.left) ;
    float right  = left + mTextureRect.width ;
    float top    = static_cast<float>(mTextureRect.top) ;
    float bottom = top + mTextureRect.height ;

	// Coordinates, defined anticlockwise.
    mVertices[0].texCoords = Vector2f(left, top) ;
    mVertices[1].texCoords = Vector2f(left, bottom) ;
    mVertices[2].texCoords = Vector2f(right, bottom) ;
    mVertices[3].texCoords = Vector2f(right, top) ;

}

//! Draw the sprite to a render target.
/*!
* \param target Render target to draw to.
* \param states Current render states.
*/
void Sprite::draw(RenderTarget& target, RenderStates states) const {

    if (nullptr != mTexture) {

        states.transform *= getTransform();

    /*std::cout << "Size of the texture which will be drawn: ";
    std::cout << m_texture.get()->getSize().x << ", ";
    std::cout << m_texture.get()->getSize().y << std::endl;
    std::cout << "Use count of the texture: ";
    std::cout << m_texture.use_count();
    std::cin.get();*/

        states.texture = mTexture.get();
        target.draw(mVertices, 4, Quads, states);
    }

}

CLOSE_WO_GFX
