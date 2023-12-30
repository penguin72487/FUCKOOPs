// Button.cpp
#include "Button.h"

Button::Button(float x, float y, float width, float height, std::string buttonText, sf::Font& font) {
    shape.setPosition(sf::Vector2f(x, y));
    shape.setSize(sf::Vector2f(width, height));

    text.setFont(font);
    text.setString(buttonText);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(
        shape.getPosition().x + (shape.getGlobalBounds().width / 2) - (text.getGlobalBounds().width / 2),
        shape.getPosition().y + (shape.getGlobalBounds().height / 2) - (text.getGlobalBounds().height / 2)
    );
}

bool Button::isClicked(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (shape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                return true;
            }
        }
    }
    return false;
}
