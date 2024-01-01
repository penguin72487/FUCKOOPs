#include "GameSelectionMenu.h"
#include <iostream>

GameSelectionMenu::GameSelectionMenu(sf::RenderWindow& window) : UIComponent(window),
    MenuButton(57, 36, 160, 70, "MENU", font),
    BasicButton(333, 164, 734, 348, "", font),
    AdvanceButton(333, 586, 734, 347, "", font) {

    basictext = sf::Text("BASIC\n3x3", font, 65);
    basictext.setFillColor(sf::Color(0, 0, 0));
    basictext.setPosition(722, 262);

    advancetext = sf::Text("ADVANCE\n9x9", font, 65);
    advancetext.setFillColor(sf::Color(0, 0, 0));
    advancetext.setPosition(722, 683);
}

UIComponent::Screen GameSelectionMenu::render() {
    std::cout << "Game Selection Menu: [List of Games]" << std::endl;
    while (window.isOpen()) {
        window.clear(color);

        window.draw(BasicButton.shape);
        window.draw(BasicButton.text);
        window.draw(AdvanceButton.shape);
        window.draw(AdvanceButton.text);
        window.draw(MenuButton.shape);
        window.draw(MenuButton.text);
        window.draw(basictext);
        window.draw(advancetext);

        window.display();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // check if buttons are clicked
            if (BasicButton.isClicked(event)) {
                return Screen::GAME_INTERFACE;
            }
            if (AdvanceButton.isClicked(event)) {
                return Screen::GAME_INTERFACE;
            }
            if (MenuButton.isClicked(event)) {
                return Screen::MAIN_MENU;
            }
        }
    }
    return Screen::MAIN_MENU;
}
