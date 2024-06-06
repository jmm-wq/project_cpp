#ifndef SRC_GRAPHIC_UI_H_

#define SRC_GRAPHIC_UI_H_

#include <vector>

#include <SFML/Graphics.hpp>

namespace CC {

/**
 * @brief A user interface to display to our player
 */
class Ui : public sf::Drawable {
 public:
    /// Construct a new empty Ui
    Ui();
    /// Construct a new Ui with specific elements
    explicit Ui(std::vector<sf::Drawable*>& elements);

    /// To know if the ui is enabled
    inline bool IsEnabled() const { return enabled; }
    /// Set enabled to true if it's false, and vice versa
    inline void SwitchEnabled() { enabled = !enabled; }

    /// Update the ui if needed
    virtual void Update() { }

    /**
     * @brief Draw game entities on screen
     * @param target Render target to draw to
     * @param states Current render states
     */
    void draw(sf::RenderTarget &target,
              sf::RenderStates states) const override;

 protected:
    std::vector<sf::Drawable*> elements;  ///< All elements that compose our Ui. The Ui is not responsable of the elements. The order of elements matters as they will be drawn in that order.
    bool enabled;  ///< If the ui is enabled <=> displayed
};

}  // namespace CC

#endif  // SRC_GRAPHIC_UI_H_
