#include "Game/Buildings/Core.h"

#include <functional>

#include "Graphic/Sprite.h"
#include "Graphic/Texture.h"

namespace CC {

Core::Core(sf::Vector2u position) :
    Building(position) {
    sf::Sprite sprite;
    sprite.setTexture(
                TextureCollection::Get(TextureCollection::Id::SpriteSheet));
    sprite.setTextureRect(Sprite::Get(Sprite::BaseCore));
    Get<sf::Sprite>("Sprite") = sprite;

    Get<std::string>("Name") = "Core";

    int& PG = Get<int>("PG");

    PG = 20;

    Get<std::function<std::string()>>("TextFunc") =
            [&]() {
        return "Power Generated : " + std::to_string(PG) + "MW";
    };
}

bool Core::Load(const std::vector<std::string>& split) {
    if (split.size() != 2)
        return false;

    Get<int>("PG") = std::stol(split[1]);

    return true;
}

std::string Core::Save() {
    std::string saveStr = "Core " +
            std::to_string(Get<int>("PG"));

    return saveStr;
}

}




