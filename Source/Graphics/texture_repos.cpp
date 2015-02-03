// texture_repository.cpp

#include "texture_repos.hpp"
#include <iostream>

// ADD texture_repository HANDLING FUNCTIONS TO THE SPRITE CLASS:
// REMEMBER - OVERLOAD THE COPY CONSTRUCTOR AND CALL inc_ref INSIDE OF IT
// AND CALL dec_ref BEFORE destroy INSIDE OF THE SPRITE DESTRUCTOR

// Member variables

//! List holding all textures.
/*!
* At first, it should be an empty list.
*/
std::list<texture_ptr> texture_repository::m_textures;

//! Internal counter of destructed texture holding objects.
/*!
* Holds the number of objects destructed which had a reference to a texture
* pointer.
*/
std::size_t texture_repository::destruct_count = 0 ;

// Member functions

//! Load a texture from a file.
/*!
* Loads a texture from a file. The area argument can be used to load only a
* sub-rectangle of the image. If the whole image should be loaded, leave this
* parameter by its default value. After the texture is successfully loaded, a
* pointer is stored in the texture_ptr.
* \param tex_ptr Shared pointer which will hold reference to texture.
* \param filename Path of the image file to load.
* \param area Area of the image to load.
* \return True on success.
*/
bool texture_repository::load(texture_ptr* tex_ptr, const std::string& filename,
                              const sf::IntRect& area) {

	m_textures.emplace_back(new sf::Texture);

	if (!m_textures.back()->loadFromFile(filename, area)) {

        // Could not load file.
        return false;

	}

    // Reference the stored texture, increases use_count().
    *tex_ptr = m_textures.back();

    /*std::cout << "Size of the texture: ";
    std::cout << m_textures.back()->getSize().x << ", ";
    std::cout << m_textures.back()->getSize().y << std::endl;*/

    return true;

}

//! Load a texture from a file in memory.
/*!
* Loads a texture from a file in memory. The area argument can be used to load
* only a sub-rectangle of the image. If the whole image should be loaded, leave
* this parameter by its default value. After the texture is successfully loaded,
* a pointer is stored in the texture_ptr.
* \param tex_pointer Shared pointer which will hold reference to texture.
* \param data Data in memory from which to load.
* \param size Size of the block of data.
* \param area Area of the image to load.
* \return True on success.
*/
bool texture_repository::load(texture_ptr* tex_ptr, const void* data,
                              std::size_t size, const sf::IntRect& area) {

	m_textures.emplace_back(new sf::Texture);

	if (!m_textures.back()->loadFromMemory(data, size, area)) {

        // Could not load file.
        return false;

	}

    // Reference the stored texture, increases use_count().
    *tex_ptr = m_textures.back();

    return true;

}

//! Load a texture from a custom stream.
/*!
* Loads a texture from a custom stream. The area argument can be used to load
* only a sub-rectangle of the image. If the whole image should be loaded, leave
* this parameter by its default value. After the texture is successfully loaded,
* a pointer is stored in the texture_ptr.
* \param tex_pointer Shared pointer which will hold reference to texture.
* \param stream Custom stream from which to load.
* \param area Area of the image to load.
* \return True on success.
*/
bool texture_repository::load(texture_ptr* tex_ptr,
                                      sf::InputStream& stream,
                                      const sf::IntRect& area) {

	m_textures.emplace_back(new sf::Texture);

	if (!m_textures.back()->loadFromStream(stream, area)) {

        // Could not load file.
        return false;

	}

    // Reference the stored texture, increases use_count().
    *tex_ptr = m_textures.back();

    return true;

}

//! Load a texture from an image.
/*!
* Loads a texture from an image. The area argument can be used to load only a
* sub-rectangle of the image. If the whole image should be loaded, leave this
* parameter by its default value. After the texture is successfully loaded, a
* pointer is stored in the texture_ptr.
* \param tex_pointer Shared pointer which will hold reference to texture.
* \param image Image from which to load.
* \param area Area of the image to load.
* \return True on success.
*/
bool texture_repository::load(texture_ptr* tex_ptr,
                                      const sf::Image& image,
                                      const sf::IntRect& area) {

	m_textures.emplace_back(new sf::Texture);

	if (!m_textures.back()->loadFromImage(image, area)) {

        // Could not load file.
        return false;

	}

    // Reference the stored texture, increases use_count().
    *tex_ptr = m_textures.back();

    return true;

}

//! Test whether to destruct a texture or not.
/*!
* This function is passed to std::list::remove_if() to be the condition under
* which a texture is removed from the list. If the use count of a texture
* pointer is one, only the std::list refers to it anymore, so it can be
* destructed without any damage.
* \param tex_ptr Texture pointer to the texture object.
* \return True if std::shared_ptr::use_count() equals 1.
*/
bool texture_repository::remove_texture(const texture_ptr& tex_ptr) {

    return 1 == tex_ptr.use_count();

}

//! Removes all unused textures from the list if needed.
/*!
* This function should be called in any object's destructor which uses a
* texture. It basically handles a counter which is increased everytime an object
* is release that had a reference to a texture pointer. Once this counter is
* half the size of the internal texture list, a function is called to garbage
* collect all unused textures.
*/
void texture_repository::tidy() {

    ++ destruct_count;

	if (m_textures.size() < destruct_count) {

        m_textures.remove_if(remove_texture);
        destruct_count = 0;

	}

}
