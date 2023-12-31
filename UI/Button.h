// Button.h
#pragma once
#include <SFML/Graphics.hpp>
#ifndef BUTTON_H
#define BUTTON_H

class Button {
public:
    sf::RectangleShape shape;
    sf::Text text;

    Button(float x, float y, float width, float height, std::string buttonText, sf::Font& font);
    bool isClicked(sf::Event event);
};
# endif