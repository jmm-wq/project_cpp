#ifndef SRC_GAME_PLAYER_H_

#define SRC_GAME_PLAYER_H_

#include "Game/Entity.h"
#include "Game/Tile.h"
#include "Window/ActionEventArg.h"

namespace CC {

class Game;

/**
 * @brief Player entity
 */
class Player : public Entity {
 public:
    /**
     * @brief Construct a new player instance
     * @param position Position of the player in the world
     * @param game Reference to the game that handle this player
     */
    Player(sf::Vector2u position, Game& game);

    /// Get the entity facing the player
    Entity* GetFacingEntity() const;
    /// Return true of the player doesn't face the outside of the world
    bool IsFacingValid() const;
    /// Get the player facing position
    sf::Vector2u GetFacingPosition() const;

 protected:
    /// When the player wants to move left
    void MoveLeft(ActionEventArg arg);
    /// When the player wants to move right
    void MoveRight(ActionEventArg arg);
    /// When the player wants to move up
    void MoveUp(ActionEventArg arg);
    /// When the player wants to move down
    void MoveDown(ActionEventArg arg);
    /// Mine the entity in front of the ship
    void Mine(ActionEventArg arg);

    Game& game;  ///< Reference to the game that handle this player
};

}

#endif  // SRC_GAME_PLAYER_H_
