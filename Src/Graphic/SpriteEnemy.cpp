#include "Graphic/Sprite.h"

#include <unordered_map>

#include "Graphic/Texture.h"

namespace CC {

sf::IntRect Sprite::Get(Sprite::Id sprite) {
    static std::unordered_map<Sprite::Id, sf::IntRect> spriteMap {
        {Enemy,    sf::IntRect(0,  0,  32,  32)},
    };

    return spriteMap[sprite];
}

const unsigned int Sprite::Size = 32;

}
