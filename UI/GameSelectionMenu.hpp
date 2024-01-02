#ifndef GAMESELECTIONMENU_HPP
#define GAMESELECTIONMENU_HPP

#include "UIComponent.hpp"
#include "Button.hpp"
class GameSelectionMenu : public UIComponent {
private:
    sf::Text BasicText;
    sf::Text AdvanceText;
    Button MenuButton;
    Button BasicButton;
    Button AdvanceButton;
    sf::Texture BasicPictureTexture;
    sf::Sprite BasicPictureSprite;
    sf::Texture UltimatePictureTexture;
    sf::Sprite UltimatePictureSprite;

public:
    GameSelectionMenu(sf::RenderWindow& window) : UIComponent(window),
                                                MenuButton(57, 36, 160, 70, "MENU", font),
                                                BasicButton(333, 164, 734, 348, "", font),
                                                AdvanceButton(333, 586, 734, 347, "", font){
        BasicText=sf::Text("BASIC\n3x3", font, 65);
        BasicText.setFillColor(sf::Color(0, 0, 0));
        BasicText.setPosition(722, 262);    
        
        AdvanceText=sf::Text("ADVANCE\n9x9", font, 65);
        AdvanceText.setFillColor(sf::Color(0, 0, 0));
        AdvanceText.setPosition(722, 683);

        if (!BasicPictureTexture.loadFromFile("data/images/ui/basic.png")) {
            std::cout << "Texture load failed\n";
        }
        BasicPictureSprite.setTexture(BasicPictureTexture);
        BasicPictureSprite.setScale(0.15, 0.15);
        BasicPictureSprite.setPosition(375, 190);
        
        if (!UltimatePictureTexture.loadFromFile("data/images/ui/ultimate.png")) {
            std::cout << "Texture load failed\n";
        }
        UltimatePictureSprite.setTexture(UltimatePictureTexture);
        UltimatePictureSprite.setScale(0.3, 0.3);
        UltimatePictureSprite.setPosition(375, 620);
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
            window.draw(BasicText);
            window.draw(AdvanceText);
            window.draw(BasicPictureSprite);
            window.draw(UltimatePictureSprite);

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