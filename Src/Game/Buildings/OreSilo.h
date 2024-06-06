#ifndef SRC_GAME_BUILDINGS_ORESILO_H_

#define SRC_GAME_BUILDINGS_ORESILO_H_

#include <string>
#include <vector>

#include "Game/Building.h"
#include "Window/ActionEventArg.h"

namespace CC {

class Game;

/**
 * @brief Ore silo building
 */
class OreSilo : public Building {
 public:
    /**
     * @brief Construct a new ore silo
     * @param position Position of the silo in the world
     */
    explicit OreSilo(sf::Vector2u position);

     //protected:
    //Base& base;  ///< A reference to the base of the game

    /**
    * @brief Load the building from a string, the string has been split by spaces
    * @param split The string of the building split by spaces
    * @return True if the building has been loaded correctly
    */
    bool Load(const std::vector<std::string>& split) override;
    /**
    * @brief Save the building as a string : OreSile Ore MaxOre
    * @return The string of the building
    */
    std::string Save() override;

 protected:
    void TransferOre(ActionEventArg arg);
};

}  // namespace CC

#endif  // SRC_GAME_BUILDINGS_ORESILO_H_
