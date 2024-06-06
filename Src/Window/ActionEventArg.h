#ifndef SRC_WINDOW_ACTIONEVENTARG_H_

#define SRC_WINDOW_ACTIONEVENTARG_H_

#include <Window/Action.h>
#include <Window/AnimationManager.h>

namespace CC {

class Game;
/**
 * @brief An ActionEventArg struct will be passed to any handler that registered to an action event
 */
struct ActionEventArg {
    Action Act;  ///< The action that was performed
    sf::Keyboard::Key Key;  ///< The key that was pressed
    Game& Gam;  ///< A reference to the current game
    bool& EndTurn;  ///< May be set to true by event handler to signify that the action has ended the player turn
    AnimationManager& AnimManager;  ///< Animation manager of the window, to allow handler to add animations

    /**
     * @brief Create a new ActionEventArg instance
     * @param action An action
     * @param key A key
     * @param game A reference to a game
     */
    ActionEventArg(Action action,
                   sf::Keyboard::Key key,
                   Game& game,
                   bool& endTurn,
                   AnimationManager& animManager) :
        Act(action),
        Key(key),
        Gam(game),
        EndTurn(endTurn),
        AnimManager(animManager) {
        EndTurn = false;
    }
};

}  // namespace CC

#endif  // SRC_WINDOW_ACTIONEVENTARG_H_
