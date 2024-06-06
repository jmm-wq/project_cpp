#ifndef SRC_GAME_BASE_H_

#define SRC_GAME_BASE_H_

#include <vector>

#include "Game/Building.h"

namespace CC {

/**
 * @brief Player base
 */
class Base {
 public:
    /// Delete all build of the base
    ~Base();

    /// Get a reference to the base buidlings
    inline std::vector<Building*>& GetBuildings() { return buildings; }

    /**
     * @brief Get the ore available in all silos
     * @return The ore available in all silos
     */
    unsigned int GetAvailableOre();

    /**
     * @brief Remove a specific amount of ore from the base silos
     * @param amount Amount of ore to remove
     */
    void RemoveOre(unsigned int amount);

    /**
     * @brief Get the amount of power usable in the base
     * @return The amount of power usable in the base
     */
    unsigned int GetFreePowerGrid();

 protected:
    std::vector<Building*> buildings;  ///< Building that are part of the base, they must be dynamically allocated, and are owned by the Base.
};

}

#endif  // SRC_GAME_BASE_H_
