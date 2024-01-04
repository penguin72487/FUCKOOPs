#include<bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "../UI/UIComponent.hpp"
# ifndef GAME_HPP
# define GAME_HPP


class Game{
    public:
        enum class player {
            none,
            O,
            X,
            draw
        };
        Game(sf::RenderWindow& win,std::tuple<int,int,int,int> gamePositionParams): window(win),GamePosition(gamePositionParams){
            currentPlayer = player::O;
            font.loadFromFile("data/ttf/TaipeiSansTCBeta-Regular.ttf");
        };// constructor
        virtual ~Game(){} // destructor
        virtual void render() = 0;
        virtual void click_Event(sf::Event &ev) = 0;
        virtual player WhoseTurn() = 0;
        virtual player check_Win() = 0;
        virtual UIComponent::Screen getGameMode() = 0;


    protected:
        sf::RenderWindow& window;
        std::tuple<int, int, int, int> GamePosition;
        player currentPlayer;// 0:O 1:X
        sf::Font font;
};


# endif