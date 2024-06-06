#include "Graphic/Ui.h"

namespace CC {

Ui::Ui() {
    enabled = true;
}

Ui::Ui(std::vector<sf::Drawable*>& elements) : elements(elements) {
    enabled = true;
}

void Ui::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (enabled)
        for (sf::Drawable* element : elements)
            if (element != nullptr)
                target.draw(*element, states);
}

}
