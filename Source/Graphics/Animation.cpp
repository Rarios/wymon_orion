// Animation
// Animation.cpp

#include <cmath>
#include <iostream>
#include "Animation.hpp"

OPEN_WO_GFX

/* 
* ATTENTION: The function "calculateMaximumSize()" uses the "std::isless()" function to
* compare to floating point variables. Since normal comparison can cause a lot
* of errors, the "std::isless()" function has been chosen to make an epsilon
* based comparison of the two values. I am not quite sure that this function
* actually does what I want it to, so if something goes wrong along the way with
* the code using the "getMaximumSize()" function, this part of the program should
* definitely be checked.
*/

//! Default constructor.
/*!
* Creates an empty Animation with no source texture. Additionally, it reserves
* space for internal vector holding pointers to the frames.
*/
Animation::Animation() : mMaximumSize() {

    mTexture = nullptr;

    mFrames = nullptr;
    FrameRepository::initialize(&mFrames);

	mTextureRect = IntRect();
	/*std::cout << "Initialized mTextureRect to: \n";
	std::cout << "\twidth = " << mTextureRect.width;
	std::cout << "\n\theight = " << mTextureRect.height << std::endl;*/

    // Since the index is unsigned, this will assign the highest value, so now
    // the next time the frame is rendered, it will produce an overflow due to
    // increasing the index, which will let it start with 0.
	mIndex = -1;

}

//! Texture constructor.
/*!
* Constructs Animation with given texture.
* \param texture Texture which will be used for the Animation.
*/
Animation::Animation(const TexturePointer& texture) : mMaximumSize() {

    mTexture = nullptr;

    mFrames = nullptr;
    FrameRepository::initialize(&mFrames);

	mTextureRect = IntRect();
	setTexture(texture);

    // Refer to default constructor for explenation.
	mIndex = -1;

}

//! Texture constructor with texture rectangle.
/*!
* Constructs Animation with given texture and assigns texture rectangle, which
* determines the part of the Animation frames which is shown.
* \param texture Texture which will be used for the Animation.
* \param rect Texture rectangle for displayed part of Animation.
*/
Animation::Animation(const TexturePointer& texture, const IntRect& rect) : 
					 mMaximumSize() {

    mTexture = nullptr;
    setTexture(texture);

    mFrames = nullptr;
    FrameRepository::initialize(&mFrames);

	mTextureRect = IntRect();
	setTextureRect(rect);

	// Refer to default constructor for explenation.
	mIndex = -1;

}

//! Default destructor.
Animation::~Animation() {

    FrameRepository::tidy();

}

//! Insert frame at the end.
/*!
* Inserts a frame at the end of the Animation.
* \param frame Frame to be inserted at the end of the Animation.
* \param rect Optional texture rectangle for Animation frame.
* \return Index (position) where the frame has been inserted.
*/
std::size_t Animation::insert(const Frame& frame, IntRect rect) {

	computeMaximumSize(Vector2f(frame.w, frame.h));

    // If no textre rectangle is given, use internal.
    if (IntRect() == rect) {

        return FrameRepository::insert(&mFrames, frame, mTextureRect);

    } else {

        return FrameRepository::insert(&mFrames, frame, rect);

    }

}

//! Insert frame at the end.
/*!
* Inserts a frame at the index position of the Animation.
*
* ATTENTION: No range checking for index.
*
* ATTENTION: Use with caution, because this function is linear in the size of
* the index, O(index), so it may slow down the program if index is large.
* \param frame Frame to be inserted at the end of the Animation.
* \param index Index where to insert the frame.
* \param rect Optional texture rectangle for Animation frame.
* \return Index (position) where the frame has been inserted (returns index).
*/
std::size_t Animation::insert(const Frame& frame, std::size_t index,
                              IntRect rect) {

	computeMaximumSize(Vector2f(frame.w, frame.h));

    // If no textre rectangle is given, use internal.
    if (IntRect() == rect) {

        return FrameRepository::insert(&mFrames, frame, index, mTextureRect);

    } else {

        return FrameRepository::insert(&mFrames, frame, index, rect);

    }

}

//! Insert frames inside frame group at end.
/*!
* Calculates frames which are inside the frame group and stores them at the end
* of the frame storing structure.
* \param frameGroup Frame group holding all frames which should be inserted.
* \param rect Texture rectangle which is applied to the frames.
* \return Index position of the first inserted frame of the group.
*/
std::size_t Animation::insert(const FrameGroup& frameGroup, IntRect rect) {

    // If no textre rectangle is given, use internal.
    auto tempTextureRect = ((IntRect() == rect) ? mTextureRect : rect);

    // Calculate how many rows and colums are inside the frame group.
    std::size_t rows = frameGroup.sh / frameGroup.h;
    std::size_t cols = frameGroup.sw / frameGroup.w;

    // Index of the first frame of the frame group which is inserted.
    // Will have an offset of the number of inserted frames, which is basically
    // rows * cols.
    std::size_t index{};

    // Calculate and iterate through the frames inside the group.
    for (std::size_t i = 0; i < rows; ++ i) {

        for (std::size_t j = 0; j < cols; ++ j) {

            // Create temporary frame based on the current row and column.
            auto tempFrame = Frame(frameGroup.x + j * frameGroup.w,
                                    frameGroup.y + i * frameGroup.h,
                                    frameGroup.w, frameGroup.h);

			computeMaximumSize(Vector2f(tempFrame.w, tempFrame.h));

			/*std::cout << "Now inserting frame with values: " << std::endl;
			std::cout << "\tx = " << temp_frame.x << std::endl;
			std::cout << "\ty = " << temp_frame.y << std::endl;
			std::cout << "\tw = " << temp_frame.w << std::endl;
			std::cout << "\th = " << temp_frame.h << std::endl;
			std::cin.get();*/

            index = FrameRepository::insert(&mFrames, tempFrame,
                                             tempTextureRect);

        }

    }

    // Remove offset before returning.
    return (index - rows * cols);

}

//! Insert frames inside frame group at given position.
/*!
* Calculates frames which are inside the frame group and stores them at the
* given position inside the frame storing structure.
*
* ATTENTION: No range checking for index.
*
* ATTENTION: Use with caution, because this function is linear in the size of
* the index, O(index), so it may slow down the program if index is large.
* \param frameGroup Frame group holding all frames which should be inserted.
* \param index Index where to insert the first frame of the group.
* \param rect Texture rectangle which is applied to the frames.
* \return Index position of the first inserted frame of the group.
*/
std::size_t Animation::insert(const FrameGroup& frameGroup, std::size_t index,
                              IntRect rect) {

    // If no textre rectangle is given, use internal.
    auto tempTextureRect = ((IntRect() == rect) ? mTextureRect : rect);

    // Calculate how many rows and colums are inside the frame group.
    std::size_t rows = frameGroup.sh / frameGroup.h;
    std::size_t cols = frameGroup.sw / frameGroup.w;

    // Save index so it can be returned later.
    auto firstIndex = index;

    // Calculate and iterate through the frames inside the group.
    for (std::size_t i = 0; i < rows; ++ i) {

        for (std::size_t j = 0; j < cols; ++ j) {

            // Create temporary frame based on the current row and column.
            auto tempFrame = Frame(frameGroup.x + j * frameGroup.w,
                                    frameGroup.y + i * frameGroup.h,
                                    frameGroup.w, frameGroup.h);
			
			computeMaximumSize(Vector2f(tempFrame.w, tempFrame.h));

            index = FrameRepository::insert(&mFrames, tempFrame,
                                             index, tempTextureRect);

            // Increase index for every frames so they are added consecutively.
            ++ index;

        }

    }

    return firstIndex;

}

//! Set the texture rectangle, which the Animation will display.
/*!
* The texture rect is useful in cases in which not the whole,
* but rather a part of the frame should be drawn. By default,
* the rectangle is equal to the size of the frame.
* \param rectangle Rectangle defining the visible region of the texture.
*/
void Animation::setTextureRect(const IntRect& rect)
{

    if (rect != mTextureRect)
    {

        mTextureRect = rect;
		FrameRepository::applyTextureRect(&mFrames, mTextureRect);
        updatePosition();
        updateTextureCoordinates();

    }

}

//! Replace Animation frame.
/*!
* Replace Animation frame at the given position with new frame.
* ATTENTION: The index is not range checked, if the index is higher than the
* number of available frames, the behaviour is undefined.
* \param index Index of the frame to replace.
* \other New frame.
*/
void Animation::replace(std::size_t index, const Frame& other) {

	// Change the original frame and calculate new texture frame.
	mFrames->operator[](ORIGINAL_FRAME).operator[](index) = other;
	
	// Frame with applied texture rectangle.
	Frame tempFrame;

	// If no texture rectangle is given, use plain frame; if one is given,
	// calculate the intersection and use it as frame.
	if (IntRect() == mTextureRect) {
		
		tempFrame = other;
	
	} else {
	
		tempFrame = FrameRepository::getIntersection(other, mTextureRect);
	
	}

	computeMaximumSize(Vector2f(tempFrame.w, tempFrame.h));

	mFrames->operator[](TEXTURE_RECT_FRAME).operator[](index)  = tempFrame;

}

//! Modify the size of a frame.
/*!
* Modify the size of the frame at the index-th position.
* \param index Index of frame to modify.
* \param size New size for frame.
*/
void Animation::modifySize(std::size_t index, const Vector2i& size) {

	mFrames->operator[](ORIGINAL_FRAME).operator[](index).w = size.x;
	mFrames->operator[](ORIGINAL_FRAME).operator[](index).h = size.y;

	// Save current frame.
	auto currentFrame = mFrames->operator[](TEXTURE_RECT_FRAME).operator[](index);
	currentFrame.w = size.x;
	currentFrame.h = size.y;
	Frame newFrame;
	
	// If no texture rectangle is given, use plain frame; if one is given,
	// calculate the intersection and use it as frame.
	if (IntRect() == mTextureRect) {
	
		newFrame = currentFrame;
	
	} else {
	
		newFrame = FrameRepository::getIntersection(currentFrame, mTextureRect);
	
	}

	computeMaximumSize(Vector2f(newFrame.w, newFrame.h));

	mFrames->operator[](TEXTURE_RECT_FRAME).operator[](index) = newFrame;

}

//! Modify the position of a frame.
/*!
* Modify the position on the sprite sheet of the frame at the index-th position.
* \param index Index of frame to modify.
* \param position New position for frame.
*/
void Animation::modifyPosition(std::size_t index, const Vector2i& position) {

	mFrames->operator[](ORIGINAL_FRAME).operator[](index).x = position.x;
	mFrames->operator[](ORIGINAL_FRAME).operator[](index).y = position.y;

	// The position of a frame within the sprite sheet is not taken into
	// account when the intersection of a frame and the texture rectangle is
	// calculated, thus no new intersection calculation is needed. The values
	// can be overwritten.
	mFrames->operator[](TEXTURE_RECT_FRAME).operator[](index).x = position.x;
	mFrames->operator[](TEXTURE_RECT_FRAME).operator[](index).y = position.y;

}

//! Render next Animation frame.
/*!
* Renders the next frame of the Animation.
* \return Index of frame which is rendered.
*/
std::size_t Animation::render() {

    // Check if already last frame.
    if ((mFrames->operator[](TEXTURE_RECT_FRAME).size() - 1) == mIndex) {

        mIndex = 0;

    } else {

        ++ mIndex;

    }

	//std::cout << "Currently rendering frame " << mIndex << std::endl;

    updatePosition();
    updateTextureCoordinates();

    return mIndex;

}

//! Render frame with given index.
/*!
* Renders the frame which is at the position of the index. No range checking for
* the index.
* \return Index of frame which is rendered.
*/
std::size_t Animation::render(std::size_t index) {

    mIndex = index;
    updatePosition();
    updateTextureCoordinates();

    return mIndex;

}

//! Get the local boundaries rectangle.
/*!
* The returned rectangle is in local coordinates. This means that
* it ignores the transformations (translation, rotation, scale, ...)
* that are applied to the entity. To put it in other words, the
* bounds of the entity in the entitiy's coordinate system are returned, for the
* current frame.
* \return Local boundaries rectangle for current frame.
*/
FloatRect Animation::getLocalBounds() const {

	float width{};
	float height{};

	// If frame list is empty, use texture rectangle, if not, use the current
	// frame.
	if (0 == mFrames->operator[](ORIGINAL_FRAME).size()) {
	
		//std::cout << "Local boundaries from mTextureRect";
		width = static_cast<float>(std::abs(mTextureRect.width));
		height = static_cast<float>(std::abs(mTextureRect.height));
	
	} else {

		// Even if the frame list is not empty, there can still be a problem
		// width the index of the current frame. Since "mIndex" is initialized
		// to "-1", causing an overload to the highest integer value possible,
		// the index is almost always out of range. The result is a set of
		// garbage values for the local boundaries.
		// In order to solve this problem, the following assumtions are made:
		// -) If the "render()" function has not yet been called, then the
		// index is still at its init value. Since the next frame that is going
		// to be rendered is the 0th frame, the temporary index is set to 0.
		// With this, the user can get the boundaries of the next/current frame
		// to draw.
		// -) The "render()" function has already been called, so the index
		// variable has a valid value. This value should be used to get the
		// local boundaries, so the user can access the boundaries of the
		// currently drawn frame (by this I mean the frame that gets drawn on
		// the screen with the next call of "draw()".
		std::size_t tempIndex{};
		if (mFrames->operator[](ORIGINAL_FRAME).size() <= mIndex) {
		
			tempIndex = 0;
		
		} else {
		
			tempIndex = mIndex;
		
		}
	
		auto textureFrame = 
		mFrames->operator[](TEXTURE_RECT_FRAME).operator[](tempIndex);

		/*std::cout << "Local boundaries from TEXTURE_RECT_FRAME\n";
		std::cout << "Index is at position " << mIndex;*/
    	width = static_cast<float>(std::abs(textureFrame.w)) ;
    	height = static_cast<float>(std::abs(textureFrame.h)) ;

		/*std::cout << "\nFrame boundaries: \n";
		std::cout << "\t width = " << width << "\n";
		std::cout << "\t height = " << height << std::endl;
		std::cin.get();*/

	}

	/*std::cout << "\nLocal boundaries: \n";
	std::cout << "\t width = " << width << "\n";
	std::cout << "\t height = " << height << std::endl;*/

    return FloatRect(0.f, 0.f, width, height) ;

}

//! Return maximum local size of Animation.
/*!
* Return the size of the biggest frame stored for the Animation, which is
* the largest possible size for the Animation, if no transformation is taken
* into account. It is actually the biggest which can be returned by the
* obj_size() function.
* \return Maximum size of the Animation, without transformations.
*/
Vector2f Animation::getMaximumObjectSize() {

	return mMaximumSize;

}

//! Return maximum global size of Animation.
/*!
* Return the size of the biggest frame stored for the Animation, which is
* the largest possible size for the Animation, with the transformation is taken
* into account. It is actually the biggest which can be returned by the size()
* function.
* \return Maximum size of the Animation, with transformations.
*/
Vector2f Animation::getMaximumSize() {

	auto bounds = getLocalBounds();
	FloatRect maximumSizeRect(bounds.top, bounds.left, 
								mMaximumSize.x, mMaximumSize.y);

	auto transformedRect = getTransform().transformRect(maximumSizeRect);

	return Vector2f(transformedRect.width, transformedRect.height);
}

//! Return number of frames.
/*!
* Return the number of frames currently stored for the Animation.
* \return Number of frames for the Animation.
*/
std::size_t Animation::getFramesCount() {

	return mFrames->operator[](ORIGINAL_FRAME).size();

}

//! Calculate maximum size for Animation.
/*!
* Compares current maximum size of the Animation frames with the given
* parameter and sets a new size if necessary.
*
* NOTE: This function is called in every member function which modifies or adds
* a frame, so that the maximum frame size is always updated.
* \param size Size of added/modified frame to compare with.
*/
void Animation::computeMaximumSize(const Vector2f& size) {

	// ATTENTION: Although the code could be written more compact with the "?"
	// operator, the "?" operator would require an assignment after the
	// comparison of the two values, even if size is not bigger than max_size.
	// Using the "if" statements, this sometimes unnecessary assignment can be
	// avoided.
	if (std::isless(mMaximumSize.x, size.x)) {
	
		mMaximumSize.x = size.x;
	
	}

	if (std::isless(mMaximumSize.y, size.y)) {
	
		mMaximumSize.y = size.y;
	
	}

}

//! Update the vertices' texture coordinates.
/*!
* The coordinates are retrieved by the current frame and
* assigned anticlockwise. If there is any texture rectangle
* in use, it is taken in account.
*/
void Animation::updateTextureCoordinates() {

	// Create variables so they are available in the whole function scope.
	float left{};
    float right{};
    float top{};
    float bottom{};

	// Check if there are already frames for the Animation. If not, then the
	// texture coords should be set to the texture rectangle, as it is done in
	// the sprite class.
	if (mFrames->operator[](TEXTURE_RECT_FRAME).size() == 0) {
	
		left = static_cast<float>(mTextureRect.left);
    	right = left + mTextureRect.width;
    	top = static_cast<float>(mTextureRect.top);
    	bottom = top + mTextureRect.height;

	} else {

		left = static_cast<float>(mFrames->operator[](TEXTURE_RECT_FRAME).operator[](mIndex).x);
		right = left + mFrames->operator[](TEXTURE_RECT_FRAME).operator[](mIndex).w;
		top = static_cast<float>(mFrames->operator[](TEXTURE_RECT_FRAME).operator[](mIndex).y);
		bottom = top + mFrames->operator[](TEXTURE_RECT_FRAME).operator[](mIndex).h;

	}

	/*std::cout << "Frame left = " << left << std::endl;
	std::cout << "Frame top = " << top << std::endl;
	std::cout << "Frame right = " << right << std::endl;
	std::cout << "Frame bottom = " << bottom << std::endl;
	std::cin.get();*/

	// Coordinates, defined anticlockwise.
    mVertices[0].texCoords = Vector2f(left, top);
    mVertices[1].texCoords = Vector2f(left, bottom);
    mVertices[2].texCoords = Vector2f(right, bottom);
    mVertices[3].texCoords = Vector2f(right, top);

}

//! Draw Animation to render target.
/*!
* NOTE: The texture rectangle is included in the vertecies.
* \param target Render target to draw to.
* \param states Current render states.
*/
void Animation::draw(RenderTarget& target, RenderStates states) const {

    if (nullptr != mTexture) {

        states.transform *= getTransform();
        states.texture = mTexture.get();
        target.draw(mVertices, 4, Quads, states);

    }

}

CLOSE_WO_GFX
