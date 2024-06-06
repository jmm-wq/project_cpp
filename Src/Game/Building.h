#ifndef SRC_GAME_BUILDING_H_

#define SRC_GAME_BUILDING_H_

#include <string>
#include <vector>

#include "Game/Entity.h"

namespace CC {

/**
 * @brief Player base
 */
class Building : public Entity {
 public:
    /// Call the entity constructor
    explicit Building(sf::Vector2u position) : Entity(position) { }

    /**
    * @brief Load the building from a string, the string has been split by spaces : <Building Name> <Param1> <Param2> ...
    * @param split The string of the building split by spaces
    * @return True if the building has been loaded correctly
    */
    virtual bool Load(const std::vector<std::string>& split) = 0;
    /**
     * @brief Save the building as a string : <Building Name> <Param1> <Param2> ...
     * @return The string of the building
     */
    virtual std::string Save() = 0;
};

}
#endif  // SRC_GAME_BUILDING_H_
