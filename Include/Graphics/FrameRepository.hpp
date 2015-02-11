// frame_repository - Static storage space for frames of animations.
// frame_repository
// frame_repository.hpp

#ifndef GRAPHICS_FRAMEREPOSITORY
#define GRAPHICS_FRAMEREPOSITORY

#include <string>
#include <list>
#include <vector>
#include <array>
#include <memory>
#include <Graphics.hpp>
#ifndef WO_NAMESPACE
	#include "Namespace.hpp"
#endif
#ifndef GRAPHICS_FRAME
	#include "Frame.hpp"
#endif

OPEN_WO_GFX

//! Index for original frames.
/*!
* Index of storage for original, unmodified frames.
*/
const std::size_t ORIGINAL_FRAME = 0;

//! Index for modified frames.
/*!
* Index of storage for modified (applied texture rectangle) frames.
*/
const std::size_t TEXTURE_RECT_FRAME = 1;

//! Type to simplify the storage of frames.
/*!
* This type uses the ability of std::shared_ptr to count the number of
* references currently in use. If only the frame container refers to the
* frame, it will be deleted out of the memory.

* This typedef is used to conveniently handle random access frame containers,
* of which two exist. One for the plain frames of a animation, the other is used
* for the frames with the applied texture rectangles for the visual part of the
* frame. Both need to be kept alive, since the second one is obviously used for
* the animation display and the first may be used if later on the texture
* rectangle changes. The shared pointer makes sure the containers are shareable
* and get destroyed once no animation uses them anymore. This also means the
* frames inside the containers have to be always copied, so no access of
* corrupted data occures.
*
* Reason why these types are used:
* std::list - Later used as FramesPointer container, allowes fast element insertion
* and removal.
* std::shared_ptr - sharing and use_count() of objects
* std::array - fast for a fixed amount of elements; perfect since we allways
* need two.
* std::vector - random access, so the order of appearance can be abitrary.
*/
typedef std::shared_ptr<std::array<std::vector<Frame>, 2>> FramesPointer;

//! Static class to automatically handle animation frames.
/*!
* The animation class needs frame objects to determine which parts of a sprite
* sheet should be used on at a time. Since it might happen that an animation
* needs a lot of frames, the animation instance itself will be very heavy in
* terms of memory. This is a drawback for function calls with animation object
* parameters. To prevent this from happening, the frame objects are stored
* outside the animation objects, inside this static class. So the size of an
* animation instance will always be the same, holding only a pointer to the
* random access frame container.
*/
class FrameRepository {

public :

	// Member functions

	static void initialize(FramesPointer* framePtr);

    static std::size_t insert(FramesPointer* framePtr, const frame& frame,
                              const IntRect& tex_rect = IntRect());
	static std::size_t insert(FramesPointer* framePtr, const frame& frame,
                              std::size_t index,
                              const IntRect& tex_rect = IntRect());

    static void replace(FramesPointer* framePtr, const frame& other,
                        std::size_t index,
                        const IntRect& rect = IntRect());
    static void applyTextureRect(FramesPointer* framePtr, const IntRect& tex_rect);

	static bool removeFrame(const FramesPointer& framePtr);
	static void tidy();

	static frame getIntersection(const frame& lhs,
                           		const IntRect& rhs);

private :

	// Member variables

	static std::list<FramesPointer> mFrames;
	static std::size_t mDestructionCount;
	
};

CLOSE_WO_GFX

#endif
