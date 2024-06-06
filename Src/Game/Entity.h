#ifndef SRC_GAME_ENTITY_H_

#define SRC_GAME_ENTITY_H_

#include <SFML/Graphics.hpp>

#include "Graphic/Sprite.h"
#include "Tool/PropertyManager.h"

namespace CC {

/**
 * @brief Entity, something that can be interacted with in the world
 */
class Entity : public sf::Drawable, public PropertyManager {
 public:
    /**
     * @brief Construct a new entity instance
     * @param position Position of the entity in the world
     */
    explicit Entity(sf::Vector2u position = sf::Vector2u(0, 0));
    /**
     * @brief Construct a new entity instance
     * @param position Position of the entity in the world
     * @param sprite Sprite of the entity
     */
    Entity(sf::Vector2u position, Sprite::Id sprite);

    /**
     * @brief Draw game entities on screen
     * @param target Render target to draw to
     * @param states Current render states
     */
    void draw(sf::RenderTarget &target,
              sf::RenderStates states) const override;
};

}

#endif  // SRC_GAME_ENTITY_H_
