// Button.cpp
// #include "Button.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>
#ifndef BUTTON_HPP
#define BUTTON_HPP
class Button {
public:
    sf::RectangleShape shape;
    sf::Text text;

    Button(float x, float y, float width, float height, std::string buttonText, sf::Font& font) {
        setupShape(x, y, width, height);
        setupText(buttonText, font);
    }

    void setupShape(float x, float y, float width, float height) {
        shape.setPosition(sf::Vector2f(x, y));
        shape.setSize(sf::Vector2f(width, height));
        // shape.setOutlineColor(sf::Color(173, 216, 230));
        // shape.setOutlineThickness(2);
        shape.setFillColor(sf::Color(173, 216, 230));
    }

    void setupText(std::string buttonText, sf::Font& font) {
        text.setFont(font);
        text.setString(buttonText);
        text.setCharacterSize(30); // in pixels
        text.setFillColor(sf::Color::Black);
        text.setPosition(
            shape.getPosition().x + (shape.getSize().x / 2) - (text.getGlobalBounds().width / 2),
            shape.getPosition().y + (shape.getSize().y / 2) - (text.getGlobalBounds().height / 2)-8
        );
    }

    bool isClicked(sf::RenderWindow& window, sf::Event event) {
        static bool PreBehRel = false;

        // 創建一個新的 FloatRect 對象，它的位置和大小與按鈕的形狀相同，但是寬度和高度都稍微小一些
        sf::FloatRect innerBounds = shape.getGlobalBounds();
        float padding = 5.0f; // 設定邊框的寬度
        innerBounds.left += padding;
        innerBounds.top += padding;
        innerBounds.width -= 2 * padding;
        innerBounds.height -= 2 * padding;

        if(innerBounds.contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
            if(event.type==sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && PreBehRel)
            {
                PreBehRel = false;
                return true;
            }
            if(event.type==sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left)
            {
                shape.setFillColor(sf::Color(89, 147, 166));
                PreBehRel = true;
            }
            else
                shape.setFillColor(sf::Color(122, 168, 184));
        }
        else
            shape.setFillColor(sf::Color(173,216,230));

        return false;
    }
};
#endif