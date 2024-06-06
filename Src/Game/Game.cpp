#include "Game/Game.h"

#include <functional>
#include <string>
#include <chrono>

#include "Game/Buildings/Core.h"
#include "Game/Buildings/OreSilo.h"
#include "Graphic/FloatingCombatText.h"
#include "Graphic/Texture.h"
#include "Graphic/Sprite.h"
#include "Window/Window.h"

namespace CC {

Game::Game(Window& window) :
    window(window),
    player(sf::Vector2u(0, 10), *this),
    enemy(sf::Vector2u(8, 10), *this),
    base(factory.GetBase()) {
    window.ActionEvents[Action::Jump] +=
           new Window::ActionEvent::T<Game>(this, &Game::PlayerJump);
    window.ActionEvents[Action::Build] +=
           new Window::ActionEvent::T<Game>(this, &Game::PlayerBuild);
    window.ActionEvents[Action::Use] +=
           new Window::ActionEvent::T<Game>(this, &Game::PlayerUse);
    baseMode = true;
}

Game::~Game() {
    Unload();
}

void Game::Init() {
    factory.Load();

    Load();
}

void Game::Load() {
    world.GenerateRandomBackground();
    world.GenerateTiles(!baseMode);
    world.AddEntity(&player);

    unsigned int availableOre = base.GetAvailableOre();
    if (availableOre > 100){
    world.AddEntity(&enemy);
    }
    //ey = rand() % (10) + 10;

    if (!baseMode) {
        entities = world.GenerateEntities();
        //
        //ey = rand() % (10) + 10;
        if (availableOre > 100){
    world.AddEntity(&enemy);
    }
    //
    } else {
        world.SetupBase(base);
    }
}

void Game::Unload() {
    for (Entity* entity : entities)
        delete entity;
    entities.clear();
}

void Game::Resolve() {
}

void Game::PlayerJump(ActionEventArg arg) {
    player.Get<sf::Vector2u>("Position") = sf::Vector2u(0, 10);
    Unload();
    baseMode = !baseMode;
    //Load();
//
        world.GenerateTiles(!baseMode);
    world.AddEntity(&player);
    //now miner drone
    unsigned int availableOre = base.GetAvailableOre();
    if (availableOre > 100){
    world.AddEntity(&enemy);
    }

    if (!baseMode) {
        entities = world.GenerateEntities();

        if (availableOre > 100){
    world.AddEntity(&enemy);
    }
         //ey = rand() % (10) + 10;
    } else {
        world.SetupBase(base);
    }
//*/



}

void Game::PlayerBuild(ActionEventArg arg) {
    if (baseMode &&
        player.IsFacingValid() &&
        player.GetFacingEntity() == nullptr) {
        Building* silo = new OreSilo(player.GetFacingPosition());

        unsigned int availableOre = base.GetAvailableOre();
        unsigned int cost = silo->Get<unsigned int>("Cost");

        unsigned int freePG = base.GetFreePowerGrid();
        unsigned int PGUsed = std::abs(silo->Get<int>("PG"));

        std::string errorMessage = "";

        if (cost <= availableOre) {
            if (PGUsed <= freePG) {
                base.GetBuildings().push_back(silo);
                base.RemoveOre(cost);
                world.AddEntity(silo);
                factory.Save();
                arg.EndTurn = true;
            } else {
                Building* core = new Core(player.GetFacingPosition());
                base.GetBuildings().push_back(core);
                base.RemoveOre(cost);
                world.AddEntity(core);
                factory.Save();
                arg.EndTurn = true;
                /*
                errorMessage += "Unable to build.\n";
                errorMessage += "PG used : " + std::to_string(PGUsed) + "MW\n";
                errorMessage += "Free PG : " + std::to_string(freePG) + "MW";
                */
            }
        } else {
            errorMessage += "Unable to build.\n";
            errorMessage += "Building cost : " + std::to_string(cost) + "\n";
            errorMessage += "Available ore : " + std::to_string(availableOre);
        }

        if (errorMessage != "") {
            delete silo;
            sf::Vector2u position = player.GetFacingPosition();

            sf::Vector2f textStartingPosition(
                        static_cast<float>(position.x * Sprite::Size),
                        static_cast<float>(position.y * Sprite::Size));



            arg.AnimManager.AddAnimation(
                        new FloatingCombatText(errorMessage,
                                               textStartingPosition));
        }//build blockade outta base
    } else {
        Building* silo = new Core(player.GetFacingPosition());

        //unsigned int availableOre = base.GetAvailableOre();
        //unsigned int cost = silo->Get<unsigned int>("Cost");

       // unsigned int freePG = base.GetFreePowerGrid();
        //unsigned int PGUsed = std::abs(silo->Get<int>("PG"));

        //base.GetBuildings().push_back(silo);
                //base.RemoveOre(cost);
                world.AddEntity(silo);
                //factory.Save();
                arg.EndTurn = true;
    }
    
}











void Game::PlayerUse(ActionEventArg arg) {
    Entity* facingEntity = player.GetFacingEntity();
    if (facingEntity != nullptr && facingEntity->HasID("PlayerUseFunc")) {
        facingEntity->Get<std::function<void(ActionEventArg)>>("PlayerUseFunc")(arg);
        if (baseMode)
            factory.Save();
        arg.EndTurn = true;
    }
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(world, states);

    sf::Transform viewTranslation;
    viewTranslation.translate(window.GetTopLeftCoordinate());
    states.transform = states.transform.combine(viewTranslation);
}

}
