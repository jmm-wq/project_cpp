#include "Game/Player.h"

#include <string>

#include "Graphic/FloatingCombatText.h"
#include "Graphic/Sprite.h"
#include "Graphic/Texture.h"
#include "Window/Window.h"

namespace CC {

Player::Player(sf::Vector2u position, Game& game) :
    Entity(position),
    game(game) {
    sf::Sprite sprite;
    sprite.setTexture(
                TextureCollection::Get(TextureCollection::Id::SpriteSheet));
    sprite.setTextureRect(Sprite::Get(Sprite::PlayerShip));
    sprite.setPosition(Sprite::Size/2.f, Sprite::Size/2.f);
    sprite.setOrigin(Sprite::Size/2.f, Sprite::Size/2.f);
    Get<sf::Sprite>("Sprite") = sprite;

    game.GetWindow().ActionEvents[Action::MoveLeft] +=
            new Window::ActionEvent::T<Player>(this, &Player::MoveLeft);
    game.GetWindow().ActionEvents[Action::MoveRight] +=
            new Window::ActionEvent::T<Player>(this, &Player::MoveRight);
    game.GetWindow().ActionEvents[Action::MoveUp] +=
            new Window::ActionEvent::T<Player>(this, &Player::MoveUp);
    game.GetWindow().ActionEvents[Action::MoveDown] +=
            new Window::ActionEvent::T<Player>(this, &Player::MoveDown);
    game.GetWindow().ActionEvents[Action::Mine] +=
            new Window::ActionEvent::T<Player>(this, &Player::Mine);

    Get<sf::Vector2i>("Facing") = sf::Vector2i(1, 0);

    Get<unsigned int>("Ore") = 0;
    Get<unsigned int>("MaxOre") = 30;

    Get<std::string>("Name") = "Player";
}

Entity* Player::GetFacingEntity() const {
    const sf::Vector2i& facing = Get<sf::Vector2i>("Facing");
    const sf::Vector2u& position = Get<sf::Vector2u>("Position");
    if ((facing.x == -1 && position.x == 0) ||
        (facing.y == -1 && position.y == 0) ||
        (facing.x == 1  && position.x == game.GetWorld().GetSize().x - 1) ||
        (facing.y == 1  && position.y == game.GetWorld().GetSize().y - 1) )
        return nullptr;

    sf::Vector2u facingPosition(
        static_cast<unsigned int>(static_cast<int>(position.x) + facing.x),
        static_cast<unsigned int>(static_cast<int>(position.y) + facing.y));

    return game.GetWorld().T(facingPosition).Ent;
}

bool Player::IsFacingValid() const {
    const sf::Vector2i& facing = Get<sf::Vector2i>("Facing");
    const sf::Vector2u& position = Get<sf::Vector2u>("Position");
    if ((facing.x == -1 && position.x == 0) ||
        (facing.y == -1 && position.y == 0) ||
        (facing.x == 1  && position.x == game.GetWorld().GetSize().x - 1) ||
        (facing.y == 1  && position.y == game.GetWorld().GetSize().y - 1) )
        return false;
    else
        return true;
}

sf::Vector2u Player::GetFacingPosition() const {
    const sf::Vector2i& facing = Get<sf::Vector2i>("Facing");
    const sf::Vector2u& position = Get<sf::Vector2u>("Position");

    sf::Vector2u facingPosition(
        static_cast<unsigned int>(static_cast<int>(position.x) + facing.x),
        static_cast<unsigned int>(static_cast<int>(position.y) + facing.y));

    return facingPosition;
}


void Player::Mine(ActionEventArg arg) {
    Entity* facingEntity = GetFacingEntity();

    if (facingEntity == nullptr)
        return;

    if (facingEntity->HasID("Ore")) {
        unsigned int& ore = facingEntity->Get<unsigned int>("Ore");
        unsigned int& Ore = Get<unsigned int>("Ore");
        unsigned int& maxOre = Get<unsigned int>("MaxOre");
        unsigned int oreMined = ore;

        if (ore > 3) {
            ore -= 3;
            Ore += 3;
        } else {
            Ore += ore;
            ore = 0;
        }

        if (Ore > maxOre) {
            unsigned int overOre = Ore - maxOre;
            Ore = maxOre;
            ore += overOre;
        }

        oreMined -= ore;

        sf::Vector2i& facing = Get<sf::Vector2i>("Facing");
        sf::Vector2u& position = Get<sf::Vector2u>("Position");
        sf::Vector2u facingPosition(
        static_cast<unsigned int>(static_cast<int>(position.x) + facing.x),
        static_cast<unsigned int>(static_cast<int>(position.y) + facing.y));
        sf::Vector2f textStartingPosition(
                    static_cast<float>(facingPosition.x * Sprite::Size),
                    static_cast<float>(facingPosition.y * Sprite::Size));

        arg.AnimManager.AddAnimation(
                    new FloatingCombatText(
                        std::to_string(oreMined) + " ore mined !",
                        textStartingPosition));

        arg.EndTurn = true;
    }
}

void Player::MoveLeft(ActionEventArg arg) {
    sf::Vector2u destination = Get<sf::Vector2u>("Position");
    if (destination.x > 0) {
        destination.x -= 1;
        arg.EndTurn = arg.EndTurn ||
                      game.GetWorld().Move(this, destination);
    }
    Get<sf::Sprite>("Sprite").setRotation(180.0);
    Get<sf::Vector2i>("Facing") = sf::Vector2i(-1, 0);
}

void Player::MoveRight(ActionEventArg arg) {
    sf::Vector2u destination = Get<sf::Vector2u>("Position");
    destination.x += 1;
    arg.EndTurn = arg.EndTurn || game.GetWorld().Move(this, destination);
    Get<sf::Sprite>("Sprite").setRotation(0.0);
    Get<sf::Vector2i>("Facing") = sf::Vector2i(1, 0);
}

void Player::MoveUp(ActionEventArg arg) {
    sf::Vector2u destination = Get<sf::Vector2u>("Position");
    if (destination.y > 0) {
        destination.y -= 1;
        arg.EndTurn = arg.EndTurn ||
                      game.GetWorld().Move(this, destination);
    }
    Get<sf::Sprite>("Sprite").setRotation(270.0);
    Get<sf::Vector2i>("Facing") = sf::Vector2i(0, -1);
}

void Player::MoveDown(ActionEventArg arg) {
    sf::Vector2u destination = Get<sf::Vector2u>("Position");
    destination.y += 1;
    arg.EndTurn = arg.EndTurn || game.GetWorld().Move(this, destination);
    Get<sf::Sprite>("Sprite").setRotation(90.0);
    Get<sf::Vector2i>("Facing") = sf::Vector2i(0, 1);
}

}



