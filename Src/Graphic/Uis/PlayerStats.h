#ifndef SRC_GRAPHIC_UIS_PLAYERSTATS_H_

#define SRC_GRAPHIC_UIS_PLAYERSTATS_H_

#include <SFML/Graphics.hpp>

#include "Game/Base.h"
#include "Game/Player.h"
#include "Graphic/Ui.h"

namespace CC {

class Window;

/**
 * @brief The Game class where game logic will be updated
 */
class PlayerStats : public Ui {
 public:
    /**
     * @brief Construct a new game overlay instance
     * @param player A reference to the player of the game
     */
    explicit PlayerStats(Player& player, Base& base);


    //loadsave



    /// Update the overlay
    void Update() override;

 protected:
    Player& player;  ///< A reference to the player of the game
    Base& base;  ///< A reference to the base of the game

    sf::Sprite portrait;  ///< Sprite for the portrait
    sf::Text name;  ///< Text for the name of the player
    sf::Text ore;  ///< Text for the ore capacity of the player
    //sf::Text baseOre;  ///< Text for the ore available in silos
    sf::Text basePG;  ///< Text for the PG available in the base
    sf::Text goal;    ///< Text for the goal of the game
    sf::Text upgrade;    ///< Text for the avalible upgrade
    sf::Text controls;    ///< Text for the controls of the game
    sf::Text highscore;    ///< Text for the highscore of the game
};

}  // namespace CC

#endif  // SRC_GRAPHIC_UIS_PLAYERSTATS_H_
