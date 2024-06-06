#include "Game/Tile.h"

namespace CC {

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (Ent != nullptr) {
        states.transform = states.transform.combine(this->getTransform());
        target.draw(*Ent, states);
    }
}

}
