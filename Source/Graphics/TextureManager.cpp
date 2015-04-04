// TextureManager.cpp

#include <iostream>
#include "TextureManager.hpp"

OPEN_WO_GFX

// ADD TextureManager HANDLING FUNCTIONS TO THE SPRITE CLASS:
// REMEMBER - OVERLOAD THE COPY CONSTRUCTOR AND CALL inc_ref INSIDE OF IT
// AND CALL dec_ref BEFORE destroy INSIDE OF THE SPRITE DESTRUCTOR

// Member variables

//! Empty texture pointer.
/*!
* This constant member is used whenever a key is not found and a texture pointer 
* has to be returned. Use it to check for errors.
*/
const TexturePointer TextureManager::EMPTY_TEXTURE;

//! Hashtable holding all texture pointers according to their keys.
/*!
* At first, it should be an empty table.
*/
std::unordered_map<std::string, TexturePointer> TextureManager::mTextures;

//! Internal counter of destructed texture holding objects.
/*!
* Holds the number of objects destructed which had a reference to a texture
* pointer.
*/
std::size_t TextureManager::mDestructionCount = 0;

// Member functions

//! Load a texture from a file.
/*!
* Loads a texture from a file and associates it with the given key. 
* The area argument can be used to load only a
* sub-rectangle of the image. If the whole image should be loaded, leave this
* parameter by its default value. After the texture is successfully loaded, a
* pointer is stored in texturePtr. The function also checks if the key 
* is already taken.
* \param texturePtr Shared pointer which will hold reference to texture.
* \param filename Path of the image file to load.
* \param key Hashtable key to associate with Texture.
* \param area Area of the image to load.
* \return True on success. False if either key is taken, or file could not be loaded.
*/
bool TextureManager::loadFromFile(TexturePointer* texturePtr, const std::string& filename,
                              const std::string& key, const IntRect& area) {

    if(!isKeyUsed(key)) {

        mTextures[key] = TexturePointer(new Texture);
        if (!mTextures[key]->loadFromFile(filename, area)) {

            // Could not load file.
            return false;

        }

    } else {

        // Key is already taken.
        return false;

    }

    // Reference the stored texture, increases use_count().
    *texturePtr = mTextures[key];

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
* a pointer is stored in the texturePtr. The function also checks if the key 
* is already taken.
* \param texturePtr Shared pointer which will hold reference to texture.
* \param data Data in memory from which to load.
* \param size Size of the block of data.
* \param key Hashtable key to associate with Texture.
* \param area Area of the image to load.
* \return True on success.
*/
bool TextureManager::loadFromMemory(TexturePointer* texturePtr, const void* data,
                             std::size_t size, const std::string& key, const IntRect& area) {

	if(!isKeyUsed(key)) {

        mTextures[key] = TexturePointer(new Texture);
        if (!mTextures[key]->loadFromMemory(data, size, area)) {

            // Could not load file.
            return false;

        }

    } else {

        // Key is already taken.
        return false;

    }

    // Reference the stored texture, increases use_count().
    *texturePtr = mTextures[key];

    return true;

}

//! Load a texture from a custom stream.
/*!
* Loads a texture from a custom stream. The area argument can be used to load
* only a sub-rectangle of the image. If the whole image should be loaded, leave
* this parameter by its default value. After the texture is successfully loaded,
* a pointer is stored in the texturePtr. The function also checks if the key 
* is already taken.
* \param texturePtr Shared pointer which will hold reference to texture.
* \param stream Custom stream from which to load.
* \param key Hashtable key to associate with Texture.
* \param area Area of the image to load.
* \return True on success.
*/
bool TextureManager::loadFromStream(TexturePointer* texturePtr,
                                      InputStream& stream, const std::string& key,
                                      const IntRect& area) {

	if(!isKeyUsed(key)) {

        mTextures[key] = TexturePointer(new Texture);
        if (!mTextures[key]->loadFromStream(stream, area)) {

            // Could not load file.
            return false;

        }

    } else {

        // Key is already taken.
        return false;

    }

    // Reference the stored texture, increases use_count().
    *texturePtr = mTextures[key];

    return true;

}

//! Load a texture from an image.
/*!
* Loads a texture from an image. The area argument can be used to load only a
* sub-rectangle of the image. If the whole image should be loaded, leave this
* parameter by its default value. After the texture is successfully loaded, a
* pointer is stored in the texturePtr. The function also checks if the key 
* is already taken.
* \param texturePtr Shared pointer which will hold reference to texture.
* \param image Image from which to load.
* \param key Hashtable key to associate with Texture.
* \param area Area of the image to load.
* \return True on success.
*/
bool TextureManager::loadFromImage(TexturePointer* texturePtr,
                                      const Image& image, const std::string& key,
                                      const IntRect& area) {

	if(!isKeyUsed(key)) {

        mTextures[key] = TexturePointer(new Texture);
        if (!mTextures[key]->loadFromImage(image, area)) {

            // Could not load file.
            return false;

        }

    } else {

        // Key is already taken.
        return false;

    }

    // Reference the stored texture, increases use_count().
    *texturePtr = mTextures[key];

    return true;

}

//! Replaces a texture from a file.
/* 
* Replaces a texture with another one loaded from a file. The area argument can 
* be used to load only a sub-rectangle of the image. If the whole image should 
* be loaded, leave this parameter by its default value. Also checks if the key 
* exists.
* \param key Hashtable key to associate with Texture.
* \param filename Path of the image file to load.
* \param area Area of the image to load.
* \return True on success. False if the key does not exist or if the file could 
* not be loaded.
*/
bool TextureManager::replaceFromFile(const std::string& key, const std::string& filename, 
                     const IntRect& area ) {

    if(isKeyUsed(key)) {

        if (!mTextures[key]->loadFromFile(filename, area)) {

            // Could not load file.
            return false;

        }

    } else {

        // Key is not used - nothing to replace.
        return false;

    }

    return true;

}

//! Replaces a texture from a file in memory.
/* 
* Replaces a texture with another one loaded from memory. The area argument can be used 
* to load only a sub-rectangle of the image. If the whole image should be loaded, leave
* this parameter by its default value. Also checks if the key exists.
* \param key Hashtable key to associate with Texture.
* \param data Data in memory from which to load.
* \param size Size of the block of data.
* \param area Area of the image to load.
* \return True on success. False if the key does not exist 
* or if the data could not be loaded.
*/
bool TextureManager::replaceFromMemory(const std::string& key, const void* data, 
                     std::size_t size, const IntRect& area ) {

    if(isKeyUsed(key)) {

        if (!mTextures[key]->loadFromMemory(data, size, area)) {

            // Could not load file.
            return false;

        }

    } else {

        // Key is not used - nothing to replace.
        return false;

    }

    return true;

}

//! Replaces a texture from a custom stream.
/* 
* Replaces a texture with another one loaded from a custom stream. The area argument 
* can be used to load only a sub-rectangle of the image. If the whole image should be 
* loaded, leave this parameter by its default value. Also checks if the key exists.
* \param key Hashtable key to associate with Texture.
* \param stream Custom stream from which to load.
* \param area Area of the image to load.
* \return True on success. False if the key does not exist 
* or if the stream could not be loaded.
*/
bool TextureManager::replaceFromStream(const std::string& key, InputStream& stream,
                     const IntRect& area ) {

    if(isKeyUsed(key)) {

        if (!mTextures[key]->loadFromStream(stream, area)) {

            // Could not load file.
            return false;

        }

    } else {

        // Key is not used - nothing to replace.
        return false;

    }

    return true;

}

//! Replaces a texture from an image.
/* 
* Replaces a texture with another one loaded from an image. The area argument can be used 
* to load only a sub-rectangle of the image. If the whole image should be loaded, leave this
* parameter by its default value. The function also checks if the key 
* exists.
* \param key Hashtable key to associate with Texture.
* \param image Image from which to load.
* \param area Area of the image to load.
* \return True on success. False if the key does not exist or if the image file 
* could not be loaded.
*/
bool TextureManager::replaceFromImage(const std::string& key, const Image& image,
                     const IntRect& area ) {


    if(isKeyUsed(key)) {

        if (!mTextures[key]->loadFromImage(image, area)) {

            // Could not load file.
            return false;

        }

    } else {

        // Key is not used - nothing to replace.
        return false;

    }

    return true;

}

//! Returns the texture pointer associated with the given key.
/*!
* This function returns the texture pointer associated with the given key, 
* in case the key is found. If the key does not exist, TextureManager::EMPTY_TEXTURE 
* is returned.
* \param key Hash key (string).
* \return texture pointer associated with the key.
*/
const TexturePointer& TextureManager::getTexture(const std::string& key) {

    if(isKeyUsed(key)) {

        return mTextures[key];

    } else {

        // Key does not exist.
        return EMPTY_TEXTURE;

    }
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
bool TextureManager::removeTexture(const TexturePointer& texturePtr) {

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

void TextureManager::tidy() {

/*
    ++ mDestructionCount;

	if (mTextures.size()/2 <= mDestructionCount) {

        mTextures.remove_if(removeTexture);
        mDestructionCount = 0;

	}
*/

}

//! Checks if the key is already taken.
/*!
* This function checks if a Hashtable key is alredy taken. 
* This should be used every time a new Hashtable entry is generated.
* \param key Hashtable key to check.
* \return true if key is taken.
*/
bool TextureManager::isKeyUsed(const std::string& key) {

    return mTextures.end() != mTextures.find(key);

}

CLOSE_WO_GFX
