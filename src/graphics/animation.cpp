// Animation
// animation.cpp

#include "animation.hpp"
#include <cmath>
#include <iostream>

/* 
* ATTENTION: The function "calc_max_size()" uses the "std::isless()" function to
* compare to floating point variables. Since normal comparison can cause a lot
* of errors, the "std::isless()" function has been chosen to make an epsilon
* based comparison of the two values. I am not quite sure that this function
* actually does what I want it to, so if something goes wrong along the way with
* the code using the "max_size()" function, this part of the program should
* definitely be checked.
*/

//! Default constructor.
/*!
* Creates an empty animation with no source texture. Additionally, it reserves
* space for internal vector holding pointers to the frames.
*/
animation::animation() : m_max_size() {

    m_texture = nullptr;

    m_frames = nullptr;
    frame_repository::create(&m_frames);

	mTexRect = sf::IntRect();
	/*std::cout << "Initialized mTexRect to: \n";
	std::cout << "\twidth = " << mTexRect.width;
	std::cout << "\n\theight = " << mTexRect.height << std::endl;*/

    // Since the index is unsigned, this will assign the highest value, so now
    // the next time the frame is rendered, it will produce an overflow due to
    // increasing the index, which will let it start with 0.
	m_index = -1;

}

//! Texture constructor.
/*!
* Constructs animation with given texture.
* \param texture Texture which will be used for the animation.
*/
animation::animation(const sf::Texture& texture) : m_max_size() {

    m_texture = nullptr;

    m_frames = nullptr;
    frame_repository::create(&m_frames);

	mTexRect = sf::IntRect();
	setTexture(texture);

    // Refer to default constructor for explenation.
	m_index = -1;

}

//! Texture constructor with texture rectangle.
/*!
* Constructs animation with given texture and assigns texture rectangle, which
* determines the part of the animation frames which is shown.
* \param texture Texture which will be used for the animation.
* \param rect Texture rectangle for displayed part of animation.
*/
animation::animation(const sf::Texture& texture, const sf::IntRect& rect) : 
					 m_max_size() {

    m_texture = nullptr;
    setTexture(texture);

    m_frames = nullptr;
    frame_repository::create(&m_frames);

	mTexRect = sf::IntRect();
	setTexRect(rect);

	// Refer to default constructor for explenation.
	m_index = -1;

}

//! Default destructor.
animation::~animation() {

    frame_repository::tidy();

}

//! Insert frame at the end.
/*!
* Inserts a frame at the end of the animation.
* \param frm Frame to be inserted at the end of the animation.
* \param rect Optional texture rectangle for animation frame.
* \return Index (position) where the frame has been inserted.
*/
std::size_t animation::insert(const frame& frm, sf::IntRect rect) {

	calc_max_size(sf::Vector2f(frm.w, frm.h));

    // If no textre rectangle is given, use internal.
    if (sf::IntRect() == rect) {

        return frame_repository::insert(&m_frames, frm, mTexRect);

    } else {

        return frame_repository::insert(&m_frames, frm, rect);

    }

}

//! Insert frame at the end.
/*!
* Inserts a frame at the index position of the animation.
*
* ATTENTION: No range checking for index.
*
* ATTENTION: Use with caution, because this function is linear in the size of
* the index, O(index), so it may slow down the program if index is large.
* \param frm Frame to be inserted at the end of the animation.
* \param index Index where to insert the frame.
* \param rect Optional texture rectangle for animation frame.
* \return Index (position) where the frame has been inserted (returns index).
*/
std::size_t animation::insert(const frame& frm, std::size_t index,
                              sf::IntRect rect) {

	calc_max_size(sf::Vector2f(frm.w, frm.h));

    // If no textre rectangle is given, use internal.
    if (sf::IntRect() == rect) {

        return frame_repository::insert(&m_frames, frm, index, mTexRect);

    } else {

        return frame_repository::insert(&m_frames, frm, index, rect);

    }

}

//! Insert frames inside frame group at end.
/*!
* Calculates frames which are inside the frame group and stores them at the end
* of the frame storing structure.
* \param frm_grp Frame group holding all frames which should be inserted.
* \param rect Texture rectangle which is applied to the frames.
* \return Index position of the first inserted frame of the group.
*/
std::size_t animation::insert(const frame_group& frm_grp, sf::IntRect rect) {

    // If no textre rectangle is given, use internal.
    auto temp_tex_rect = ((sf::IntRect() == rect) ? mTexRect : rect);

    // Calculate how many rows and colums are inside the frame group.
    std::size_t rows = frm_grp.sh / frm_grp.h;
    std::size_t cols = frm_grp.sw / frm_grp.w;

    // Index of the first frame of the frame group which is inserted.
    // Will have an offset of the number of inserted frames, which is basically
    // rows * cols.
    std::size_t index{};

    // Calculate and iterate through the frames inside the group.
    for (std::size_t i = 0; i < rows; ++ i) {

        for (std::size_t j = 0; j < cols; ++ j) {

            // Create temporary frame based on the current row and column.
            auto temp_frame = frame(frm_grp.x + j * frm_grp.w,
                                    frm_grp.y + i * frm_grp.h,
                                    frm_grp.w, frm_grp.h);

			calc_max_size(sf::Vector2f(temp_frame.w, temp_frame.h));

			/*std::cout << "Now inserting frame with values: " << std::endl;
			std::cout << "\tx = " << temp_frame.x << std::endl;
			std::cout << "\ty = " << temp_frame.y << std::endl;
			std::cout << "\tw = " << temp_frame.w << std::endl;
			std::cout << "\th = " << temp_frame.h << std::endl;
			std::cin.get();*/

            index = frame_repository::insert(&m_frames, temp_frame,
                                             temp_tex_rect);

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
* \param frm_grp Frame group holding all frames which should be inserted.
* \param index Index where to insert the first frame of the group.
* \param rect Texture rectangle which is applied to the frames.
* \return Index position of the first inserted frame of the group.
*/
std::size_t animation::insert(const frame_group& frm_grp, std::size_t index,
                              sf::IntRect rect) {

    // If no textre rectangle is given, use internal.
    auto temp_tex_rect = ((sf::IntRect() == rect) ? mTexRect : rect);

    // Calculate how many rows and colums are inside the frame group.
    std::size_t rows = frm_grp.sh / frm_grp.h;
    std::size_t cols = frm_grp.sw / frm_grp.w;

    // Save index so it can be returned later.
    auto first_index = index;

    // Calculate and iterate through the frames inside the group.
    for (std::size_t i = 0; i < rows; ++ i) {

        for (std::size_t j = 0; j < cols; ++ j) {

            // Create temporary frame based on the current row and column.
            auto temp_frame = frame(frm_grp.x + j * frm_grp.w,
                                    frm_grp.y + i * frm_grp.h,
                                    frm_grp.w, frm_grp.h);
			
			calc_max_size(sf::Vector2f(temp_frame.w, temp_frame.h));

            index = frame_repository::insert(&m_frames, temp_frame,
                                             index, temp_tex_rect);

            // Increase index for every frames so they are added consecutively.
            ++ index;

        }

    }

    return first_index;

}

//! Set the texture rectangle, which the animation will display.
/*!
* The texture rect is useful in cases in which not the whole,
* but rather a part of the frame should be drawn. By default,
* the rectangle is equal to the size of the frame.
* \param rectangle Rectangle defining the visible region of the texture.
*/
void animation::setTexRect(const sf::IntRect& rect)
{

    if (rect != mTexRect)
    {

        mTexRect = rect ;
		frame_repository::apply_tex_rect(&m_frames, mTexRect);
        updatePos() ;
        updateTexCoords() ;

    }

}

//! Replace animation frame.
/*!
* Replace animation frame at the given position with new frame.
* ATTENTION: The index is not range checked, if the index is higher than the
* number of available frames, the behaviour is undefined.
* \param index Index of the frame to replace.
* \other New frame.
*/
void animation::replace(std::size_t index, const frame& other) {

	// Change the original frame and calculate new texture frame.
	m_frames->operator[](ORIG_FRM).operator[](index) = other;
	
	// Frame with applied texture rectangle.
	frame tmp_frm;

	// If no texture rectangle is given, use plain frame; if one is given,
	// calculate the intersection and use it as frame.
	if (sf::IntRect() == mTexRect) {
		
		tmp_frm = other;
	
	} else {
	
		tmp_frm = frame_repository::intersect(other, mTexRect);
	
	}

	calc_max_size(sf::Vector2f(tmp_frm.w, tmp_frm.h));

	m_frames->operator[](TEX_RECT_FRM).operator[](index)  = tmp_frm;

}

//! Modify the size of a frame.
/*!
* Modify the size of the frame at the index-th position.
* \param index Index of frame to modify.
* \param size New size for frame.
*/
void animation::mod_size(std::size_t index, const sf::Vector2i& size) {

	m_frames->operator[](ORIG_FRM).operator[](index).w = size.x;
	m_frames->operator[](ORIG_FRM).operator[](index).h = size.y;

	// Save current frame.
	auto cur_frm = m_frames->operator[](TEX_RECT_FRM).operator[](index);
	cur_frm.w = size.x;
	cur_frm.h = size.y;
	frame new_frm;
	
	// If no texture rectangle is given, use plain frame; if one is given,
	// calculate the intersection and use it as frame.
	if (sf::IntRect() == mTexRect) {
	
		new_frm = cur_frm;
	
	} else {
	
		new_frm = frame_repository::intersect(cur_frm, mTexRect);
	
	}

	calc_max_size(sf::Vector2f(new_frm.w, new_frm.h));

	m_frames->operator[](TEX_RECT_FRM).operator[](index) = new_frm;

}

//! Modify the position of a frame.
/*!
* Modify the position on the sprite sheet of the frame at the index-th position.
* \param index Index of frame to modify.
* \param size New position for frame.
*/
void animation::mod_pos(std::size_t index, const sf::Vector2i& pos) {

	m_frames->operator[](ORIG_FRM).operator[](index).x = pos.x;
	m_frames->operator[](ORIG_FRM).operator[](index).y = pos.y;

	// The position of a frame within the sprite sheet is not taken into
	// account when the intersection of a frame and the texture rectangle is
	// calculated, thus no new intersection calculation is needed. The values
	// can be overwritten.
	m_frames->operator[](TEX_RECT_FRM).operator[](index).x = pos.x;
	m_frames->operator[](TEX_RECT_FRM).operator[](index).y = pos.y;

}

//! Render next animation frame.
/*!
* Renders the next frame of the animation.
* \return Index of frame which is rendered.
*/
std::size_t animation::render() {

    // Check if already last frame.
    if ((m_frames->operator[](TEX_RECT_FRM).size() - 1) == m_index) {

        m_index = 0;

    } else {

        ++ m_index;

    }

	//std::cout << "Currently rendering frame " << m_index << std::endl;

    updatePos();
    updateTexCoords();

    return m_index;

}

//! Render frame with given index.
/*!
* Renders the frame which is at the position of the index. No range checking for
* the index.
* \return Index of frame which is rendered.
*/
std::size_t animation::render(std::size_t index) {

    m_index = index;
    updatePos();
    updateTexCoords();

    return m_index;

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
sf::FloatRect animation::loc_bound() const {

	float width{};
	float height{};

	// If frame list is empty, use texture rectangle, if not, use the current
	// frame.
	if (0 == m_frames->operator[](ORIG_FRM).size()) {
	
		//std::cout << "Local boundaries from mTexRect";
		width = static_cast<float>(std::abs(mTexRect.width));
		height = static_cast<float>(std::abs(mTexRect.height));
	
	} else {

		// Even if the frame list is not empty, there can still be a problem
		// width the index of the current frame. Since "m_index" is initialized
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
		std::size_t temp_index{};
		if (m_frames->operator[](ORIG_FRM).size() <= m_index) {
		
			temp_index = 0;
		
		} else {
		
			temp_index = m_index;
		
		}
	
		auto tex_frm = 
		m_frames->operator[](TEX_RECT_FRM).operator[](temp_index);

		/*std::cout << "Local boundaries from TEX_RECT_FRM\n";
		std::cout << "Index is at position " << m_index;*/
    	width = static_cast<float>(std::abs(tex_frm.w)) ;
    	height = static_cast<float>(std::abs(tex_frm.h)) ;

		/*std::cout << "\nFrame boundaries: \n";
		std::cout << "\t width = " << width << "\n";
		std::cout << "\t height = " << height << std::endl;
		std::cin.get();*/

	}

	/*std::cout << "\nLocal boundaries: \n";
	std::cout << "\t width = " << width << "\n";
	std::cout << "\t height = " << height << std::endl;*/

    return sf::FloatRect(0.f, 0.f, width, height) ;

}

//! Return maximum local size of animation.
/*!
* Return the size of the biggest frame stored for the animation, which is
* the largest possible size for the animation, if no transformation is taken
* into account. It is actually the biggest which can be returned by the
* obj_size() function.
* \return Maximum size of the animation, without transformations.
*/
sf::Vector2f animation::max_obj_size() {

	return m_max_size;

}

//! Return maximum global size of animation.
/*!
* Return the size of the biggest frame stored for the animation, which is
* the largest possible size for the animation, with the transformation is taken
* into account. It is actually the biggest which can be returned by the size()
* function.
* \return Maximum size of the animation, with transformations.
*/
sf::Vector2f animation::max_size() {

	auto bounds = loc_bound();
	sf::FloatRect max_size_rect(bounds.top, bounds.left, 
								m_max_size.x, m_max_size.y);

	auto trans_rect = getTransform().transformRect(max_size_rect);

	return sf::Vector2f(trans_rect.width, trans_rect.height);
}

//! Return number of frames.
/*!
* Return the number of frames currently stored for the animation.
* \return Number of frames for the animation.
*/
std::size_t animation::frames() {

	return m_frames->operator[](ORIG_FRM).size();

}

//! Calculate maximum size for animation.
/*!
* Compares current maximum size of the animation frames with the given
* parameter and sets a new size if necessary.
*
* NOTE: This function is called in every member function which modifies or adds
* a frame, so that the maximum frame size is always updated.
* \param size Size of added/modified frame to compare with.
*/
void animation::calc_max_size(const sf::Vector2f& size) {

	// ATTENTION: Although the code could be written more compact with the "?"
	// operator, the "?" operator would require an assignment after the
	// comparison of the two values, even if size is not bigger than max_size.
	// Using the "if" statements, this sometimes unnecessary assignment can be
	// avoided.
	if (std::isless(m_max_size.x, size.x)) {
	
		m_max_size.x = size.x;
	
	}

	if (std::isless(m_max_size.y, size.y)) {
	
		m_max_size.y = size.y;
	
	}

}

//! Update the vertices' texture coordinates.
/*!
* The coordinates are retrieved by the current frame and
* assigned anticlockwise. If there is any texture rectangle
* in use, it is taken in account.
*/
void animation::updateTexCoords() {

	// Create variables so they are available in the whole function scope.
	float left{};
    float right{};
    float top{};
    float bottom{};

	// Check if there are already frames for the animation. If not, then the
	// texture coords should be set to the texture rectangle, as it is done in
	// the sprite class.
	if (m_frames->operator[](TEX_RECT_FRM).size() == 0) {
	
		left = static_cast<float>(mTexRect.left);
    	right = left + mTexRect.width;
    	top = static_cast<float>(mTexRect.top);
    	bottom = top + mTexRect.height;

	} else {

		left = static_cast<float>(m_frames->operator[](TEX_RECT_FRM).operator[](m_index).x);
		right = left + m_frames->operator[](TEX_RECT_FRM).operator[](m_index).w;
		top = static_cast<float>(m_frames->operator[](TEX_RECT_FRM).operator[](m_index).y);
		bottom = top + m_frames->operator[](TEX_RECT_FRM).operator[](m_index).h;

	}

	/*std::cout << "Frame left = " << left << std::endl;
	std::cout << "Frame top = " << top << std::endl;
	std::cout << "Frame right = " << right << std::endl;
	std::cout << "Frame bottom = " << bottom << std::endl;
	std::cin.get();*/

	// Coordinates, defined anticlockwise.
    m_vertices[0].texCoords = sf::Vector2f(left, top);
    m_vertices[1].texCoords = sf::Vector2f(left, bottom);
    m_vertices[2].texCoords = sf::Vector2f(right, bottom);
    m_vertices[3].texCoords = sf::Vector2f(right, top);

}

//! Draw animation to render target.
/*!
* NOTE: The texture rectangle is included in the vertecies.
* \param target Render target to draw to.
* \param states Current render states.
*/
void animation::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    if (nullptr != m_texture) {

        states.transform *= getTransform();
        states.texture = m_texture.get();
        target.draw(m_vertices, 4, sf::Quads, states);

    }

}
