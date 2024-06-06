#ifndef SRC_WINDOW_ACTION_H_

#define SRC_WINDOW_ACTION_H_

#include <unordered_map>
#include <unordered_set>

#include <SFML/Graphics.hpp>

namespace CC {

/**
 * @brief An action that the user can perform
 */
enum Action : int {
    Blank,  // Blank action that can be returned in case of error, ...
    Screenshot,
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown,
    Mine,
    Jump,
    Build,
    //BuildCore,
    Use
};

/**
 * @brief The ActionManager class allows us to better manager action made by the user.
 */
class ActionManager {
 public:
    /**
     * @brief Create a new ActionManager instance
     */
    ActionManager();

    /**
     * @brief Get the action corresponding to the provided key
     * @param key Key that the user pressed
     * @return The corresponding action, or Blank is the key doesn't correpond to any action
     */
    Action GetAction(sf::Keyboard::Key key) const;

    /**
     * @brief Check if a key correspond to an action
     * @param key A key
     * @return True if key correspond to an action, false otherwise
     */
    bool IsAnAction(sf::Keyboard::Key key) const;

    typedef std::unordered_map<sf::Keyboard::Key, Action> KeyMap;

 protected:
    KeyMap keysToActions;  ///< Actions that correspond to keys
};

}  // namespace CC

#endif  // SRC_WINDOW_ACTION_H_
