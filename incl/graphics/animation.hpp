// Animation
// animation.hpp

#ifndef _ANIMATION_
#define _ANIMATION_

#include <SFML/Graphics.hpp>
#ifndef _TEXTUREABLE_
#include "texturable.hpp"
#endif
#ifndef _TEXTUREREPOSITORY_
#include "texture_repos.hpp"
#endif
#ifndef _FRAMEREPOSITORY_
#include "frame_repos.hpp"
#endif

//! Class for animating sprites.
/*!
* This class provides methods for creating, modifying and rendering animated
* sprites. It uses a texture as base for the graphical information and frames,
* which provide basic information about animation frames.
*/
class animation : public Textureable {

public:

    // Member functions.

    animation();
    animation(const sf::Texture& texture);
    animation(const sf::Texture& texture, const sf::IntRect& rect);
    ~animation();

    std::size_t insert(const frame& frm, sf::IntRect rect = sf::IntRect());
    std::size_t insert(const frame& frm, std::size_t index,
                       sf::IntRect rect = sf::IntRect());
    std::size_t insert(const frame_group& frm_grp,
                       sf::IntRect rect = sf::IntRect());
    std::size_t insert(const frame_group& frm_grp, std::size_t index,
                       sf::IntRect rect = sf::IntRect());

    void setTexRect(const sf::IntRect& rect);

	void replace(std::size_t index, const frame& other);
	void mod_size(std::size_t index, const sf::Vector2i& size);
	void mod_pos(std::size_t index, const sf::Vector2i& pos);

    std::size_t render();
    std::size_t render(std::size_t index);

	sf::FloatRect loc_bound() const;
	sf::Vector2f max_obj_size();
	sf::Vector2f max_size();
	std::size_t frames();

private:

	void calc_max_size(const sf::Vector2f& size);
    void updateTexCoords();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    //! Pointer to stored frames inside repository.
    frames_ptr m_frames;
    //! Index of the current pointer.
    std::size_t m_index;
	//! Biggest frame of the animation.
	sf::Vector2f m_max_size;

};

#endif // _ANIMATION_
