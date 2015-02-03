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

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <cstdlib>
#include "texturable.hpp"

//! Load a texture from file into the sprite.
/*!
* Loads a texture object from a file and stores a pointer to it
* inside of the sprite. With the two last arguments, it can be specified how
* much of the image should be loaded, and how much of the loaded content should
* be displayed.
* \param filename Name of the file from which to load.
* \param displ_rect Area of texture (applied load_rect) to display.
* \param load_rect Area of image (file) to load.
* \return True on success.
*/
/* \todo Apply the better style of the load function (below) to all other
load functions */
bool Textureable::load(const std::string& filename,
					   const sf::IntRect& displ_rect,
					   const sf::IntRect& load_rect) {

    if (!texture_repository::load(&this->m_texture, filename, load_rect)) {

        return false;

    }

	// THIS LINE CAUSE THE SPRITE NOT TO APPEAR ON SCREEN. UNCOMMENT IT TO FIX
	// THE ERROR.
	//setTexture(*(m_texture.get()));
	
	appl_displ_rect(displ_rect);	

	return true;

}

//! Load a texture from a file in memory.
/*!
* Loads a texture object from a file in memory and stores a pointer to it
* inside of the sprite. With the two last arguments, it can be specified how
* much of the image should be loaded, and how much of the loaded content should
* be displayed.
* \param data Data in memory from which to load.
* \param size Size of the block of data.
* \param displ_rect Area of texture (applied load_rect) to display.
* \param load_rect Area of image (file) to load.
* \return True on success.
*/
bool Textureable::load(const void* data, std::size_t size,
					   const sf::IntRect& displ_rect,
					   const sf::IntRect& load_rect) {

    if (!texture_repository::load(&this->m_texture, data, size, load_rect)) {

        return false;

    }

	appl_displ_rect(displ_rect);

	return true;

}

//! Load a texture from a custom stream.
/*!
* Loads a texture object from a custrom stream and stores a pointer to it
* inside of the sprite. With the two last arguments, it can be specified how
* much of the image should be loaded, and how much of the loaded content should
* be displayed.
* \param stream Custom stream from which to load.
* \param displ_rect Area of texture (applied load_rect) to display.
* \param load_rect Area of image (file) to load.
* \return True on success.
*/
bool Textureable::load(sf::InputStream& stream, const sf::IntRect& displ_rect,
					   const sf::IntRect& load_rect) {

    if (!texture_repository::load(&this->m_texture, stream, load_rect)) {

        return false;

    }

	appl_displ_rect(displ_rect);

	return true;

}

//! Load a texture from an image.
/*!
* Loads a texture object from an image and stores a pointer to it
* inside of the sprite. With the two last arguments, it can be specified how
* much of the image should be loaded, and how much of the loaded content should
* be displayed.
* \param image Image from which to load.
* \param displ_rect Area of texture (applied load_rect) to display.
* \param load_rect Area of image (file) to load.
* \return True on success.
*/
bool Textureable::load(const sf::Image& image, 
					   const sf::IntRect& displ_rect,
					   const sf::IntRect& load_rect) {

    if (!texture_repository::load(&this->m_texture, image, load_rect)) {

        return false;

    }

	appl_displ_rect(displ_rect);

	return true;

}

//! Change the source texture.
/*!
* The texture argument must not be destroyed as long as the Sprite
* object uses it. This is due to the fact, that only a pointer to
* the source texture is hold inside this class, but not a copy. If
* the texture is destroyed anyway, the behaviour is undefined.
*
* If the seconds parameter is true, the internal render rectangle
* is adjusted to the size of the new texture; otherwise left
* unchanged.
* \param texture New source texture.
* \param If true, the visible (drawn) rectangle is adjusted.
* \sa setTexRect
*/
void Textureable::setTexture(const sf::Texture& texture, bool reset_rect)
{

    // Recompute the texture area if requested, or if there is a valid texture,
    // but there has not been a rect before.
	if (reset_rect || (nullptr != m_texture && (mTexRect == sf::IntRect())))
        setTexRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));

    // Assign the new texture.
    m_texture = std::make_shared<sf::Texture>(texture);

}

//! Set the global color of the sprite.
/*!
* The color will be modulated (multiplied) with the
* color of the texture (defined by the data). It can
* be used to colorize the sprite, or change its global
* opacity.
* By default, the sprite's color is opaque white.
* \param color New color of the sprite.
* \sa get_color
*/
void Textureable::setColor(const sf::Color& color)
{

    // Update the vertices' color.
    m_vertices[0].color = color ;
    m_vertices[1].color = color ;
    m_vertices[2].color = color ;
    m_vertices[3].color = color ;

}

//! Get the source texture of the sprite.
/*!
* If the sprite currently does not hold a source
* texture, a NULL pointer is returned. Since the returned
* pointer is const, the texture is not modifyable if retrieved
* with this funtion.
* \return Pointer to the sprite's texture.
* \sa get_tex_rect
*/
const sf::Texture* Textureable::getTexture() const
{

    return m_texture.get() ;

}

//! Get the render rectangle of the sprite.
/*!
* The render rectangle defines the part of the texture,
* which is actually drawn on screen.
* \return Render rectangle of the sprite.
* \sa set_tex_rect
*/
const sf::IntRect& Textureable::getTexRect() const {

    return mTexRect ;

}

//! Get the global color of the sprite.
/*!
* \return Global color of the sprite.
*/
const sf::Color& Textureable::getColor() const
{

    return m_vertices[0].color ;

}

//! Get the global boundaries rectangle.
/*!
* The returned rectangle is in global coordinates, which means
* that it takes in account the transformations (translation,
* rotation, scale, ...) that are applied to the entity.
* In other words, this function returns the bounds of the
* sprite in the global 2D world's coordinate system.
* \return Global boundaries rectangle.
*/
sf::FloatRect Textureable::glob_bound() const {

    return getTransform().transformRect(loc_bound()) ;

}

//! Get the local object size.
/*!
* This is a convenience function. It just return the width and height from the
* loc_bound() function, so less data has to be passed if only the size is
* needed.
* \return Object size (size without transformations).
*/
sf::Vector2f Textureable::obj_size() const {

	auto size = loc_bound();

    return sf::Vector2f(size.width, size.height);

}

//! Get the global size.
/*!
* This is a convenience function. It just return the width and height from the
* glob_bound() function, so less data has to be passed if only the size is
* needed.
* \return Global boundaries rectangle.
*/
sf::Vector2f Textureable::size() const {

	auto size = glob_bound();

    return sf::Vector2f(size.width, size.height);

}

//! Update the vertices' position.
/*!
* The position is retrieved by the local bounds and
* assigned anticlockwise.
*/
void Textureable::updatePos()
{

    sf::FloatRect bounds = loc_bound() ;

	// Position, defined anticlockwise.
    m_vertices[0].position = sf::Vector2f(0, 0) ;
    m_vertices[1].position = sf::Vector2f(0, bounds.height) ;
    m_vertices[2].position = sf::Vector2f(bounds.width, bounds.height) ;
    m_vertices[3].position = sf::Vector2f(bounds.width, 0) ;

}

//! Apply display rectangle.
/*!
* Convenience function to set a visible (displayed) are for the texture to draw
* on the screen. Since there does not necessarily have to be a display
* rectangle, this function sets one that is big enough to display all of the
* texture in case there is no given rectangle.
* \param displ_rect Display rectangle to apply.
*/
void Textureable::appl_displ_rect(const sf::IntRect& displ_rect) {

	if (sf::IntRect() == displ_rect) {
		
		// If there is no display rectangle set, create one as big as the
		// texture.
		setTexRect(sf::IntRect(0, 0, 
							   m_texture->getSize().x, m_texture->getSize().y));

	} else {
			
		setTexRect(displ_rect);

	}

}
