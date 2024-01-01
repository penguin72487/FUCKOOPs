#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "UIComponent.hpp"
#include "Button.hpp"
class MainMenu : public UIComponent {
private:
    enum class Show
    {
        Picture,
        ILLUSTRATE,
        DEVELOPER
    };
    sf::Text title;
    Button illustrateButton, settingButton, startGameButton, exitGameButton, developerButton;
    sf::Texture pic;
    sf::Sprite picture;
    sf::Texture backgroundTexture;//siroku 暫存
    sf::Sprite backgroundSprite;//siroku 暫存
    Show show = Show::Picture;
    sf::Texture illustratepic;
    sf::Sprite illustratepicture;
    sf::Texture developerpic;
    sf::Sprite developerpicture;

public:
    MainMenu(sf::RenderWindow& window) : UIComponent(window), 
        illustrateButton(57, 650, 200, 70, "ILLUSTRATE", font),
        settingButton(57, 500, 200, 70, "SETTING", font),
        startGameButton(57, 350, 200, 70, "START GAME", font),
        exitGameButton(57, 800, 200, 70, "EXIT", font),
        developerButton(1150, 900, 200, 70, "DEVELOPER", font) {

        title = sf::Text("TIC-TAC-TOC", font, 170);
        title.setFillColor(sf::Color::White);
        title.setPosition(57, 57);

        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        if (!pic.loadFromFile("../data/images/ui/OOXX.png")) {
            std::cout << "Texture load failed\n";
        }
        picture.setTexture(pic);
        picture.setScale(1.2, 1.2);
        picture.setPosition(540, 314);
        
        if (!backgroundTexture.loadFromFile("../data/images/bg/Bg1.png")) {
            std::cout << "Texture load failed\n";
        }
        backgroundSprite.setTexture(backgroundTexture);


        //load illustrate
        if (!illustratepic.loadFromFile("../data/images/ui/illustrate.png")) {
            std::cout << "Texture load failed\n";
        }
        illustratepicture.setTexture(illustratepic);
        illustratepicture.setScale(0.27, 0.27);
        illustratepicture.setPosition(325, 300);

        //load developer
        if (!developerpic.loadFromFile("../data/images/ui/developer.png")) {
            std::cout << "Texture load failed\n";
        }
        developerpicture.setTexture(developerpic);
        developerpicture.setScale(0.4, 0.4);
        developerpicture.setPosition(400, 500);
    }

    Screen render() override {
        while (window.isOpen()) {
            window.clear(color);
            window.draw(backgroundSprite);
            // Draw title and buttons
            window.draw(title);            
            window.draw(illustrateButton.shape);
            window.draw(illustrateButton.text);
            window.draw(settingButton.shape);
            window.draw(settingButton.text);
            window.draw(startGameButton.shape);
            window.draw(startGameButton.text);
            window.draw(exitGameButton.shape);
            window.draw(exitGameButton.text);
            window.draw(developerButton.shape);
            window.draw(developerButton.text);
            
            switch(show){
                case Show::Picture:
                    window.draw(picture);
                    break;
                case Show::ILLUSTRATE:
                    window.draw(illustratepicture);
                    break;
                case Show::DEVELOPER:
                    window.draw(developerpicture);
                    break;
            }
            window.display();


            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                // Handle button clicks
                if (illustrateButton.isClicked(event)) {
                    if(show==Show::Picture||show==Show::DEVELOPER)
                        show = Show::ILLUSTRATE;
                    else
                        show = Show::Picture;
                }
                else if (settingButton.isClicked(event)) {
                    return Screen::SETTINGS_MENU;
                }
                else if (startGameButton.isClicked(event)) {
                    return Screen::GAME_SELECTION_MENU;
                }
                else if (exitGameButton.isClicked(event)) {
                    return Screen::EXIT;
                }
                else if (developerButton.isClicked(event)) {
                    if(show==Show::Picture||show==Show::ILLUSTRATE)
                        show = Show::DEVELOPER;
                    else
                        show = Show::Picture;
                }
            }
        }
        return Screen::EXIT;
    }
};

#endif