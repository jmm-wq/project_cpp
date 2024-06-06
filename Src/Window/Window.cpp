#include "Window/Window.h"

#include <chrono>
#include <ctime>
#include <iostream>
#include <string>

#include "Graphic/Sprite.h"
#include "Graphic/Texture.h"

//#define _RECORDING_

namespace CC {

Window::Window() :
    game(*this),
    playerStats(game.GetPlayer(), game.GetBase()) {
    window.create(
                sf::VideoMode(1.5*Size.x, 1.5*Size.y),
                "SpaceFactory",
                sf::Style::Close
#ifdef _RECORDING_
                | sf::Style::Fullscreen
#endif
                );
    ActionEvents[Action::Screenshot]
            += new ActionEvent::T<Window>(this, &Window::TakeScreenshot);

    if (Size.x < Size.y)
        throw std::string("Window width cannot be inferior to height");

    worldView.setSize(sf::Vector2f(Size.y, Size.y));

    worldView.setViewport(sf::FloatRect(0.f, 0.f, static_cast<float>(Size.y) /
                                        static_cast<float>(Size.x), 1.f));

    playerStatUiView.setSize(sf::Vector2f(Size.x - Size.y, Size.y * 0.5f));

    float uiWidth = static_cast<float>(Size.x - Size.y) /
                    static_cast<float>(Size.x);

    playerStatUiView.setViewport(sf::FloatRect(1.0f - uiWidth, 0.f,
                                               uiWidth, 0.5f));

    playerStatUiView.setCenter(sf::Vector2f(playerStatUiView.getSize().x / 2,
                                            playerStatUiView.getSize().y / 2));

    otherUiView.setSize(sf::Vector2f(Size.x - Size.y, Size.y * 0.5f));

    otherUiView.setViewport(sf::FloatRect(1.0f - uiWidth, 0.5f,
                                          uiWidth, 0.5f));

    otherUiView.setCenter(sf::Vector2f(otherUiView.getSize().x / 2,
                                       otherUiView.getSize().y / 2));
}

void Window::Run() {
    if (!TextureCollection::Load())
        window.close();

    Font.loadFromFile("./Assets/arial.ttf");

    game.Init();

    while (window.isOpen()) {
        HandleEvents();

        window.clear(sf::Color::Black);

        UpdateView();
        playerStats.Update();
        entityStats.Update(game.GetPlayer().GetFacingEntity());

        animationManager.Update();

        window.setView(worldView);
        window.draw(game);
        window.draw(animationManager);

        window.setView(playerStatUiView);
        window.draw(playerStats);

        window.setView(otherUiView);
        window.draw(entityStats);


        window.display();
    }
}

void Window::UpdateView() {
    sf::Vector2f center(
                static_cast<float>(
                    game.GetPlayer().Get<sf::Vector2u>("Position").x *
                    Sprite::Size+Sprite::Size/2),
                static_cast<float>(
                    game.GetPlayer().Get<sf::Vector2u>("Position").y *
                    Sprite::Size+Sprite::Size/2));

    if (center.x < worldView.getSize().x / 2.f)
        center.x = worldView.getSize().x / 2.f;

    if (center.x > game.GetWorld().GetSize().x * Sprite::Size -
                   worldView.getSize().x / 2.f)
        center.x = game.GetWorld().GetSize().x * Sprite::Size -
                   worldView.getSize().x / 2.f;

    if (center.y < worldView.getSize().y / 2.f)
        center.y = worldView.getSize().y / 2.f;

    if (center.y > game.GetWorld().GetSize().y * Sprite::Size -
                   worldView.getSize().y / 2.f)
        center.y = game.GetWorld().GetSize().y * Sprite::Size -
                   worldView.getSize().y / 2.f;

    worldView.setCenter(center);
}

void Window::HandleEvents() {
    // Check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (window.pollEvent(event)) {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            Action currentAction = actionManager.GetAction(event.key.code);
            if (currentAction != Action::Blank) {
                ActionEventsMap::iterator it =
                        ActionEvents.find(currentAction);

                if (it != ActionEvents.end()) {
                    bool endTurn;
                    ActionEventArg arg(
                                currentAction,
                                event.key.code,
                                game,
                                endTurn,
                                animationManager);
                    it->second(arg);
                    if (endTurn)
                        game.Resolve();
                }
            }
        }
    }
}

void Window::TakeScreenshot(ActionEventArg arg) {
    sf::Texture screenTex;
    screenTex.create(Size.x, Size.y);
    screenTex.update(window);
    sf::Image screenImg = screenTex.copyToImage();
    std::time_t time =
            std::chrono::system_clock::to_time_t(
                std::chrono::system_clock::now());
    char datetime[512];
    std::size_t datetimesize =
            strftime(datetime, 512, "%Y%m%d-%H%M%S", std::localtime(&time));
    std::string filename(datetime, datetimesize);
    filename = "screenshot-"+filename+".png";
    screenImg.saveToFile(filename);
}

const sf::Vector2u Window::Size = sf::Vector2u(640, 480);
sf::Font Window::Font;

}
