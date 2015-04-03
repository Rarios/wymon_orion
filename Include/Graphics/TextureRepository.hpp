// texture_repository.hpp

#ifndef GRAPHICS_TEXTUREREPOSITORY
#define GRAPHICS_TEXTUREREPOSITORY

#include <string>
#include <list>
#include <memory>
#include <SFML/Graphics.hpp>
#ifndef WO_NAMESPACE
	#include "Namespace.hpp"
#endif

// Only temporarily during integration of coding conventions.
using namespace sf;

OPEN_WO_GFX

//! Type to conveniently work with shared textures.
/*!
* This type uses the ability of std::shared_ptr to count the number of
* references currently in use. If only the texture container refers to the
* texture, it will be deleted out of the memory.
*/
typedef std::shared_ptr<Texture> TexturePointer;

//! Static class to automatically handle textures.
/*!
* In the SFML, a sprite only holds a pointer to a Texture object, which
* means this object must not be destroyed as long as the sprite uses it. Since
* it is sometimes difficult to manage those textures and keep them alive as long
* as they are needed, this conveniece class has been created. It holds a static
* array of textures, so that they can be accessed and referenced by Sprite
* objects, but not accidently destroyed during runtime. Therefore the code will
* be much cleaner an easier to handle; Sprite objects should most likely be the
* only object which has to be taken care of.
*/
class TextureRepository {

public :

	// Member functions

	static bool loadFromFile(TexturePointer* texturePtr, const std::string& filename,
					 const IntRect& area = IntRect());
	static bool loadFromMemory(TexturePointer* texturePtr, const void* data, std::size_t size,
					 const IntRect& area = IntRect());
	static bool loadFromStream(TexturePointer* texturePtr, InputStream& stream,
					 const IntRect& area = IntRect());
	static bool loadFromImage(TexturePointer* texturePtr, const Image& image,
					 const IntRect& area = IntRect());

    static bool removeTexture(const TexturePointer& texturePtr);
	static void tidy();

private :

	// Member variables

	static std::list<TexturePointer> mTextures;
	static std::size_t mDestructionCount;

};

CLOSE_WO_GFX

#endif
