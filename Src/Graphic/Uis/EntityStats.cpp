#include "Graphic/Uis/EntityStats.h"

#include <functional>
#include <string>

#include "Graphic/Texture.h"
#include "Graphic/Sprite.h"
#include "Window/Window.h"

namespace CC {

EntityStats::EntityStats() {
    portrait.setTexture(
                TextureCollection::Get(TextureCollection::Id::SpriteSheet));
    portrait.setPosition(8, 12);

    name.setFillColor(sf::Color::White);
    name.setPosition(48, 18);
    name.setFont(Window::Font);
    name.setCharacterSize(18);
    name.setStyle(sf::Text::Bold | sf::Text::Underlined);

    statText.setFillColor(sf::Color::White);
    statText.setPosition(8, 56);
    statText.setFont(Window::Font);
    statText.setCharacterSize(12);


    elements.push_back(&portrait);
    elements.push_back(&name);
    elements.push_back(&statText);
}

void EntityStats::Update(Entity* entity) {
    if (entity != nullptr) {
        enabled = true;

        sf::Sprite& sprite = entity->Get<sf::Sprite>("Sprite");

        portrait.setTextureRect(sprite.getTextureRect());

        if (entity->HasID("TextFunc"))
            statText.setString(entity->Get<std::function<std::string()>>("TextFunc")());
        else
            statText.setString("");

        name.setString(entity->Get<std::string>("Name"));
    } else {
        enabled = false;
    }
}

}
