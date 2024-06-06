#ifndef SRC_GAME_TILE_H_

#define SRC_GAME_TILE_H_

#include <SFML/Graphics.hpp>

#include "Game/Entity.h"

namespace CC {

/**
 * @brief A tile in the world
 */
struct Tile : public sf::Drawable, sf::Transformable {
    sf::Vector2u Position;  ///< Position of the tile in the world
    Entity* Ent = nullptr;  ///< Entity present on the tile, nullptr is none. There can be only one entity on each tile

    /**
     * @brief Draw the content of the tile on screen
     * @param target Render target to draw to
     * @param states Current render states
     */
    void draw(sf::RenderTarget &target,
              sf::RenderStates states) const override;
};

}

#endif  // SRC_GAME_TILE_H_
