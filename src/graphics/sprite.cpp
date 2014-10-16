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

#include "sprite.hpp"
#include <iostream>

//! Default constructor.
/*!
* Creates an empty sprite with no source texture.
*/
Sprite::Sprite() {

	m_texture = nullptr;
	mTexRect = sf::IntRect();

}

//! Construct sprite from a source texture.
/*!
* Constructs a sprite with the given source texture.
* \param texture Source texture.
* \sa setTexture
*/
Sprite::Sprite(const sf::Texture& texture) {

	m_texture = nullptr;
	mTexRect = sf::IntRect();
    setTexture(texture) ;

}

//! Construct sprite from a source texture with a given render rectangle.
/*!
* Constructs a sprite with the given source texture. Additionally uses
* the given rectangle to determine which part of the texture is shown
* on screen.
* \param texture Source texture.
* \param rect Rectangle which defines the visible part of the texture.
* \sa setTexture, setTexRect
*/
Sprite::Sprite(const sf::Texture& texture, const sf::IntRect& rect) {

	m_texture = NULL;
	mTexRect = sf::IntRect();
    setTexture(texture) ;
    setTexRect(rect) ;

}

//! Texture destructing destructor.
/*!
* The purpose of this destructor is to delete the reference to
* the texture held by this object. Afterwards call the texture
* destructing function.
*/
Sprite::~Sprite(void) {

	texture_repository::tidy();

}

//! Set the render rectangle, which the sprite will display.
/*!
* The texture rect is useful in cases in which not the whole,
* but rather a part of the texture should be drawn. By default,
* the rectangle is equal to the size of the texture.
* \param rectangle Rectangle defining the visible region of the texture.
*/
void Sprite::setTexRect(const sf::IntRect& rect) {

    if (rect != mTexRect) {

        mTexRect = rect ;
        updatePos() ;
        updateTexCoords() ;

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
sf::FloatRect Sprite::loc_bound() const {

    float width = static_cast<float>(std::abs(mTexRect.width)) ;
    float height = static_cast<float>(std::abs(mTexRect.height)) ;

    return sf::FloatRect(0.f, 0.f, width, height) ;

}

//! Update the vertices' texture coordinates.
/*!
* The coordinates are retrieved by the texture rect member and
* assigned anticlockwise.
*/
void Sprite::updateTexCoords() {

    float left   = static_cast<float>(mTexRect.left) ;
    float right  = left + mTexRect.width ;
    float top    = static_cast<float>(mTexRect.top) ;
    float bottom = top + mTexRect.height ;

	// Coordinates, defined anticlockwise.
    m_vertices[0].texCoords = sf::Vector2f(left, top) ;
    m_vertices[1].texCoords = sf::Vector2f(left, bottom) ;
    m_vertices[2].texCoords = sf::Vector2f(right, bottom) ;
    m_vertices[3].texCoords = sf::Vector2f(right, top) ;

}

//! Draw the sprite to a render target.
/*!
* \param target Render target to draw to.
* \param states Current render states.
*/
void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    if (nullptr != m_texture)
    {
        states.transform *= getTransform();


    /*std::cout << "Size of the texture which will be drawn: ";
    std::cout << m_texture.get()->getSize().x << ", ";
    std::cout << m_texture.get()->getSize().y << std::endl;
    std::cout << "Use count of the texture: ";
    std::cout << m_texture.use_count();
    std::cin.get();*/

        states.texture = m_texture.get();
        target.draw(m_vertices, 4, sf::Quads, states);
    }

}
