#ifndef GAMESELECTIONMENU_HPP
#define GAMESELECTIONMENU_HPP

#include "UIComponent.hpp"
#include "Button.hpp"
class GameSelectionMenu : public UIComponent {
private:
    sf::Text basictext;
    sf::Text advancetext;
    Button MenuButton;
    Button BasicButton;
    Button AdvanceButton;
    sf::Texture basicpic;
    sf::Sprite basicpicture;
    sf::Texture ultimatepic;
    sf::Sprite ultimatepicture;

public:
    GameSelectionMenu(sf::RenderWindow& window) : UIComponent(window),
                                                MenuButton(57, 36, 160, 70, "MENU", font),
                                                BasicButton(333, 164, 734, 348, "", font),
                                                AdvanceButton(333, 586, 734, 347, "", font){
        basictext=sf::Text("BASIC\n3x3", font, 65);
        basictext.setFillColor(sf::Color(0, 0, 0));
        basictext.setPosition(722, 262);    
        
        advancetext=sf::Text("ADVANCE\n9x9", font, 65);
        advancetext.setFillColor(sf::Color(0, 0, 0));
        advancetext.setPosition(722, 683);

        if (!basicpic.loadFromFile("../data/png/ui/basic.png")) {
            std::cout << "Texture load failed\n";
        }
        basicpicture.setTexture(basicpic);
        basicpicture.setScale(0.15, 0.15);
        basicpicture.setPosition(375, 190);
        
        if (!ultimatepic.loadFromFile("../data/png/ui/ultimate.png")) {
            std::cout << "Texture load failed\n";
        }
        ultimatepicture.setTexture(ultimatepic);
        ultimatepicture.setScale(0.3, 0.3);
        ultimatepicture.setPosition(375, 620);
    }
    Screen render() override {
        std::cout << "Game Selection Menu: [List of Games]" << std::endl;
        while(window.isOpen()){
            window.clear(color);

            
            window.draw(BasicButton.shape);
            window.draw(BasicButton.text);
            window.draw(AdvanceButton.shape);
            window.draw(AdvanceButton.text);
            window.draw(MenuButton.shape);
            window.draw(MenuButton.text);
            window.draw(basictext);
            window.draw(advancetext);
            window.draw(basicpicture);
            window.draw(ultimatepicture);

            window.display();
            sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();

                    // check if buttons are clicked
                    if (BasicButton.isClicked(event)) {
                        std::cout << "select Basic Game: [Gameplay Elements]" << std::endl;
                        return Screen::GAME_BASIC_INTERFACE;
                    }
                    if (AdvanceButton.isClicked(event)) {
                        std::cout << "select Advance Game: [Gameplay Elements]" << std::endl;
                        return Screen::GAME_ULTIMATE_INTERFACE;
                    }
                    if (MenuButton.isClicked(event)) {
                        return Screen::MAIN_MENU;
                    }
                    
                }

        }
        return Screen::MAIN_MENU;
    }
};

#endif