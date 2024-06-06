///*      Enemy is no longer an enemy, now its Remote Miner

#ifndef SRC_GAME_ENEMY_H_

#define SRC_GAME_ENEMY_H_

#include "Game/Entity.h"
#include "Game/Tile.h"
#include "Window/ActionEventArg.h"

namespace CC {

class Game;
//
 /**
 * @brief Enemy entity
 //
 */
class Enemy : public Entity {
 public:
//
   /**
     * @brief Construct a new Enemy instance
     * @param position Position of the Enemy in the world
     * @param game Reference to the game that handle this Enemy
//
     */
    Enemy(sf::Vector2u position, Game& game);

    /// Get the entity facing the Enemy
    Entity* GetFacingEntity() const;
    /// Return true of the Enemy doesn't face the outside of the world
    bool IsFacingValid() const;
    /// Get the Enemy facing position
    sf::Vector2u GetFacingPosition() const;


 protected:
    /// When the Enemy wants to move left
    void MoveLeft(ActionEventArg arg);
    /// When the Enemy wants to move right
    void MoveRight(ActionEventArg arg);
    /// When the Enemy wants to move up
    void MoveUp(ActionEventArg arg);
    /// When the Enemy wants to move down
   void MoveDown(ActionEventArg arg);
   /// Mine the entity in front of the remote miner
    void Mine(ActionEventArg arg);

    Game& game;  ///< Reference to the game that handle this Enemy
};

}

#endif  // SRC_GAME_ENEMY_H_

//*

