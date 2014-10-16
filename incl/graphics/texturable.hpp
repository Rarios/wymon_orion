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

#ifndef _TEXTUREABLE_
#define _TEXTUREABLE_

#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Rect.hpp>
#ifndef _TEXTUREREPOSITORY_
#include "texture_repos.hpp"
#endif

class sf::Texture;

//! Base class for texture handling.
/*!
* This abstract base class has functions to handle textures
* at the very basic level, like loading a sprite for instance.
* Its purpose is to be inherited and extended, like the Sprite
* class will do.
*/
class Textureable : public sf::Drawable, public sf::Transformable {

public :

	// Member functions.

	virtual ~Textureable(void) {}

	bool load(const std::string& filename,
              const sf::IntRect& displ_rect = sf::IntRect(),
			  const sf::IntRect& load_rect = sf::IntRect());
	bool load(const void* data, std::size_t size,
              const sf::IntRect& displ_rect = sf::IntRect(),
			  const sf::IntRect& load_rect = sf::IntRect());
	bool load(sf::InputStream& stream,
			  const sf::IntRect& displ_rect = sf::IntRect(),
			  const sf::IntRect& load_rect = sf::IntRect());
	bool load(const sf::Image& image,
			  const sf::IntRect& displ_rect = sf::IntRect(),
			  const sf::IntRect& load_rect = sf::IntRect());

	void setTexture(const sf::Texture& texture, bool resetRect = false);
	//! Set the render rectangle, which the sprite will display.
	/*!
	* ATTENTION: This is a pure virtual function. The classes
	* inheriting by this one should implement this funtion.
	*/
	virtual void setTexRect(const sf::IntRect& rect) = 0;
    void setColor(const sf::Color& color);

	const sf::Texture* getTexture() const;
	const sf::IntRect& getTexRect() const;
    const sf::Color& getColor() const;
	//! Get the local boundaries rectangle.
	/*!
	* ATTENTION: This is a pure virtual function. The classes
	* inheriting by this one should implement this funtion.
	*/
	virtual sf::FloatRect loc_bound() const = 0;
	sf::FloatRect glob_bound() const;
	sf::Vector2f obj_size() const;
    sf::Vector2f size() const;

protected :

	void updatePos();
	//! Update the vertices' texture coordinates.
	/*!
	* ATTENTION: This is a pure virtual function. The classes
	* inheriting by this one should implement this funtion.
	*/
    virtual void updateTexCoords() = 0;

#endif
	void appl_displ_rect(const sf::IntRect& displ_rect);

	//! Draw the sprite to a render target.
	/*!
	* ATTENTION: This is a pure virtual function. The classes
	* inheriting by this one should implement this funtion.
	* \param target Render target to draw to.
	* \param states Current render states.
	*/
	virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const = 0;

	// Member variables.

	//! Vertices defining the sprite's geometry
	/*!
	* The geometry of a sprite is defined by an array of
	* four vertices, which means it is of type "sf::Quads".
	*/
    sf::Vertex m_vertices[4];
	//! Pointer to the texture of the sprite.
    texture_ptr m_texture;
	//! Texture rectangle.
	/*!
	* Rectangle defining the area of the source texture to
	* display.
	*/
    sf::IntRect mTexRect;

};

#endif
