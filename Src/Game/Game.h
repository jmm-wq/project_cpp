#ifndef SRC_GAME_GAME_H_

#define SRC_GAME_GAME_H_

#include <vector>

#include <SFML/Graphics.hpp>

#include "Game/Base.h"
#include "Game/BaseFactory.h"
#include "Game/Player.h"
#include "Game/Enemy.h"
#include "Game/World.h"
#include "Window/ActionEventArg.h"

namespace CC {

class Window;

/**
 * @brief The Game class where game logic will be updated
 */
class Game : public sf::Drawable {
 public:
    /**
     * @brief Construct a new game instance
     * @param window A refence to the drawing window
     */
    explicit Game(Window& window);
    /**
     *  Game destructor
     */
    ~Game();

    /**
     * @brief Init and load game resources for the first game screen (should only be called once)
     */
    void Init();
    /**
     * @brief Load game resources for current game screen
     */
    void Load();
    /**
     * @brief Unload game resources for current game screen
     */
    void Unload();

    /**
     * @brief Resolve the game logic after the player takes a turn-ending action
     */
    void Resolve();

    /// Get the world of current game
    inline World& GetWorld() { return world; }
    /// Get the window of current game
    inline Window& GetWindow() { return window; }
    /// Get the player of current game
    inline Player& GetPlayer() { return player; }
    /// Get the Enemy of current game
    inline Enemy& GetEnemy() { return enemy; }
    /// Get the base of the current game
    inline Base& GetBase() { return base; }

    /**
     * @brief Draw game entities on screen
     * @param target Render target to draw to
     * @param states Current render states
     */
    void draw(sf::RenderTarget &target,
              sf::RenderStates states) const override;

 protected:
    /**
     * @brief Handle the player Jump action, will transport the player to the base or to a new adventure
     * @param arg Action argument
     */
    void PlayerJump(ActionEventArg arg);
    /**
     * @brief Handle the player Build action, as an effect only if the player is at base
     * @param arg Action argument
     */
    void PlayerBuild(ActionEventArg arg);
    /**
     * @brief Handle the player Use action, call the player use function of the entity facing the player
     * @param arg Action argument
     */
    void PlayerUse(ActionEventArg arg);

    Window& window;  ///< A reference to the drawing window
    World world;  ///< The world in which the game takes place
    Player player;  ///< The player controlled entity
    Enemy enemy;
    BaseFactory factory;  ///< Factory used to load/save the base
    Base& base;  ///< The base built by the player
    std::vector<Entity*> entities;  ///< All entities in the world
    bool baseMode;  ///< True if the player is at its base
};

}

#endif  // SRC_GAME_GAME_H_
