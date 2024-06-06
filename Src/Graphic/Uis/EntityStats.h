#ifndef SRC_GRAPHIC_UIS_ENTITYSTATS_H_

#define SRC_GRAPHIC_UIS_ENTITYSTATS_H_

#include <SFML/Graphics.hpp>

#include "Game/Entity.h"
#include "Graphic/Ui.h"

namespace CC {

class Window;

/**
 * @brief The Game class where game logic will be updated
 */
class EntityStats : public Ui {
 public:
    /**
     * @brief Construct a new entity stats ui instance
     */
    EntityStats();

    /**
     * @brief Update the ui to display an entity stats
     * @param entity Entity that we want stats to be displayed
     */
    void Update(Entity* entity);

 protected:
    sf::Sprite portrait;  ///< Sprite for the portrait
    sf::Text name;  ///< Text for the name of the player
    sf::Text statText;  ///< Text for the entity stat
};

}  // namespace CC

#endif  // SRC_GRAPHIC_UIS_ENTITYSTATS_H_
