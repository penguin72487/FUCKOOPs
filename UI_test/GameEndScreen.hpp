#include "GameEndScreen.h"
#include <iostream>

GameEndScreen::GameEndScreen(sf::RenderWindow& window) : UIComponent(window),
    AgainButton(560, 512, 280, 85, "Again", font),
    ResultButton(560, 687, 280, 85, "Result", font),
    BackButton(560, 862, 280, 85, "Menu", font) {

    winMessege = sf::Text("Player__ Win!!", font, 80);
    winMessege.setFillColor(sf::Color(255, 255, 255));
    winMessege.setPosition(420, 83);
}

UIComponent::Screen GameEndScreen::render() {
    // std::cout << "Game End: [Gameplay Elements]" << std::endl;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // check if buttons are clicked
            if (AgainButton.isClicked(event)) {
                return Screen::GAME_INTERFACE;
            }
            if (ResultButton.isClicked(event)) {
                return Screen::RESULT_SCREEN;
            }
            if (BackButton.isClicked(event)) {
                return Screen::MAIN_MENU;
            }
        }

        window.clear(color);
        // draw title and buttons
        window.draw(winMessege);
        window.draw(AgainButton.shape);
        window.draw(AgainButton.text);
        window.draw(ResultButton.shape);
        window.draw(ResultButton.text);
        window.draw(BackButton.shape);
        window.draw(BackButton.text);
        window.display();
    }
    return Screen::MAIN_MENU;
}
