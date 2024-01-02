#ifndef ULTIMATE_H
#define ULTIMATE_H
#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include "../UI/Button.hpp"
#include "Basic.hpp"
#include <vector>

class Ultimate : public Game{

    using player = Game::player;
    public:
    Ultimate(sf::RenderWindow& win,std::tuple<int,int,int,int> g_P ): Game(win, g_P){
        auto [x,y,w,h] = g_P;
        basics.resize(3);
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                basics[i].push_back(Basic(window, {x + j * (w / 3), y + i * (h / 3), w / 3, h / 3}));
            }
        }
        board = std::vector<std::vector<player>>(3, std::vector<player>(3, player::none));
       
    }
    ~Ultimate() override{}
    void render() override{
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                basics[i][j].render();
            }
        }
        return;
    }
    void click_Event(sf::Event &event) override{
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                // auto [x,y] = sf::Mouse::getPosition(window);
                for(int i = 0; i < 3; i++){
                    for(int j = 0; j < 3; j++){
                            basics[i][j].click_Event(event);
                    }
                }
            }
        }
    }
    player WhoseTurn() override{
        return player::none;
    }
    player check_Win() override{
        return player::O;
    }
    UIComponent::Screen getGameMode() override{
        return UIComponent::Screen::GAME_ULTIMATE_INTERFACE;
    }
    private:
    std::vector<std::vector<player>> board;
    std::vector<std::vector<Basic>> basics;
};

#endif
