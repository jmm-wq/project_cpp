#ifndef SRC_WINDOW_ANIMATIONMANAGER_H_

#define SRC_WINDOW_ANIMATIONMANAGER_H_

#include <list>

#include <SFML/Graphics.hpp>

#include "Graphic/Animation.h"

namespace CC {

/**
 * @brief The AnimationManager class allows us to manage the update and drawing of animations
 */
class AnimationManager : public sf::Drawable {
 public:
    /**
     * @brief Construct a new AnimationManager instance
     */
    AnimationManager() {}

    /// Add an animation to the manager, animation must be dynamically allocated and it will become the property of the manager who will be delete.
    inline void AddAnimation(Animation* animation) {
        animations.push_back(animation); }

    /**
     * @brief Update the animations
     */
    void Update();

    /**
     * @brief Draw game entities on screen
     * @param target Render target to draw to
     * @param states Current render states
     */
    void draw(sf::RenderTarget &target,
              sf::RenderStates states) const override;

 protected:
    std::list<Animation*> animations;  ///< The list of currently runing animation. The manager is the proprietary of the animations.
};

}  // namespace CC

#endif  // SRC_WINDOW_ANIMATIONMANAGER_H_
