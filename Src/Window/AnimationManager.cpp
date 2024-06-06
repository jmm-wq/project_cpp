#include "Window/AnimationManager.h"

namespace CC {

void AnimationManager::Update() {
    auto it = animations.begin();
    while (it != animations.end()) {
        if ((*it)->HasEnded()) {
            it = animations.erase(it);
        } else {
            (*it)->Update();
            it++;
        }
    }
}

void AnimationManager::draw(sf::RenderTarget &target,
                            sf::RenderStates states) const {
    for (Animation* animation : animations)
        if (animation != nullptr)
            target.draw(*animation, states);
}

}
