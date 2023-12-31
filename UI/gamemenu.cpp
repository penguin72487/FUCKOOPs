#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include<iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(1400, 1024), "SETTING");
    sf::Font font;
    if (!font.loadFromFile("TaipeiSansTCBeta-Regular.ttf")) {
        // handle error
    }

    sf::Image icon;
    if (!icon.loadFromFile("OOXX.png")) {
        // 圖示載入失敗
        return EXIT_FAILURE;
    }

    // 設定窗口圖示
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // create title
    sf::Text colorset("BASIC\n3*3", font, 65);
    colorset.setFillColor(sf::Color(0, 0, 0));
    colorset.setPosition(722, 262);    
    
    sf::Text timeset("ADVANCE\n9*9", font, 65);
    timeset.setFillColor(sf::Color(0, 0, 0));
    timeset.setPosition(722, 683);


    Button MenuButton(57, 36, 160, 70, "MENU", font);
    Button BasicButton(333, 164, 734, 348, "", font);
    Button AdvanceButton(333, 586, 734, 347, "", font);

    sf::Color color(224, 171, 114);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // check if buttons are clicked
            if (MenuButton.isClicked(event)) {
                // do something
                std::cout << "MenuButton" << std::endl;
            }
            if (BasicButton.isClicked(event)) {

                // do something
                std::cout << "BasicButton" << std::endl;
            }
            if (AdvanceButton.isClicked(event)) {
                // do something
                std::cout << "AdvanceButton" << std::endl;
            }
        }

        window.clear(color);
        // draw title and buttons
        window.draw(MenuButton.shape);
        window.draw(MenuButton.text);
        window.draw(BasicButton.shape);
        window.draw(BasicButton.text);
        window.draw(AdvanceButton.shape);
        window.draw(AdvanceButton.text);
        window.draw(colorset);
        window.draw(timeset);
        window.display();
    }
    
    return 0;
}