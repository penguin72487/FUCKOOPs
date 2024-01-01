#include "UIComponent.h"
#include <iostream>

UIComponent::UIComponent(sf::RenderWindow& win) : window(win), color(sf::Color(224, 171, 114)) {
    if (!font.loadFromFile("TaipeiSansTCBeta-Regular.ttf")) {
        std::cout << "Font load failed\n";
    }
    if (!icon.loadFromFile("OOXX.png")) {
        std::cout << "Texture load failed\n";
    }
}
