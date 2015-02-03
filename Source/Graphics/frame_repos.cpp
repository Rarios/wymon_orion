// frame_repository.cpp

#include "frame_repos.hpp"
#include <iostream>
#include <cassert>

// Member variables

// ATTENTION: Do NOT change the "operator[]()" calls to just "[]". Implicit
// calls to the overloaded operator generates compiler errors.

//! List holding all frames.
/*!
* At first, it should be an empty list.
*/
std::list<frames_ptr> frame_repository::m_frames;

//! Internal counter of destructed frame holding objects.
/*!
* Holds the number of objects destructed which had a reference to a frame
* pointer.
*/
std::size_t frame_repository::destruct_count = 0 ;

// Member functions

//! Create pointer to frame storing structure.
/*!
* Creates a pointer to a structure for storing frames, which then can be used by
* an animation object to access frames.
*
* NOTE: Since every instance of the animation class only needs one of these
* pointers, this function should be called inside the constructor.
* \param frm_ptr Pointer which will point to frame storing structure.
*/
void frame_repository::create(frames_ptr* frm_ptr) {

    // Create new frame storage and assign pointer for the animation.
    // ATTENTION: Do not use emplace_back() here, it causes problems due to
    // an error while initializing. Since temp is only valid in this scope, it
    // won't cause any errors when dealing with use_count().
/* \todo (lin#9#2014-08-15): The error was, that the intance of the shared_ptr
which has been push backed was not initialized properly.
This is fixed now, maybe try to simplify the code a little
by making some typedefs.

Also try to use emplace_back again. */
	std::vector<frame> temp_vec;
    frames_ptr temp(new std::array<std::vector<frame>, 2>);
	temp->operator[](ORIG_FRM) = temp_vec;
	temp->operator[](TEX_RECT_FRM) = temp_vec;
    m_frames.push_back(temp);
    *frm_ptr = m_frames.back();

}

//! Inserts frame at the back of the repository.
/*!
* Inserts given frame into the repository list at the end. If a texture
* rectangle other than an empty one is given, it is also applied to the frame
* and stored inside.
* \param frm_ptr Pointer to where the frames are stored for the animation.
* \param frm Frame to store.
* \param tex_rect Texture rectangle to apply.
* \return Index where the frame has been inserted.
*/
std::size_t frame_repository::insert(frames_ptr* frm_ptr, const frame& frm,
                                     const sf::IntRect& tex_rect) {

    (*frm_ptr)->operator[](ORIG_FRM).push_back(frm);

    // If no texture rectangle is given, store the unmodified frame inside the
    // texture rectangle storage as well. If one is given, apply and store.
    if (sf::IntRect() == tex_rect) {

        (*frm_ptr)->operator[](TEX_RECT_FRM).push_back(frm);

    } else {

        (*frm_ptr)->operator[](TEX_RECT_FRM).push_back(intersect(frm, tex_rect));

    }

    return ((*frm_ptr)->operator[](ORIG_FRM).size() - 1);

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
* \param frm_ptr Pointer to where the frames are stored for the animation.
* \param frm Frame to store.
* \param index Index of where to store it.
* \param tex_rect Texture rectangle to apply.
* \return Index where the frame has been inserted (just returns index).
*/
std::size_t frame_repository::insert(frames_ptr* frm_ptr, const frame& frm,
                                     std::size_t index,
                                     const sf::IntRect& tex_rect) {

    // Get iterator at position index. Do it AFTER the emplace, to make sure
    // that back() has an element to access.
    auto it = (*frm_ptr)->operator[](ORIG_FRM).begin();
    for (std::size_t i = 0; i <= index; ++ i) {

        ++ it;

    }

    (*frm_ptr)->operator[](ORIG_FRM).insert(it, frm);

    // If no texture rectangle is given, store the unmodified frame inside the
    // texture rectangle storage as well. If one is given, apply and store.
    if (sf::IntRect() == tex_rect) {

        (*frm_ptr)->operator[](TEX_RECT_FRM).insert(it, frm);

    } else {

        (*frm_ptr)->operator[](TEX_RECT_FRM).insert(it, intersect(frm, tex_rect));

    }

    return index;

}

//! Checks whether frame and texture rectangle intersect.
/*!
* Checks if the given frame intersects with the texture rectangle. Returns the
* intersection. In the case there is no intersection, an empty frame is
* returned.
* \param frm Frame of animation.
* \param rect Texture rectangle of animation.
* \return Intersecting rectangle as a frame.
*/
frame frame_repository::intersect(const frame& frm,
                                               const sf::IntRect& rect) {

    // Create temporary rectangle to use intersection function.
    auto temp = sf::IntRect(0, 0, frm.w, frm.h);
    auto result = sf::IntRect();

    // Check for intersection and store if there is one.
    temp.intersects(rect, result);

    // Convert to frame.
    frame res_frame(frm.x, frm.y, result.width, result.height);

    return res_frame;

}

//! Replace frame with new one.
/*!
* Replaces frame at position index with new index.
*
* ATTENTION: No range checking for frame.
* \param frm_ptr Pointer to storage in which frame is.
* \param other Frame which replaces frame at index position.
* \param index Position of the frame which should be replaced.
*/
void frame_repository::replace(frames_ptr* frm_ptr, const frame& other,
                               std::size_t index, const sf::IntRect& rect) {

    // Store frame in original storage and then apply texture rectangle and
    // store.
    (*frm_ptr)->operator[](ORIG_FRM).operator[](index) = other;
    if (sf::IntRect() == rect) {

        // No rect to apply.
        (*frm_ptr)->operator[](TEX_RECT_FRM).operator[](index) = other;

    } else {

        (*frm_ptr)->operator[](TEX_RECT_FRM).operator[](index) = intersect(other, rect);

    }

}

//! Applies texture rectangle to all frames in given repository.
/*!
* Applies texture rectangle to all frames currently stores inside the given
* repository and then stores them in the texture rectangle frame storage.
* \param frm_ptr Pointer to storage of frames which should be used.
* \param tex_rect Texture rectangle which should be applied.
*/
void frame_repository::apply_tex_rect(frames_ptr* frm_ptr,
                                      const sf::IntRect& tex_rect) {

    // Iterate through both vectors of frames (they are of the same size) and
    // calculate the texture rectangle for each original frame.
    auto orig_it = (*frm_ptr)->operator[](ORIG_FRM).begin();
    auto tex_it = (*frm_ptr)->operator[](TEX_RECT_FRM).begin();
    while (orig_it != (*frm_ptr)->operator[](ORIG_FRM).end()) {

        *tex_it = intersect(*orig_it, tex_rect);

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
* \param frm_ptr Frame pointer to the frame object.
* \return True if std::shared_ptr::use_count() equals 1.
*/
bool frame_repository::remove_frame(const frames_ptr& frm_ptr) {

    return 1 == frm_ptr.use_count();

}

//! Removes all unused frames from the list if needed.
/*!
* This function should be called in any object's destructor which uses frames.
* It basically handles a counter which is increased everytime an object is
* release that had a reference to a frame pointer. Once this counter is half the
*  size of the internal frame list, a function is called to garbage collect all
* unused textures.
*/
void frame_repository::tidy() {

    ++ destruct_count;

	if (m_frames.size() < destruct_count) {

        m_frames.remove_if(remove_frame);
        destruct_count = 0;

	}

}
