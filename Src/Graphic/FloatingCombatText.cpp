#include "Graphic/FloatingCombatText.h"

#include "Graphic/Sprite.h"
#include "Window/Window.h"

namespace CC {

FloatingCombatText::FloatingCombatText(
        std::string floatingText, sf::Vector2f startingPosition) :
    Animation(1.f),
    startingPosition(startingPosition) {
    text.setFont(Window::Font);
    text.setPosition(startingPosition);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1.f);
    text.setCharacterSize(12);
    text.setString(floatingText);
    drawable = &text;
}

void FloatingCombatText::Update() {
    sf::Vector2f position = startingPosition;
    position.y -= (Sprite::Size / 2.f) * timer.getElapsedTime().asSeconds();
    text.setPosition(position);
}

}
