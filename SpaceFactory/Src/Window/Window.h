#ifndef CC_Window

#define CC_Window

#include <SFML/Graphics.hpp>

namespace CC
{
    /**
    *   A window where we will this our game
    */
    class Window
    {
    public:
        /**
        *	Construct and open a new window
        */
        Window();
        /**
        *	Window main loop, handle events, draw things, ...
        */
        void Run();

    protected:
        /**
        *	Treat all event that happended since the last time we called this
        */
        void HandleEvents();

        sf::RenderWindow window;///< SFML window where we render our game
    };
}

#endif // CC_WINDOW
