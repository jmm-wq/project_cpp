#ifndef SRC_WINDOW_WINDOW_H_

#define SRC_WINDOW_WINDOW_H_

#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "Game/Game.h"
#include "Graphic/Uis/EntityStats.h"
#include "Graphic/Uis/PlayerStats.h"
#include "Tool/Event.h"
#include "Window/Action.h"
#include "Window/ActionEventArg.h"
#include "Window/AnimationManager.h"

namespace CC {

/**
 * @brief A window where we will this our game
 */
class Window {
 public:
    /**
     * @brief Construct and open a new window
     */
    Window();
    /**
     * @brief Window main loop, handle events, draw things, ...
     */
    void Run();

    typedef Event<void, ActionEventArg> ActionEvent;
    typedef std::unordered_map<Action, ActionEvent> ActionEventsMap;
    ActionEventsMap ActionEvents;  ///< A map where each action may have its own event

    /// Get the coordinate of the top left pixel of the window, according to the current view
    inline sf::Vector2f GetTopLeftCoordinate() const {
        return window.mapPixelToCoords(sf::Vector2i(0, 0));
    }

    static const sf::Vector2u Size;  ///< Size of the window (in pixels)
    static sf::Font Font;  ///< Font used to draw text accross all uis

 protected:
    /**
     * @brief Treat all event that happended since the last time we called this
     */
    void HandleEvents();
    /**
     * @brief Take a screenshot of the entire screen and save it on disk
     * @param key The key that was pressed to take the screenshot
     */
    void TakeScreenshot(ActionEventArg arg);
    /**
     * @brief Update the view of the window, according to the player position
     */
    void UpdateView();

    sf::RenderWindow window;  ///< SFML window where we render our game
    Game game;  ///< Our game logic instance
    ActionManager actionManager;  ///< Action manager of the window
    AnimationManager animationManager;  ///< Animation manager of the window

    EntityStats entityStats;  ///< Ui to display the stats of the entity facing the player
    PlayerStats playerStats;  ///< Ui to display player stats

    sf::View worldView;  ///< View used to draw the world
    sf::View playerStatUiView;  ///< View used to draw the player stat ui
    sf::View otherUiView;  ///< View used to draw other ui (down the player stat ui)
};

}  // namespace CC

#endif  // SRC_WINDOW_WINDOW_H_
