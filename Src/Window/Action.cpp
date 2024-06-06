#include "Window/Action.h"

namespace CC {

ActionManager::ActionManager() {
    keysToActions.insert({
        {sf::Keyboard::Insert, Action::Screenshot},
        {sf::Keyboard::A, Action::MoveLeft},
        {sf::Keyboard::D, Action::MoveRight},
        {sf::Keyboard::W, Action::MoveUp},
        {sf::Keyboard::S, Action::MoveDown},
        {sf::Keyboard::J, Action::Mine},
        {sf::Keyboard::Space, Action::Jump},
        {sf::Keyboard::L, Action::Build},
        //{sf::Keyboard::L, Action::BuildCore},
        {sf::Keyboard::K, Action::Use}
    });
}

Action ActionManager::GetAction(sf::Keyboard::Key key) const {
    KeyMap::const_iterator it = keysToActions.find(key);
    return it != keysToActions.end() ? it->second : Action::Blank;
}

bool ActionManager::IsAnAction(sf::Keyboard::Key key) const {
    return keysToActions.find(key) != keysToActions.end();
}

}
