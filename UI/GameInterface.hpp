#ifndef GAMEINTERFACE_HPP
#define GAMEINTERFACE_HPP

#include "UIComponent.hpp"
#include "Button.hpp"
#include "../Game/Game.hpp"
#include "../Game/Basic.hpp"
#include "../Game/Ultimate.hpp"

class GameInterface : public UIComponent {
private:
    Button MenuButton;
    Button RestartButton;
    // Button board;//棋盤
    Screen gameMode;
    std::shared_ptr<Game> game;
    std::tuple<int,int,int,int> GamePosition = {333, 164, 734, 734};
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;


public:
    GameInterface(sf::RenderWindow& window) : UIComponent(window),MenuButton(57, 36, 160, 70, "MENU", font),
    RestartButton(57, 900, 160, 70, "RESTART", font)
    {

    }
    Screen render() override {
        // Render the game interface including buttons and game elements
        std::cout << "Game Invidual Interface: [Gameplay Elements]" << std::endl;
        return Screen::EXIT;
    }
    std::tuple<Screen,std::shared_ptr<Game>> render(Screen &GameMod) {
        gameMode = GameMod;

        if(gameMode == Screen::GAME_BASIC_INTERFACE){
            std::cout << "Game Basic new [Gameplay Elements]" << std::endl;
            game = std::make_shared<Basic>(window, GamePosition);
        }
        else if(gameMode == Screen::GAME_ULTIMATE_INTERFACE){
            //std::cout << "Game Ultimate new [Gameplay Elements]" << std::endl;
                game = std::make_shared<Ultimate>(window, GamePosition);
                // return {Screen::GAME_SELECTION_MENU,nullptr};
            }
        else{
            std::cout << "Game Ultimate Interface: [Gameplay Elements]" << std::endl;
        }


        while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        return {Screen::EXIT,nullptr};
                    }
                    if (MenuButton.isClicked(window,event)) {
                        return {Screen::GAME_SELECTION_MENU,nullptr};
                    }
                    if (RestartButton.isClicked(window,event)) {
                        return {gameMode,nullptr};
                    }
                    game->click_Event(event); // 处理游戏内的点击事件
                }
        
        if (!backgroundTexture.loadFromFile("data/images/bg/Bg1.png")) {
            std::cerr << "Error: Texture load failed\n";
            //return {Screen::ERROR_SCREEN, nullptr}; // Assuming there's an error screen or similar handling
        }
        backgroundSprite.setTexture(backgroundTexture);
                // 更新游戏状态
                // game->update(); // 假设你有一个负责更新游戏逻辑的方法

                // 渲染游戏和界面
                window.clear(color);
                window.draw(backgroundSprite);
                game->render(); // 渲染游戏
                window.draw(MenuButton.shape);
                window.draw(MenuButton.text);
                window.draw(RestartButton.shape);
                window.draw(RestartButton.text); // 渲染界面元素，例如菜单和重新开始按钮
                window.display(); // 更新窗口显示

                // 检查游戏是否结束
                Game::player win_Player=game->check_Win();
                if(win_Player != Game::player::none){
                    return {Screen::GAME_END_SCREEN,game};
                }
            }

        return {Screen::EXIT,nullptr};
    }
    // 其他遊戲功能
};

#endif