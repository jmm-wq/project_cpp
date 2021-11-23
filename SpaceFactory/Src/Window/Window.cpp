#include <Window/Window.h>
#include <iostream>

namespace CC
{
    Window::Window()
    {
        window.create(sf::VideoMode(640, 480), "SpaceFactory", sf::Style::Close);
    }

    void Window::Run()
    {
        while (window.isOpen())
        {
            HandleEvents();
        }
    }

    void Window::HandleEvents()
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
}
