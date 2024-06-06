#include "Game/Buildings/OreSilo.h"

#include <functional>
#include <iostream>

#include "Game/Game.h"
#include "Graphic/FloatingCombatText.h"
#include "Graphic/Sprite.h"
#include "Graphic/Texture.h"

namespace CC {

OreSilo::OreSilo(sf::Vector2u position) :
    Building(position) {
    sf::Sprite sprite;
    sprite.setTexture(
                TextureCollection::Get(TextureCollection::Id::SpriteSheet));
    sprite.setTextureRect(Sprite::Get(Sprite::OreSilo));
    Get<sf::Sprite>("Sprite") = sprite;


    unsigned int& ore = Get<unsigned int>("Ore");
    unsigned int& maxOre = Get<unsigned int>("MaxOre");
    int& PG = Get<int>("PG");

    //unsigned int& highscore = Get<unsigned int>("HighScore");

    ore = 0;
    maxOre = 50;
    PG = -5;
    //highscore = 0;
    //highscore = highscore + ore;

    Get<std::string>("Name") = "OreSilo";
    Get<unsigned int>("Cost") = 30;




    Get<std::function<void(ActionEventArg)>>("PlayerUseFunc") =
            [&](ActionEventArg arg) { TransferOre(arg); };

    Get<std::function<std::string()>>("TextFunc") =
            [&]() {
        return "Ore : " + std::to_string(ore) +
               "/" + std::to_string(maxOre) + "\n" +
               "Power used :" + std::to_string(PG) + "MW";
    };
}

bool OreSilo::Load(const std::vector<std::string>& split) {
    if (split.size() != 5)
        return false;

    Get<unsigned int>("Ore") = std::stoul(split[1]);
    Get<unsigned int>("MaxOre") = std::stoul(split[2]);
    Get<unsigned int>("Cost") = std::stoul(split[3]);
    Get<int>("PG") = std::stol(split[4]);
    //Get<unsigned int>("HighScore") = std::stoul(split[5]);

    return true;
}

std::string OreSilo::Save() {
    std::string saveStr = "OreSilo " +
            std::to_string(Get<unsigned int>("Ore")) + " " +
            std::to_string(Get<unsigned int>("MaxOre")) + " " +
            std::to_string(Get<unsigned int>("Cost")) + " " +
            std::to_string(Get<int>("PG"));
            //std::to_string(Get<unsigned int>("HighScore"));

    return saveStr;
}

void OreSilo::TransferOre(ActionEventArg arg) {
    Player& player = arg.Gam.GetPlayer();

    unsigned int& siloOre = Get<unsigned int>("Ore");
    unsigned int& siloMaxOre = Get<unsigned int>("MaxOre");

    unsigned int& playerOre = player.Get<unsigned int>("Ore");

    unsigned int maxOreTransferable = siloMaxOre - siloOre;
    unsigned int oreTransfered = 0;

    if (playerOre > maxOreTransferable) {
        oreTransfered = maxOreTransferable;
        playerOre -= maxOreTransferable;
        siloOre += maxOreTransferable;
    } else {
        oreTransfered = playerOre;
        siloOre += playerOre;
        playerOre = 0;
    }

    sf::Vector2u& position = Get<sf::Vector2u>("Position");

    sf::Vector2f textStartingPosition(
                static_cast<float>(position.x * Sprite::Size),
                static_cast<float>(position.y * Sprite::Size));

    arg.AnimManager.AddAnimation(
                new FloatingCombatText(
                    std::to_string(oreTransfered) + " ore transfered.",
                    textStartingPosition));
}

}




