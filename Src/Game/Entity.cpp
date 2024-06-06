#include "Game/Entity.h"

#include "Graphic/Texture.h"

namespace CC {

Entity::Entity(sf::Vector2u position) {
    Get<sf::Vector2u>("Position") = position;
    Get<sf::Sprite>("Sprite") = sf::Sprite();
}

Entity::Entity(sf::Vector2u position, Sprite::Id sprite) {
    Get<sf::Vector2u>("Position") = position;
    Get<sf::Sprite>("Sprite").setTexture(
                TextureCollection::Get(TextureCollection::Id::SpriteSheet));
    Get<sf::Sprite>("Sprite").setTextureRect(Sprite::Get(sprite));
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(Get<sf::Sprite>("Sprite"), states);
}

}
