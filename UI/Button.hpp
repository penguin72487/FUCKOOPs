// Button.cpp
// #include "Button.h"
#include <SFML/Graphics.hpp>

class Button {
public:
    sf::RectangleShape shape;
    sf::Text text;

    Button(float x, float y, float width, float height, std::string buttonText, sf::Font& font) {
        shape.setPosition(sf::Vector2f(x, y));
        shape.setSize(sf::Vector2f(width, height));
        shape.setOutlineColor(sf::Color(224, 171, 114));
        shape.setOutlineThickness(2);
        shape.setFillColor(sf::Color(173, 216, 230));

        text.setFont(font);
        text.setString(buttonText);
        text.setCharacterSize(30); // in pixels
        text.setFillColor(sf::Color::Black);
        text.setPosition(
            shape.getPosition().x + (shape.getSize().x / 2) - (text.getGlobalBounds().width / 2),
            shape.getPosition().y + (shape.getSize().y / 2) - (text.getGlobalBounds().height / 2)-8
        );
    }

    bool isClicked(sf::Event event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (shape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    return true;
                }
            }
        }
        return false;
    }
};