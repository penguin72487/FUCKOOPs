#include<bits/stdc++.h>
#include <SFML/Graphics.hpp>
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
        Game(sf::RenderWindow& win,std::tuple<int,int,int,int> g_P): window(win), game_Possition(g_P){
            currentPlayer = player::O;
            font.loadFromFile("../TaipeiSansTCBeta-Regular.ttf");
        };// constructor
        virtual ~Game(){} // destructor
        virtual void render() = 0;
        virtual void click_Event(sf::Event &ev) = 0;
        // virtual void WhooseTurn() = 0;
        virtual player check_Win() = 0;

    protected:
        sf::RenderWindow& window;
        std::tuple<int, int, int, int> game_Possition;
        player currentPlayer;// 0:O 1:X
        sf::Font font;
        time_t get_Timestamp(){
            return time(0);
        }
};


# endif