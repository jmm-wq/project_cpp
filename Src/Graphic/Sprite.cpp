#include "Graphic/Sprite.h"

#include <unordered_map>

#include "Graphic/Texture.h"

namespace CC {

sf::IntRect Sprite::Get(Sprite::Id sprite) {
    static std::unordered_map<Sprite::Id, sf::IntRect> spriteMap {
        {PlayerShip,    sf::IntRect(0,  0,  32,  32)},
        {Asteroid1,     sf::IntRect(32, 0,  32,  32)},
        {Asteroid2,     sf::IntRect(64, 0,  32,  32)},
        {Asteroid3,     sf::IntRect(96, 0,  32,  32)},
        {BaseCore,     sf::IntRect(128, 0,  32,  32)},
        {OreSilo,     sf::IntRect(160, 0,  32,  32)},
        {Portrait,      sf::IntRect(0,  0,  32,  32)},//(0,  32, 64,  64)},
        {RemoteMiner,      sf::IntRect(16,  32,  32,  32)},//(0,  32, 64,  64)},
        {UiElement1,    sf::IntRect(0,  96, 192, 96)},
        {Enemy,    sf::IntRect(0,  96,  32,  32)},
    };

    return spriteMap[sprite];
}

const unsigned int Sprite::Size = 32;

}
