#ifndef GAMEINTERFACE_HPP
#define GAMEINTERFACE_HPP

#include "UIComponent.hpp"
#include "Button.hpp"
#include "../Game/Game.hpp"
#include "../Game/Basic.hpp"
// #include "../Game/Ultimate.hpp"

class GameInterface : public UIComponent {
private:
    Button MenuButton;
    Button RestartButton;
    // Button board;//棋盤
    Screen gameMode;
    std::tuple<int,int,int,int> using player = Game::player; = {333, 164, 734, 734};


public:
    GameInterface(sf::RenderWindow& window) : UIComponent(window),MenuButton(57, 36, 160, 70, "MENU", font),
    RestartButton(57, 900, 160, 70, "RESTART", font)
    {

    }
    Screen render() override {
        std::cout << "Game Individual Interface: [GamePlay Elements]" << std::endl;
        return Screen::EXIT;
    }
    Screen render(Screen &GameMod) {
        gameMode = GameMod;
        std::unique_ptr<Game> game;
        if(gameMode == Screen::GAME_BASIC_INTERFACE){
            std::cout << "Game Basic new [GamePlay Elements]" << std::endl;
            game = std::make_unique<Basic>(window, using player = Game::player;);
        }
        else if(gameMode == Screen::GAME_ULTIMATE_INTERFACE){
            std::cout << "Game Ultimate new [GamePlay Elements]" << std::endl;
                // game = std::make_unique<Ultimate>(window, using player = Game::player;);
                return Screen::GAME_SELECTION_MENU;
            }
        else{
            std::cout << "Game Ultimate Interface: [GamePlay Elements]" << std::endl;
        }


        while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        return Screen::EXIT;
                    }
                    if (MenuButton.isClicked(event)) {
                        return Screen::MAIN_MENU;
                    }
                    if (RestartButton.isClicked(event)) {
                        return gameMode; // 你可能需要重置游戏状态
                    }
                    game->click_Event(event); // 处理游戏内的点击事件
                }

                // 更新游戏状态
                // game->update(); // 假设你有一个负责更新游戏逻辑的方法

                // 渲染游戏和界面
                window.clear(color);
                game->render(); // 渲染游戏
                window.draw(MenuButton.shape);
                window.draw(MenuButton.text);
                window.draw(RestartButton.shape);
                window.draw(RestartButton.text); // 渲染界面元素，例如菜单和重新开始按钮
                window.display(); // 更新窗口显示

                // 检查游戏是否结束
                if(game->check_Win() != Game::player::none){
                    return Screen::GAME_END_SCREEN;
                }
            }

        return Screen::EXIT;
    }
    // 其他遊戲功能
};

#endif