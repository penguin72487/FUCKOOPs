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
        board = std::vector<std::vector<player>>(3, std::vector<player>(3, player::none));
        
    }
    ~Ultimate() override{}

    std::vector<std::vector<player>> board;
    std::vector<std::vector<Basic>> basics;
    std::vector<sf::RectangleShape> lines;
};

#endif
