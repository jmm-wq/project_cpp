#ifndef SRC_GRAPHIC_ANIMATION_H_

#define SRC_GRAPHIC_ANIMATION_H_

#include <SFML/Graphics.hpp>

namespace CC {

/**
 * @brief An animation
 */
class Animation : public sf::Drawable {
 public:
    /**
     * @brief Construct a new animation instance
     * @param duration The duration of the animation (in second)
     */
    explicit Animation(float duration);

    /// Return true if the animation has ended
    inline bool HasEnded() const {
        return timer.getElapsedTime().asSeconds() >= duration; }

    /**
     * @brief Update the animation
     */
    virtual void Update() = 0;

    /**
     * @brief Draw game entities on screen
     * @param target Render target to draw to
     * @param states Current render states
     */
    void draw(sf::RenderTarget &target,
              sf::RenderStates states) const override;

 protected:
    sf::Drawable* drawable;  ///< The drawable of the animation
    sf::Clock timer;  ///< A timer to know when the animation end
    float duration;  ///< The duration of the animation (in second)
};

}  // namespace CC

#endif  // SRC_GRAPHIC_ANIMATION_H_
