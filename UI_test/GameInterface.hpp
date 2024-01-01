#include "GameInterface.h"
#include <iostream>

GameInterface::GameInterface(sf::RenderWindow& window) : UIComponent(window), MenuButton(57, 36, 160, 70, "MENU", font),
    RestartButton(57, 900, 160, 70, "RESTART", font), board(333, 164, 734, 734, "", font) {
}

UIComponent::Screen GameInterface::render() {
    while (window.isOpen()) {
        window.clear(color);
        // draw title and buttons
        window.draw(MenuButton.shape);
        window.draw(MenuButton.text);
        window.draw(RestartButton.shape);
        window.draw(RestartButton.text);
        window.draw(board.shape);
        window.draw(board.text);
        window.display();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // check if buttons are clicked
            if (MenuButton.isClicked(event)) {
                return Screen::MAIN_MENU;
            }
            if (RestartButton.isClicked(event)) {
                return Screen::GAME_INTERFACE;
            }
            if (board.isClicked(event)) {
                // 棋盤被點擊
                return Screen::GAME_END_SCREEN;
            }
        }
    }

    return Screen::EXIT;
}
