#ifndef SRC_GRAPHIC_SPRITE_H_

#define SRC_GRAPHIC_SPRITE_H_

#include <SFML/Graphics.hpp>

namespace CC {

class Sprite {
 public:
    /**
     * @brief Name of all sprites available in the spritesheet texture
     */
    enum Id : int {
        PlayerShip = 0,     // Source : Edited using : pixelatorapp.com
        Asteroid1,          // Source : Edited using : pixelatorapp.com
        Asteroid2,          // Source : Edited using : pixelatorapp.com
        Asteroid3,          // Source : Edited using : pixelatorapp.com
        BaseCore,          // Source : Edited using : pixelatorapp.com
        OreSilo,          // Source : Edited using : pixelatorapp.com
        Portrait,           // Source :  Edited using : pixelatorapp.com
        RemoteMiner,           // Source :  Edited using : pixelatorapp.com
        UiElement1,          // Source : Edited using : pixelatorapp.com
        Enemy
    };

    /**
     * @brief Get the sf::IntRect corresponding to a sprite in THE texture
     * @param sprite Name of the wanted sprite
     * @return The sf::IntRect corresponding to the sprite wanted
     */
    static sf::IntRect Get(Sprite::Id sprite);

    static const unsigned int Size;  ///< Size of a tile sprite in the spritesheet texture

 private:
    Sprite() = delete;
};

}  // namespace CC

#endif  // SRC_GRAPHIC_SPRITE_H_
