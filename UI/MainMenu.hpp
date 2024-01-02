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
    sf::Texture PictureTexture;
    sf::Sprite PictureSprite;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    Show show = Show::Picture;
    sf::Texture IllustratePictureTexture;
    sf::Sprite IllustratePictureSprite;
    sf::Texture DeveloperPictureTexture;
    sf::Sprite DeveloperPictureSprite;

public:
    MainMenu(sf::RenderWindow& window) : UIComponent(window), 
        illustrateButton(57, 650, 200, 70, "ILLUSTRATE", font),
        settingButton(57, 500, 200, 70, "SETTING", font),
        startGameButton(57, 350, 200, 70, "START GAME", font),
        exitGameButton(57, 800, 200, 70, "EXIT", font),
        developerButton(1150, 900, 200, 70, "DEVELOPER", font) {

        title = sf::Text("TIC-TAC-TOC", font, 170);
        title.setFillColor(sf::Color::Black);
        title.setPosition(57, 57);

        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        if (!PictureTexture.loadFromFile("data/images/ui/OOXX.png")) {
            std::cout << "Texture load failed\n";
        }
        PictureSprite.setTexture(PictureTexture);
        PictureSprite.setScale(1.2, 1.2);
        PictureSprite.setPosition(540, 314);
        
        if (!backgroundTexture.loadFromFile("data/images/bg/LobbyBG.png")) {
            std::cout << "Texture load failed\n";
        }
        backgroundSprite.setTexture(backgroundTexture);


        //load illustrate
        if (!IllustratePictureTexture.loadFromFile("data/images/ui/illustrate.png")) {
            std::cout << "Texture load failed\n";
        }
        IllustratePictureSprite.setTexture(IllustratePictureTexture);
        IllustratePictureSprite.setScale(0.27, 0.27);
        IllustratePictureSprite.setPosition(325, 300);

        //load developer
        if (!DeveloperPictureTexture.loadFromFile("data/images/ui/developer.png")) {
            std::cout << "Texture load failed\n";
        }
        DeveloperPictureSprite.setTexture(DeveloperPictureTexture);
        DeveloperPictureSprite.setScale(0.4, 0.4);
        DeveloperPictureSprite.setPosition(400, 500);
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
                    window.draw(PictureSprite);
                    break;
                case Show::ILLUSTRATE:
                    window.draw(IllustratePictureSprite);
                    break;
                case Show::DEVELOPER:
                    window.draw(DeveloperPictureSprite);
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