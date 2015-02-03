// texture_repository.hpp

#ifndef _TEXTUREREPOSITORY_
#define _TEXTUREREPOSITORY_

#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include <memory>

//! Type to conveniently work with shared textures.
/*!
* This type uses the ability of std::shared_ptr to count the number of
* references currently in use. If only the texture container refers to the
* texture, it will be deleted out of the memory.
*/
typedef std::shared_ptr<sf::Texture> texture_ptr;

//! Static class to automatically handle textures.
/*!
* In the SFML, a sprite only holds a pointer to a sf::Texture object, which
* means this object must not be destroyed as long as the sprite uses it. Since
* it is sometimes difficult to manage those textures and keep them alive as long
* as they are needed, this conveniece class has been created. It holds a static
* array of textures, so that they can be accessed and referenced by Sprite
* objects, but not accidently destroyed during runtime. Therefore the code will
* be much cleaner an easier to handle; Sprite objects should most likely be the
* only object which has to be taken care of.
*/
class texture_repository {

public :

	// Member functions

	static bool load(texture_ptr* tex_ptr, const std::string& filename,
					 const sf::IntRect& area = sf::IntRect());
	static bool load(texture_ptr* tex_ptr, const void* data, std::size_t size,
					 const sf::IntRect& area = sf::IntRect());
	static bool load(texture_ptr* tex_ptr, sf::InputStream& stream,
					 const sf::IntRect& area = sf::IntRect());
	static bool load(texture_ptr* tex_ptr, const sf::Image& image,
					 const sf::IntRect& area = sf::IntRect());

    static bool remove_texture(const texture_ptr& tex_ptr);
	static void tidy();

private :

	// Member variables

	static std::list<texture_ptr> m_textures;
	static std::size_t destruct_count;

};

#endif
