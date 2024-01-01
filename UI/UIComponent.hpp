#ifndef UICOMPONENT_HPP
#define UICOMPONENT_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
class UIComponent {
public:
    enum class Screen {
        MAIN_MENU,
        SETTINGS_MENU,
        GAME_SELECTION_MENU,
        GAME_BASIC_INTERFACE,
        GAME_ULTIMATE_INTERFACE,
        GAME_END_SCREEN,
        RESULT_SCREEN,
        EXIT
    };
    virtual Screen render() = 0;
    virtual ~UIComponent() {}

protected:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Color color;
    sf::Image icon;


    UIComponent(sf::RenderWindow& win) : window(win), color(sf::Color(224, 171, 114)) {
        if (!font.loadFromFile("../data/ttf/TaipeiSansTCBeta-Regular.ttf")) {
            std::cout << "Font load failed\n";
        }
        if (!icon.loadFromFile("../data/images/ui/icon.png")) {
            std::cout << "Texture load failed\n";
        }
    } 
};
#endif