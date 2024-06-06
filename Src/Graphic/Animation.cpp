#include "Graphic/Animation.h"

namespace CC {

Animation::Animation(float duration)
    : drawable(nullptr),
      duration(duration) {
}

void Animation::draw(sf::RenderTarget &target,
                     sf::RenderStates states) const {
    if (drawable != nullptr)
        target.draw(*drawable, states);
}

}
