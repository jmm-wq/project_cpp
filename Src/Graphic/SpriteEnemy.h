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
        Enemy = 0     // Source : Edited using : pixelatorapp.com
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
