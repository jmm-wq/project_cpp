//
/*
#include "Game/Enemy.h"

#include <string>

#include "Graphic/Sprite.h"
#include "Graphic/Texture.h"
#include "Window/Window.h"

namespace CC {

    Enemy::Enemy(sf::Vector2u position, Game& game):
    Entity(position),
    game(game) {
        sf::Sprite sprite;
        sprite.setTexture(
            TextureCollection::Get(TextureCollection::Id::SpriteSheet));
        sprite.setTextureRect(Sprite::Get(/Enemy/));
        sprite.setPosition(Sprite::Size/2.f, Sprite::Size/2.f);
        sprite.setOrigin(Sprite::Size/2.f, Sprite::Size/2.f);
        Get<sf::Sprite>("Sprite") = sprite;

        game.GetWindow().ActionEvents[Action::MoveLeft] +=
            new Window::ActionEvent::T<Enemy>(this, &Enemy::MoveLeft);
        game.GetWindow().ActionEvents[Action::MoveRight] +=
            new Window::ActionEvent::T<Enemy>(this, &Enemy::MoveRight);
        game.GetWindow().ActionEvents[Action::MoveUp] +=
            new Window::ActionEvent::T<Enemy>(this, &Enemy::MoveUp);
        game.GetWindow().ActionEvents[Action::MoveDown] +=
            new Window::ActionEvent::T<Enemy>(this, &Enemy::MoveDown);

    Get<sf::Vector2i>("Facing") = sf::Vector2i(0, 1);


    }

    Entity* Enemy::GetFacingEntity() const {
        const sf::Vector2i& facing = Get<sf::Vector2i>("Facing");
        const sf::Vector2u& position = Get<sf::Vector2u>("Position");
        if
    }



//
void Enemy::Move()
{
    //cout << "Move" << endl;

    // Make movement
    Vector2f EnemyPosition = EntityManager::Instance().Enemy.GetPosition();
    Vector2f thisPosition;
    thisPosition.x = xPos;
    thisPosition.y = yPos;
    //Vector2f direction = normalize(EnemyPosition - thisPosition);

    speed = 5;
    //EntityManager::Instance().enemy.enemyVisual.move(speed * direction);
}

Vector2f normalize(const Vector2f& source)
{
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return Vector2f(source.x / length, source.y / length);
    else
        return source;
}

//
void Enemy::MoveLeft(ActionEventArg arg) {
    sf::Vector2u destination = Get<sf::Vector2u>("Position");
    if (destination.x > 0) {
        destination.x -= 1;
        arg.EndTurn = arg.EndTurn ||
                      game.GetWorld().Move(this, destination);
    }
    Get<sf::Sprite>("Sprite").setRotation(180.0);
    Get<sf::Vector2i>("Facing") = sf::Vector2i(-1, 0);

//*
}
//*/
#include "Game/Enemy.h"

#include <string>

#include "Graphic/FloatingCombatText.h"
#include "Graphic/Sprite.h"
#include "Graphic/Texture.h"
#include "Window/Window.h"

namespace CC {

Enemy::Enemy(sf::Vector2u position, Game& game) :
    Entity(position),
    game(game) {
    sf::Sprite sprite;
    sprite.setTexture(
                TextureCollection::Get(TextureCollection::Id::SpriteSheet));
    sprite.setTextureRect(Sprite::Get(Sprite::RemoteMiner));
    sprite.setPosition(Sprite::Size/2.f, Sprite::Size/2.f);
    sprite.setOrigin(Sprite::Size/2.f, Sprite::Size/2.f);
    Get<sf::Sprite>("Sprite") = sprite;

    game.GetWindow().ActionEvents[Action::MoveLeft] +=
            new Window::ActionEvent::T<Enemy>(this, &Enemy::MoveLeft);
    game.GetWindow().ActionEvents[Action::MoveRight] +=
            new Window::ActionEvent::T<Enemy>(this, &Enemy::MoveRight);
    game.GetWindow().ActionEvents[Action::MoveUp] +=
            new Window::ActionEvent::T<Enemy>(this, &Enemy::MoveUp);
    game.GetWindow().ActionEvents[Action::MoveDown] +=
            new Window::ActionEvent::T<Enemy>(this, &Enemy::MoveDown);
    game.GetWindow().ActionEvents[Action::Mine] +=
            new Window::ActionEvent::T<Enemy>(this, &Enemy::Mine);

    Get<sf::Vector2i>("Facing") = sf::Vector2i(1, 0);

//
Get<unsigned int>("Ore") = 0;
    Get<unsigned int>("MaxOre") = 30;

    Get<std::string>("Name") = "Miner Drone";
}

Entity* Enemy::GetFacingEntity() const {
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

bool Enemy::IsFacingValid() const {
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

sf::Vector2u Enemy::GetFacingPosition() const {
    const sf::Vector2i& facing = Get<sf::Vector2i>("Facing");
    const sf::Vector2u& position = Get<sf::Vector2u>("Position");

    sf::Vector2u facingPosition(
        static_cast<unsigned int>(static_cast<int>(position.x) + facing.x),
        static_cast<unsigned int>(static_cast<int>(position.y) + facing.y));

    return facingPosition;
}
//Remote Mine

void Enemy::Mine(ActionEventArg arg) {
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


void Enemy::MoveLeft(ActionEventArg arg) {
    sf::Vector2u destination = Get<sf::Vector2u>("Position");
    if (destination.x > 0) {
        destination.x -= 1;
        arg.EndTurn = arg.EndTurn ||
                      game.GetWorld().Move(this, destination);
    }
    Get<sf::Sprite>("Sprite").setRotation(180.0);
    Get<sf::Vector2i>("Facing") = sf::Vector2i(-1, 0);
}

void Enemy::MoveRight(ActionEventArg arg) {
    sf::Vector2u destination = Get<sf::Vector2u>("Position");
    destination.x += 1;
    arg.EndTurn = arg.EndTurn || game.GetWorld().Move(this, destination);
    Get<sf::Sprite>("Sprite").setRotation(0.0);
    Get<sf::Vector2i>("Facing") = sf::Vector2i(1, 0);
}

void Enemy::MoveUp(ActionEventArg arg) {   //
    sf::Vector2u destination = Get<sf::Vector2u>("Position");
    if (destination.y > 0) {
        destination.y -= 1;
        arg.EndTurn = arg.EndTurn ||
                      game.GetWorld().Move(this, destination);
    }
    Get<sf::Sprite>("Sprite").setRotation(270.0);
    Get<sf::Vector2i>("Facing") = sf::Vector2i(0, -1);
}

void Enemy::MoveDown(ActionEventArg arg) {
    sf::Vector2u destination = Get<sf::Vector2u>("Position");
    destination.y += 1;
    arg.EndTurn = arg.EndTurn || game.GetWorld().Move(this, destination);
    Get<sf::Sprite>("Sprite").setRotation(90.0);
    Get<sf::Vector2i>("Facing") = sf::Vector2i(0, 1);
}

}



