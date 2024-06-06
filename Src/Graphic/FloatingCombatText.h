#ifndef SRC_GRAPHIC_FLOATINGCOMBATTEXT_H_

#define SRC_GRAPHIC_FLOATINGCOMBATTEXT_H_

#include <string>

#include <SFML/Graphics.hpp>

#include "Graphic/Animation.h"

namespace CC {

/**
 * @brief A user interface to display to our player
 */
class FloatingCombatText : public Animation {
 public:
    /**
     * @brief Construct a new floating combat text instance
     * @param floatingText The text to display
     * @param startingPosition The starting position of the text
     */
    FloatingCombatText(std::string floatingText,
                       sf::Vector2f startingPosition);

    /**
     * @brief Update the floating combat text
     */
    void Update() override;

 protected:
    sf::Text text;  ///< The text to display
    sf::Vector2f startingPosition;  ///< The starting position of the text
};

}  // namespace CC

#endif  // SRC_GRAPHIC_FLOATINGCOMBATTEXT_H_
