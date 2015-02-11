// FrameRepository.cpp

#include <cassert>
#include <iostream>
#include "FrameRepository.hpp"

OPEN_WO_GFX

// Member variables

// ATTENTION: Do NOT change the "operator[]()" calls to just "[]". Implicit
// calls to the overloaded operator generate compiler errors.

//! List holding all frames.
/*!
* At first, it should be an empty list.
*/
std::list<FramesPointer> FrameRepository::mFrames;

//! Internal counter of destructed frame holding objects.
/*!
* Holds the number of objects destructed which had a reference to a frame
* pointer.
*/
std::size_t FrameRepository::mDestructionCount = 0;

// Member functions

//! Create pointer to frame storing structure.
/*!
* Creates a pointer to a structure for storing frames, which then can be used by
* an animation object to access frames.
*
* NOTE: Since every instance of the animation class only needs one of these
* pointers, this function should be called inside the constructor.
* \param framePtr Pointer which will point to frame storing structure.
*/
void FrameRepository::initialize(FramesPointer* framePtr) {

    // Create new frame storage and assign pointer for the animation.
    // ATTENTION: Do not use emplace_back() here, it causes problems due to
    // an error while initializing. Since temp is only valid in this scope, it
    // won't cause any errors when dealing with use_count().
	/* \todo (lin#9#2014-08-15): The error was, that the intance of the shared_ptr
	which has been push backed was not initialized properly.
	This is fixed now, maybe try to simplify the code a little
	by making some typedefs.

	Also try to use emplace_back again. */
	std::vector<Frame> tempVector;
    FramesPointer temp(new std::array<std::vector<Frame>, 2>);
	temp->operator[](ORIGINAL_FRAME) = tempVector;
	temp->operator[](TEXTURE_RECT_FRAME) = tempVector;
    mFrames.push_back(temp);
    *framePtr = mFrames.back();

}

//! Inserts frame at the back of the repository.
/*!
* Inserts given frame into the repository list at the end. If a texture
* rectangle other than an empty one is given, it is also applied to the frame
* and stored inside.
* \param framePtr Pointer to where the frames are stored for the animation.
* \param frame Frame to store.
* \param textureRect Texture rectangle to apply.
* \return Index where the frame has been inserted.
*/
std::size_t FrameRepository::insert(FramesPointer* framePtr, const Frame& frame,
                                     const IntRect& textureRect) {

    (*framePtr)->operator[](ORIGINAL_FRAME).push_back(frame);

    // If no texture rectangle is given, store the unmodified frame inside the
    // texture rectangle storage as well. If one is given, apply and store.
    if (IntRect() == textureRect) {

        (*framePtr)->operator[](TEXTURE_RECT_FRAME).push_back(frame);

    } else {

        (*framePtr)->operator[](TEXTURE_RECT_FRAME).push_back(getIntersection(frame, textureRect));

    }

    return ((*framePtr)->operator[](ORIGINAL_FRAME).size() - 1);

}

//! Inserts frame into the repository.
/*!
* Inserts given frame into the repository list at given position. If a texture
* rectangle other than an empty one is given, it is also applied to the frame
* and stored inside.
*
* ATTENTION: There should be at least one frame inside the repository, so this
* function does not crash. Also, no range checking is done.
*
* ATTENTION: This function will iterate until the position of index, which is
* considered O(index), linear complexity. Try to use the other overload, since
* it is O(1), constsant complexity. Try to use the O(1) function.
* the container.
* \param framePtr Pointer to where the frames are stored for the animation.
* \param frame Frame to store.
* \param index Index of where to store it.
* \param textureRect Texture rectangle to apply.
* \return Index where the frame has been inserted (just returns index).
*/
std::size_t FrameRepository::insert(FramesPointer* framePtr, const Frame& frame,
                                     std::size_t index,
                                     const IntRect& textureRect) {

    // Get iterator at position index. Do it AFTER the emplace, to make sure
    // that back() has an element to access.
    auto it = (*framePtr)->operator[](ORIGINAL_FRAME).begin();
    for (std::size_t i = 0; i <= index; ++ i) {

        ++ it;

    }

    (*framePtr)->operator[](ORIGINAL_FRAME).insert(it, frame);

    // If no texture rectangle is given, store the unmodified frame inside the
    // texture rectangle storage as well. If one is given, apply and store.
    if (IntRect() == textureRect) {

        (*framePtr)->operator[](TEXTURE_RECT_FRAME).insert(it, frame);

    } else {

        (*framePtr)->operator[](TEXTURE_RECT_FRAME).insert(it, getIntersection(frame, textureRect));

    }

    return index;

}

//! Checks whether frame and texture rectangle getIntersection.
/*!
* Checks if the given frame getIntersections with the texture rectangle. Returns the
* getIntersectionion. In the case there is no getIntersectionion, an empty frame is
* returned.
* \param frame Frame of animation.
* \param rect Texture rectangle of animation.
* \return Intersecting rectangle as a frame.
*/
Frame FrameRepository::getIntersection(const Frame& frame,
                                 	   const IntRect& rect) {

    // Create temporary rectangle to use getIntersectionion function.
    auto temp = IntRect(0, 0, frame.w, frame.h);
    auto result = IntRect();

    // Check for getIntersectionion and store if there is one.
    temp.intersects(rect, result);

    // Convert to frame.
    Frame resultFrame(frame.x, frame.y, result.width, result.height);

    return resultFrame;

}

//! Replace frame with new one.
/*!
* Replaces frame at position index with new index.
*
* ATTENTION: No range checking for frame.
* \param framePtr Pointer to storage in which frame is.
* \param other Frame which replaces frame at index position.
* \param index Position of the frame which should be replaced.
*/
void FrameRepository::replace(FramesPointer* framePtr, const Frame& other,
                               std::size_t index, const IntRect& rect) {

    // Store frame in original storage and then apply texture rectangle and
    // store.
    (*framePtr)->operator[](ORIGINAL_FRAME).operator[](index) = other;
    if (IntRect() == rect) {

        // No rect to apply.
        (*framePtr)->operator[](TEXTURE_RECT_FRAME).operator[](index) = other;

    } else {

        (*framePtr)->operator[](TEXTURE_RECT_FRAME).operator[](index) = getIntersection(other, rect);

    }

}

//! Applies texture rectangle to all frames in given repository.
/*!
* Applies texture rectangle to all frames currently stores inside the given
* repository and then stores them in the texture rectangle frame storage.
* \param framePtr Pointer to storage of frames which should be used.
* \param textureRect Texture rectangle which should be applied.
*/
void FrameRepository::applyTextureRect(FramesPointer* framePtr,
                                      const IntRect& textureRect) {

    // Iterate through both vectors of frames (they are of the same size) and
    // calculate the texture rectangle for each original frame.
    auto orig_it = (*framePtr)->operator[](ORIGINAL_FRAME).begin();
    auto tex_it = (*framePtr)->operator[](TEXTURE_RECT_FRAME).begin();
    while (orig_it != (*framePtr)->operator[](ORIGINAL_FRAME).end()) {

        *tex_it = getIntersection(*orig_it, textureRect);

        // Increment iterators for next loop run.
        ++ orig_it;
        ++ tex_it;

    }

}

//! Test whether to destruct a frame or not.
/*!
* This function is passed to std::list::remove_if() to be the condition under
* which a frame is removed from the list. If the use count of a frame
* pointer is one, only the std::list refers to it anymore, so it can be
* destructed without any damage.
* \param framePtr Frame pointer to the frame object.
* \return True if std::shared_ptr::use_count() equals 1.
*/
bool FrameRepository::removeFrame(const FramesPointer& framePtr) {

    return 1 == framePtr.use_count();

}

//! Removes all unused frames from the list if needed.
/*!
* This function should be called in any object's destructor which uses frames.
* It basically handles a counter which is increased everytime an object is
* release that had a reference to a frame pointer. Once this counter is half the
*  size of the internal frame list, a function is called to garbage collect all
* unused textures.
*/
void FrameRepository::tidy() {

    ++ mDestructionCount;

	if (mFrames.size() / 2 <= mDestructionCount) {

        mFrames.remove_if(removeFrame);
        mDestructionCount = 0;

	}

}

CLOSE_WO_GFX
