#ifndef GAMEENDSCREEN_HPP
#define GAMEENDSCREEN_HPP

#include "UIComponent.hpp"
#include "Button.hpp"
#include "../Game/Game.hpp"
class GameEndScreen : public UIComponent {
private:
    sf::Text WinMessage;
    // sf::RenderWindow window;
    Button AgainButton;
    Button ResultButton;
    Button BackButton;
public:
    GameEndScreen(sf::RenderWindow& window) : UIComponent(window),AgainButton(110,913, 280, 85, "Again", font)
    ,ResultButton(1010,913, 280, 85, "Result", font),BackButton(560,913, 280, 85, "Menu", font) {
        
        WinMessage = sf::Text("Player__ Win!!", font, 80);
        WinMessage.setFillColor(sf::Color(255, 255, 255));
        WinMessage.setPosition(700, 83); 
    }
    Screen render() override {
        // std::cout << "Game End: [Gameplay Elements]" << std::endl;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                // check if buttons are clicked
                if (AgainButton.isClicked(window,event)) {
                    return Screen::GAME_BASIC_INTERFACE;
                }
                if(ResultButton.isClicked(window,event)){
                    return Screen::RESULT_SCREEN;
                }
                if (BackButton.isClicked(window,event)) {
                    return Screen::MAIN_MENU;
                }
            }

            window.clear(color);
            // draw title and buttons
            window.draw(WinMessage);
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
    Screen render(std::shared_ptr<Game> game) {
        // std::cout << "Game End: [Gameplay Elements]" << std::endl;
        std::string player;
        if(game->check_Win() == Game::player::O){
            player = "O";
        }
        else if(game->check_Win() == Game::player::X){
            player = "X";
        }
        else{
            player = "Draw";
        }

        if(player == "Draw"){
            
            WinMessage.setString("Draw!!");
        }
        else{
            WinMessage.setString("Player " + player + " Win!!");
        }
        sf::FloatRect WinMessageRect = WinMessage.getLocalBounds();//獲取文字的長寬
        WinMessage.setOrigin(WinMessageRect.left + WinMessageRect.width/2.0f, WinMessageRect.top  + WinMessageRect.height/2.0f);//設置中心點
        WinMessage.setPosition(sf::Vector2f(window.getSize().x/2.0f, 82.0f));

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                // check if buttons are clicked
                if (AgainButton.isClicked(window,event)) {

                    if(game->getGameMode() == Screen::GAME_BASIC_INTERFACE){
                        return Screen::GAME_BASIC_INTERFACE;
                    }
                    else if(game->getGameMode() == Screen::GAME_ULTIMATE_INTERFACE){
                        return Screen::GAME_ULTIMATE_INTERFACE;
                    }
                    else{
                        return Screen::EXIT;
                    }

                }
                if(ResultButton.isClicked(window,event)){
                    return Screen::RESULT_SCREEN;
                }
                if (BackButton.isClicked(window,event)) {
                    return Screen::MAIN_MENU;
                }
            }

            window.clear(color);
            // draw title and buttons
            window.draw(WinMessage);
            window.draw(AgainButton.shape);
            window.draw(AgainButton.text);
            window.draw(ResultButton.shape);
            window.draw(ResultButton.text);
            window.draw(BackButton.shape);
            window.draw(BackButton.text);
            game->render();
            window.display();
        }
        return Screen::MAIN_MENU;
    }
    // 其他遊戲功能
};

#endif