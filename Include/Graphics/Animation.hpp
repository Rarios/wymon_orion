// Animation
// animation.hpp

#ifndef GRAPHICS_ANIMATION
#define GRAPHICS_ANIMATION

#include <Graphics.hpp>
#ifndef WO_NAMESPACE
	#include "Namespace.hpp"
#endif
#ifndef GRAPHICS_TEXTURABLE
	#include "Texturable.hpp"
#endif
#ifndef GRAPHICS_TEXTUREREPOSITORY
	#include "TextureRepository.hpp"
#endif
#ifndef GRAPHICS_FRAMEREPOSITORY
	#include "FrameRepository.hpp"
#endif

OPEN_WO_GFX

//! Class for animating sprites.
/*!
* This class provides methods for creating, modifying and rendering animated
* sprites. It uses a texture as base for the graphical information and Frames,
* which provide basic information about animation Frames.
*/
class Animation : public Texturable {

public:

    // Member functions.

    Animation();
    Animation(const Texture& texture);
    Animation(const Texture& texture, const IntRect& rect);
    ~Animation();

    std::size_t insert(const Frame& frm, IntRect rect = IntRect());
    std::size_t insert(const Frame& frm, std::size_t index,
                       IntRect rect = IntRect());
    std::size_t insert(const FrameGroup& frm_grp,
                       IntRect rect = IntRect());
    std::size_t insert(const FrameGroup& frm_grp, std::size_t index,
                       IntRect rect = IntRect());

    void setTextureRect(const IntRect& rect);

	void replace(std::size_t index, const Frame& other);
	void modifySize(std::size_t index, const Vector2i& size);
	void modifyPosition(std::size_t index, const Vector2i& position);

    std::size_t render();
    std::size_t render(std::size_t index);

	FloatRect getLocalBounds() const;
	Vector2f getMaximumObjectSize();
	Vector2f getMaximumSize();
	std::size_t getFramesCount();

private:

	void computeMaximumSize(const Vector2f& size);
    void updateTextureCoordinates();

    void draw(RenderTarget& target, RenderStates states) const;

    //! Pointer to stored Frames inside repository.
    FramesPointer mFrames;
    //! Index of the current pointer.
    std::size_t mIndex;
	//! Biggest Frame of the animation.
	Vector2f mMaximumSize;

};

CLOSE_WO_GFX

#endif
