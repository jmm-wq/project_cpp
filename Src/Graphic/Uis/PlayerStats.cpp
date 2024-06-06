#include "Graphic/Uis/PlayerStats.h"

#include "Graphic/Texture.h"
#include "Graphic/Sprite.h"
#include "Window/Window.h"

namespace CC {

PlayerStats::PlayerStats(Player& player, Base& base) :
    player(player),
    base(base) {
    portrait.setTexture(
                TextureCollection::Get(TextureCollection::Id::SpriteSheet));
    portrait.setTextureRect(Sprite::Get(Sprite::Portrait));
    portrait.setPosition(8, 12);

    name.setString("Player");
    name.setFillColor(sf::Color::White);
    name.setPosition(80, 12);
    name.setFont(Window::Font);
    name.setCharacterSize(18);
    name.setStyle(sf::Text::Bold | sf::Text::Underlined);


    ore.setString("Ore : " +
                  std::to_string(player.Get<unsigned int>("Ore")) +
                  "/" + std::to_string(player.Get<unsigned int>("MaxOre")));
    ore.setFillColor(sf::Color::White);
    ore.setPosition(6, 50);
    ore.setFont(Window::Font);
    ore.setCharacterSize(12);

    basePG.setFillColor(sf::Color::White);
    basePG.setPosition(6, 60);
    basePG.setFont(Window::Font);
    basePG.setCharacterSize(12);

    goal.setFillColor(sf::Color::White);
    goal.setPosition(6, 116);
    goal.setFont(Window::Font);
    goal.setCharacterSize(13);

    upgrade.setFillColor(sf::Color::White);
    upgrade.setPosition(6, 150);
    upgrade.setFont(Window::Font);
    upgrade.setCharacterSize(10);

    highscore.setFillColor(sf::Color::White);
    highscore.setPosition(6, 86);
    highscore.setFont(Window::Font);
    highscore.setCharacterSize(12);

    controls.setFillColor(sf::Color::White);
    controls.setPosition(8, 176);
    controls.setFont(Window::Font);
    controls.setCharacterSize(10);

    elements.push_back(&portrait);
    elements.push_back(&name);
    elements.push_back(&ore);
    //elements.push_back(&baseOre);
    elements.push_back(&basePG);
    elements.push_back(&goal);
    elements.push_back(&upgrade);
    elements.push_back(&controls);
    elements.push_back(&highscore);

//
/*
    unsigned int& HighScore = Get<unsigned int>("HighScore");
    HighScore = base.GetAvailableOre();
    */
}

void PlayerStats::Update() {
    ore.setString("Ore : " +
                  std::to_string(player.Get<unsigned int>("Ore")) +
                  "/" + std::to_string(player.Get<unsigned int>("MaxOre")));
    //baseOre.setString("Ore in base : " + std::to_string(base.GetAvailableOre()));
    basePG.setString("Free power in base : " +
                     std::to_string(base.GetFreePowerGrid()) + "MW");
    highscore.setString("High Score : " + std::to_string(base.GetAvailableOre())); 
    if (base.GetAvailableOre() < 100)   {            
    goal.setString("Goal: Collect 300 Ore");
    upgrade.setString("Collect 100 Ore to upgrade");
    } else if (base.GetAvailableOre() > 299) {
    goal.setString("Goal: Reached\nCongratulation!");
    upgrade.setString("You unlocked miner drone!");
    }
    else {
    goal.setString("Goal: Collect 300 Ore");
    upgrade.setString("You unlocked miner drone!");
    }
    controls.setString("Controls:\nWASD: Move, Space: Jump\nL: Build, J: Mine\nK: Deposit, Ins: Prnt Screen");
}

/*
bool PlayerStats::Load(const std::vector<std::string>& split) {
    if (split.size() != 2)
        return false;

    Get<unsigned int>("HighScore") = std::stoul(split[1]);

    return true;
}

std::string PlayerStats::Save() {
    std::string saveStr = "HighScore " +
            std::to_string(Get<unsigned int>("HighScore"));

    return saveStr;
}
*/
}
