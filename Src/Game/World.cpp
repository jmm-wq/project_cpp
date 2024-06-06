#include "Game/World.h"

#include <chrono>
#include <functional>
#include <string>

#include "Graphic/Sprite.h"
#include "Graphic/Texture.h"
#include "Window/Window.h"

namespace CC {

using IntDistrib = std::uniform_int_distribution<int>;
using UIntDistrib = std::uniform_int_distribution<unsigned int>;

World::World() : size(0, 0) {
    generator = std::mt19937(
                static_cast<unsigned int>(
                    std::chrono::system_clock::now().time_since_epoch().count()));
}

bool World::AddEntity(Entity* entity) {
    Tile& tile = T(entity->Get<sf::Vector2u>("Position"));
    if (tile.Ent != nullptr) {
        return false;
    } else {
        tile.Ent = entity;
        return true;
    }
}

void World::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(background, states);
    for (unsigned int j = 0; j < size.y; j++) {
        for (unsigned int i = 0; i < size.x; i++) {
            target.draw(T(i, j), states);
        }
    }
}

bool World::CanMove(Entity* entity, sf::Vector2u destination) {
    if (destination.x >= size.x || destination.y >= size.y) {
        return false;
    } else if (T(entity->Get<sf::Vector2u>("Position")).Ent == entity) {
        Tile& tile = T(destination);
        if (tile.Ent != nullptr)
            return false;
        else
            return true;
    } else {
        return false;
    }
}

bool World::Move(Entity* entity, sf::Vector2u destination) {
    if (CanMove(entity, destination))  {
        Tile& tileOld = T(entity->Get<sf::Vector2u>("Position"));
        tileOld.Ent = nullptr;
        entity->Get<sf::Vector2u>("Position") = destination;
        Tile& tileNew = T(destination);
        tileNew.Ent = entity;
        return true;
    } else {
        return false;
    }
}

void World::GenerateTiles(bool random) {
    unsigned int minSizeX = Window::Size.x / Sprite::Size;
    unsigned int minSizeY = Window::Size.y / Sprite::Size;
    UIntDistrib distributionX(minSizeX, random ? minSizeX*2 : minSizeX);
    UIntDistrib distributionY(minSizeY, random ? minSizeY*2 : minSizeY);

    size = sf::Vector2u(distributionX(generator), distributionY(generator));

    tiles.clear();
    tiles.resize(size.x*size.y);

    for (unsigned int j = 0; j < size.y; j++) {
        for (unsigned int i = 0; i < size.x; i++) {
            Tile& t = T(i, j);
            t.Position.x = i;
            t.Position.y = j;
            t.setPosition(
                        Sprite::Size * static_cast<float>(i),
                        Sprite::Size * static_cast<float>(j));
        }
    }
}

void World::GenerateRandomBackground() {
    IntDistrib distribution(
                TextureCollection::Id::Andromeda,
                TextureCollection::Id::YellowSun);

    TextureCollection::Id bgTex =
            TextureCollection::Id(distribution(generator));
    background.setTexture(TextureCollection::Get(bgTex));
}

//
unsigned int enemyCount = 20;//distNbenemy(generator);

std::vector<Entity*> World::GenerateEntities() {
    std::vector<Entity*> entities;


    // Asteroids Generation

    UIntDistrib distNbAsteroid(15, 30);
    IntDistrib distAsteroidSprite(Sprite::Asteroid1, Sprite::Asteroid3);
    UIntDistrib distAsteroidXPos(0, size.x-1);
    UIntDistrib distAsteroidYPos(0, size.y-1);
    UIntDistrib distAsteroidOreAmount(50, 100);

    unsigned int asteroidCount = distNbAsteroid(generator);
    for (unsigned int i = 0; i < asteroidCount; i++) {
        sf::Vector2u position(
                    distAsteroidXPos(generator),
                    distAsteroidYPos(generator));

        while (T(position).Ent != nullptr)
           position = sf::Vector2u(
                       distAsteroidXPos(generator),
                       distAsteroidYPos(generator));

        Sprite::Id sprite = Sprite::Id(distAsteroidSprite(generator));

        Entity* asteroid = new Entity(position, sprite);
        asteroid->Get<unsigned int>("Ore") = distAsteroidOreAmount(generator);
        unsigned int& ore = asteroid->Get<unsigned int>("Ore");

        asteroid->Get<std::function<std::string()>>("TextFunc") =
                [&]() {
            return "Ore : " + std::to_string(ore);
        };

        entities.push_back(asteroid);
        T(position).Ent = asteroid;
    }

    //Enemy generation

//unsigned int i;

    UIntDistrib distNbenemy(15, 30);
    IntDistrib distenemySprite(Sprite::Enemy, Sprite::Enemy);//PlayerShip
    UIntDistrib distenemyXPos(0, size.x-1);
    UIntDistrib distenemyYPos(0, size.y-1);
    //UIntDistrib distenemyOreAmount(50, 100);

    //unsigned int enemyCount = 2;//distNbenemy(generator);

    for (unsigned int i = 0; i < enemyCount; i++) {
        sf::Vector2u position(
                    distenemyXPos(generator),
                    distenemyYPos(generator));

        while (T(position).Ent != nullptr)
           position = sf::Vector2u(
                       distenemyXPos(generator),
                       distenemyYPos(generator));

        Sprite::Id sprite = Sprite::Id(distenemySprite(generator));

        Entity* enemy = new Entity(position, sprite);
        enemy->Get<std::string>("Name") = "Gray Matter";
        //enemy->Get<unsigned int>("Ore") = distenemyOreAmount(generator);
        //unsigned int& ore = enemy->Get<unsigned int>("Ore");

        //enemy->Get<std::function<std::string()>>("TextFunc") =
        //        [&]() {
        //    return "Ore : " + std::to_string(ore);
        //};

        entities.push_back(enemy);
        T(position).Ent = enemy;
    }

enemyCount=enemyCount+10;



    return entities;
}




void World::SetupBase(Base& base) {
    for (Entity* ent : base.GetBuildings()) {
        if (!AddEntity(ent))
            std::cerr << "Could not add a building to the world." << std::endl;
    }
}

}
