#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include <SFML/Graphics.hpp>

class UIComponent {
public:
    enum class Screen {
        MAIN_MENU,
        SETTINGS_MENU,
        GAME_SELECTION_MENU,
        GAME_INTERFACE,
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

    UIComponent(sf::RenderWindow& win);
};


#endif