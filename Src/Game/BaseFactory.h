#ifndef SRC_GAME_BASEFACTORY_H_

#define SRC_GAME_BASEFACTORY_H_

#include <string>
#include <vector>

#include "Game/Base.h"

namespace CC {

/**
 * @brief Factory used to save/load base and create building
 */
class BaseFactory {
 public:
    /// Get a reference to the base
    inline Base& GetBase() { return base; }

    /// Load the base from the Base.dat file
    void Load();

    /// Save the base to the Base.dat file
    void Save();

 protected:
    /**
     * @brief Load a building according to it split string string
     * @param buildingSplit the
     * @return The building, or nullptr if an error occured
     */
    Building* LoadBuilding(const std::vector<std::string>& buildingSplit,
                           const sf::Vector2u& position);

    Base base;  ///< Building that are part of the base, they must be dynamically allocated, and are owned by the Base.
};

}

#endif  // SRC_GAME_BASEFACTORY_H_
