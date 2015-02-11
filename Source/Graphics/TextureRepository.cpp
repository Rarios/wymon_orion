// TextureRepository.cpp

#include <iostream>
#include "TextureRepository.hpp"

OPEN_WO_GFX

// ADD TextureRepository HANDLING FUNCTIONS TO THE SPRITE CLASS:
// REMEMBER - OVERLOAD THE COPY CONSTRUCTOR AND CALL inc_ref INSIDE OF IT
// AND CALL dec_ref BEFORE destroy INSIDE OF THE SPRITE DESTRUCTOR

// Member variables

//! List holding all textures.
/*!
* At first, it should be an empty list.
*/
std::list<TexturePointer> TextureRepository::mTextures;

//! Internal counter of destructed texture holding objects.
/*!
* Holds the number of objects destructed which had a reference to a texture
* pointer.
*/
std::size_t TextureRepository::mDestructionCount = 0;

// Member functions

//! Load a texture from a file.
/*!
* Loads a texture from a file. The area argument can be used to load only a
* sub-rectangle of the image. If the whole image should be loaded, leave this
* parameter by its default value. After the texture is successfully loaded, a
* pointer is stored in the TexturePointer.
* \param texturePtr Shared pointer which will hold reference to texture.
* \param filename Path of the image file to load.
* \param area Area of the image to load.
* \return True on success.
*/
bool TextureRepository::loadFromFile(TexturePointer* texturePtr, const std::string& filename,
                              const IntRect& area) {

	mTextures.emplace_back(new Texture);

	if (!mTextures.back()->loadFromFile(filename, area)) {

        // Could not load file.
        return false;

	}

    // Reference the stored texture, increases use_count().
    *texturePtr = mTextures.back();

    /*std::cout << "Size of the texture: ";
    std::cout << mTextures.back()->getSize().x << ", ";
    std::cout << mTextures.back()->getSize().y << std::endl;*/

    return true;

}

//! Load a texture from a file in memory.
/*!
* Loads a texture from a file in memory. The area argument can be used to load
* only a sub-rectangle of the image. If the whole image should be loaded, leave
* this parameter by its default value. After the texture is successfully loaded,
* a pointer is stored in the TexturePointer.
* \param texturePtr Shared pointer which will hold reference to texture.
* \param data Data in memory from which to load.
* \param size Size of the block of data.
* \param area Area of the image to load.
* \return True on success.
*/
bool TextureRepository::loadFromMemory(TexturePointer* texturePtr, const void* data,
                              std::size_t size, const IntRect& area) {

	mTextures.emplace_back(new Texture);

	if (!mTextures.back()->loadFromMemory(data, size, area)) {

        // Could not load file.
        return false;

	}

    // Reference the stored texture, increases use_count().
    *texturePtr = mTextures.back();

    return true;

}

//! Load a texture from a custom stream.
/*!
* Loads a texture from a custom stream. The area argument can be used to load
* only a sub-rectangle of the image. If the whole image should be loaded, leave
* this parameter by its default value. After the texture is successfully loaded,
* a pointer is stored in the TexturePointer.
* \param texturePtr Shared pointer which will hold reference to texture.
* \param stream Custom stream from which to load.
* \param area Area of the image to load.
* \return True on success.
*/
bool TextureRepository::loadFromStream(TexturePointer* texturePtr,
                                      InputStream& stream,
                                      const IntRect& area) {

	mTextures.emplace_back(new Texture);

	if (!mTextures.back()->loadFromStream(stream, area)) {

        // Could not load file.
        return false;

	}

    // Reference the stored texture, increases use_count().
    *texturePtr = mTextures.back();

    return true;

}

//! Load a texture from an image.
/*!
* Loads a texture from an image. The area argument can be used to load only a
* sub-rectangle of the image. If the whole image should be loaded, leave this
* parameter by its default value. After the texture is successfully loaded, a
* pointer is stored in the TexturePointer.
* \param texturePtr Shared pointer which will hold reference to texture.
* \param image Image from which to load.
* \param area Area of the image to load.
* \return True on success.
*/
bool TextureRepository::loadFromImage(TexturePointer* texturePtr,
                                      const Image& image,
                                      const IntRect& area) {

	mTextures.emplace_back(new Texture);

	if (!mTextures.back()->loadFromImage(image, area)) {

        // Could not load file.
        return false;

	}

    // Reference the stored texture, increases use_count().
    *texturePtr = mTextures.back();

    return true;

}

//! Test whether to destruct a texture or not.
/*!
* This function is passed to std::list::remove_if() to be the condition under
* which a texture is removed from the list. If the use count of a texture
* pointer is one, only the std::list refers to it anymore, so it can be
* destructed without any damage.
* \param texturePtr Texture pointer to the texture object.
* \return True if std::shared_ptr::use_count() equals 1.
*/
bool TextureRepository::removeTexture(const TexturePointer& texturePtr) {

	// 1, because 'use_count()' counts the pointer that calls it as user too.
    return 1 == texturePtr.use_count();

}

//! Removes all unused textures from the list if needed.
/*!
* This function should be called in any object's destructor which uses a
* texture. It basically handles a counter which is increased everytime an object
* is release that had a reference to a texture pointer. Once this counter is
* half the size of the internal texture list, a function is called to garbage
* collect all unused textures.
*/
void TextureRepository::tidy() {

    ++ mDestructionCount;

	if (mTextures.size()/2 <= mDestructionCount) {

        mTextures.remove_if(removeTexture);
        mDestructionCount = 0;

	}

}

CLOSE_WO_GFX
