// frame - Single animation frame.
// frame_group - Group of animation frames.
// frame.hpp

#ifndef _FRAME_
#define _FRAME_

#include <SFML/Graphics.hpp>
#include <utility>

//! Single animation frame.
/*!
* This class represents a single animation frame, defined by a position on the
* texture and its size.
*/
class frame {

public:

    // Member variables.

    //! X-coordinate, left offset.
    int x;
    //! Y-coordinate, top offset.
    int y;
    //! Width of frame.
    int w;
    //! Height of frame.
    int h;

    // Member functions.

    //! Default constructor.
    frame() : x(0), y(0), w(0), h(0) {
    }

    //! Value constructor.
    /*!
    * Initializes frame with given parameters.
    * \param x X-coordinate, left offset.
    * \param y Y-coordinate, top offset.
    * \param width Width of frame.
    * \param height Height of frame.
    */
    frame(int x, int y, int width, int height) : x(x), y(y),
          w(width), h(height) {
    }

    //! Value pair constructor.
    /*!
    * Initializes frame with two value pairs, position and size.
    * \param pos X- and y-coordinate of frame.
    * \param size Size of frame.
    */
    frame(sf::Vector2i pos, sf::Vector2i size) : x(pos.x), y(pos.y),
          w(size.x), h(size.y) {
    }

    //! Copy constructor.
    /*!
    * Copy constructs frame from other frame.
    * \param other Frame from which to copy construct.
    */
    frame(const frame& other) : x(other.x), y(other.y), w(other.w), h(other.h) {
    }

    //! Move constructor.
    /*!
    * Move constructs frame from other frame
    * \param other Frame from which to move construct.
    */
    frame(frame&& other) : x(std::move(other.x)), y(std::move(other.y)),
          w(std::move(other.w)), h(std::move(other.h)) {
    }

    //! Default destructor.
    ~frame() {
    }

    //! Copy assignment.
    void operator=(const frame& other) {

        this->x = other.x;
        this->y = other.y;
        this->w = other.w;
        this->h = other.h;

    }

};

//! Group of same size animation frames.
/*!
* This class represents a group of frames which are all of the same size. First
* it defines the general frame size, second it defines a section, with position
* and size, on the texture, where all the frames are located. The general frame
* size is then used to split up the section on the texture into single frames.
*/
class frame_group {

public:

    // Member variables.

    //! X-coordinate of section, left offset.
    int x;
    //! Y-coordinate of section, top offset.
    int y;
    //! Section width.
    /*!
    * Width of the section where the frames are located.
    */
    int sw;
    //! Section height.
    /*!
    * Height of the section where the frames are located.
    */
    int sh;
    //! General frame width.
    int w;
    //! General frame height.
    int h;

    // Member functions.

    //! Default constructor.
    frame_group() : x(0), y(0), sw(0), sh(0), w(0), h(0) {
    }

    //! Value constructor.
    /*!
    * Initializes group of frames with given parameters.
    * \param x X-coordinate of section, left offset.
    * \param y Y-coordinate of section, top offset.
    * \param sWidth Width of the section.
    * \param sHeight Height of the section.
    * \param width General frame width.
    * \param height General frame height.
    */
    frame_group(int x, int y, int sWidth, int sHeight, int width, int height) :
                x(x), y(y), sw(sWidth), sh(sHeight), w(width), h(height) {
    }

    //! Value pair constructor.
    /*!
    * Initializes frame with two value pairs, position and size.
    * \param pos X- and y-coordinate of the section.
    * \param size Size of the section.
    * \param frameSize General frame size.
    */
    frame_group(sf::Vector2i pos, sf::Vector2i size, sf::Vector2i frameSize) :
                x(pos.x), y(pos.y), sw(size.x), sh(size.y), w(frameSize.x),
                h(frameSize.y) {
    }

    //! Copy constructor.
    /*!
    * Copy constructs frame group from other frame group.
    * \param other Frame group from which to copy construct.
    */
    frame_group(const frame_group& other) : x(other.x), y(other.y),
                sw(other.sw), sh(other.sh), w(other.w), h(other.h) {
    }

    //! Move constructor.
    /*!
    * Move constructs frame group from other frame group.
    * \param other Frame group from which to move construct.
    */
    frame_group(frame_group&& other) : x(std::move(other.x)),
                y(std::move(other.y)), sw(std::move(other.sw)),
                sh(std::move(other.sh)), w(std::move(other.w)),
                h(std::move(other.h)) {
    }

    //! Default destructor.
    ~frame_group() {
    }

    //! Copy assignment.
    void operator=(const frame_group& other) {

        this->x = other.x;
        this->y = other.y;
        this->sw = other.sw;
        this->sh = other.sh;
        this->w = other.w;
        this->h = other.h;

    }

};

#endif // _FRAME_
