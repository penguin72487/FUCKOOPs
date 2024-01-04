#ifndef RESULTSCREEN_HPP
#define RESULTSCREEN_HPP

#include "UIComponent.hpp"
#include "Button.hpp"

class ResultScreen : public UIComponent {
private:
    sf::Text playerCongratulationText;
    sf::Text gamePlayedText;
    sf::Text player1StatsText;
    sf::Text player2StatsText;
    Button BackButton;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
public:
    ResultScreen(sf::RenderWindow& window) : UIComponent(window),BackButton(490, 914, 420, 85, "menu", font){
        playerCongratulationText = sf::Text ("Congratulation Player__!!", font, 80);
        playerCongratulationText.setFillColor(sf::Color(255, 255, 255));
        playerCongratulationText.setPosition(234, 60); 

        gamePlayedText = sf::Text ("You have played __", font, 65);
        gamePlayedText.setFillColor(sf::Color(255, 255, 255));
        gamePlayedText.setPosition(110, 206);

        player1StatsText = sf::Text ("Player1\nwin:__(__)%\nlose:__(__)%", font, 65);
        player1StatsText.setFillColor(sf::Color(255, 255, 255));
        player1StatsText.setPosition(110, 359);

        player2StatsText = sf::Text ("Player1\nwin:__(__)%\nlose:__(__)%", font, 65);
        player2StatsText.setFillColor(sf::Color(255, 255, 255));
        player2StatsText.setPosition(110,650);
    }
    Screen render() override {
        std::cout << "Result Screen: [Results and Scores]" << std::endl;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                // check if buttons are clicked
                if (BackButton.isClicked(window,event)) {
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
            window.draw(playerCongratulationText);
            window.draw(gamePlayedText);
            window.draw(player1StatsText);
            window.draw(player2StatsText);
            window.draw(BackButton.shape);
            window.draw(BackButton.text);
            window.display();
        }
        return Screen::MAIN_MENU;
        }
    // 其他結果展示功能
};

#endif
