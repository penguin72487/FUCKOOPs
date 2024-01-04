#ifndef SETTINGSMENU_HPP
#define SETTINGSMENU_HPP

#include "UIComponent.hpp"
#include "Button.hpp"
// 設置菜單類
class SettingsMenu : public UIComponent {
private:
    sf::Text ColorSet;
    sf::Text TimeSet;
    Button MenuButton;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
public:
    SettingsMenu(sf::RenderWindow& window) : UIComponent(window),MenuButton(57, 36, 160, 70, "MENU", font) {
        ColorSet = sf::Text("SETTING COLOR", font, 50);
        ColorSet.setFillColor(sf::Color(255, 255, 255));
        ColorSet.setPosition(50, 377);    
        
        TimeSet = sf::Text("SETTING TIME", font, 50);
        TimeSet.setFillColor(sf::Color(255, 255, 255));
        TimeSet.setPosition(50, 622);
    }
    Screen render() override {
        std::cout << "Settings Menu: [Settings Options]" << std::endl;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                // check if buttons are clicked
                if (MenuButton.isClicked(window,event)) {
                    return Screen::MAIN_MENU;
                }
            }
            if (!backgroundTexture.loadFromFile("data/images/bg/Bg1.png")) {
                std::cout << "Texture load failed\n";
            }
            backgroundSprite.setTexture(backgroundTexture);

            window.clear(color);
            window.draw(backgroundSprite);
            // draw title and buttons
            window.draw(ColorSet);
            window.draw(TimeSet);
            window.draw(MenuButton.shape);
            window.draw(MenuButton.text);
            window.display();


        }
        return Screen::MAIN_MENU;
    }
};
#endif