#ifndef SRC_GAME_BUILDINGS_CORE_H_

#define SRC_GAME_BUILDINGS_CORE_H_

#include <string>
#include <vector>

#include "Game/Building.h"
#include "Window/ActionEventArg.h"

namespace CC {

class Game;

/**
 * @brief Base Core building
 */
class Core : public Building {
 public:
    /**
     * @brief Construct a new base core
     * @param position Position of the core in the world
     */
    explicit Core(sf::Vector2u position);

    /**
    * @brief Load the building from a string, the string has been split by spaces
    * @param split The string of the building split by spaces
    * @return True if the building has been loaded correctly
    */
    bool Load(const std::vector<std::string>& split) override;
    /**
    * @brief Save the building as a string : Core
    * @return The string of the building
    */
    std::string Save() override;
};

}  // namespace CC

#endif  // SRC_GAME_BUILDINGS_CORE_H_
