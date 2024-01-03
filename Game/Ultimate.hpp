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
        std::tuple<int, int> valid_Board;

        Ultimate(sf::RenderWindow &win, std::tuple<int, int, int, int> g_P) : Game(win, g_P)
        {
            valid_Board = {-1, -1};
            auto [x, y, w, h] = g_P;
            basics.resize(3);
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    basics[i].push_back(Basic(window, {x + j * (w / 3), y + i * (h / 3), w / 3, h / 3}));
                }
            }
            board = std::vector<std::vector<player>>(3, std::vector<player>(3, player::none));
            lines.resize(4);
            for (int i = 0; i < 4; i++)
            {
                lines[i].setSize(sf::Vector2f(10, h));
                lines[i].setFillColor(sf::Color::Black);
            }
            lines[0].setPosition(x + w / 3-2.5, y);
            lines[1].setPosition(x + w / 3 * 2-2.5, y);
            lines[2].setPosition(x + w, y + h / 3-2.5);
            lines[3].setPosition(x + w, y + h / 3 * 2-2.5);

            lines[2].rotate(90);
            lines[3].rotate(90);

                   
    }
    ~Ultimate() override{}
    void render() override{
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                basics[i][j].render();
            }
        }
        for(auto &line : lines){
            window.draw(line);
        }
        return;
    }
    void click_Event(sf::Event &event) override{
        if (event.type == sf::Event::Closed) {
            window.close();
        }


        auto [x,y] = valid_Board;
        if(valid_Board==std::make_tuple(-1,-1)){
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    if(basics[i][j].check_Win()!=player::none){
                        continue;
                    }
                    auto [r,c] = basics[i][j].click_Event(event,currentPlayer);
                    if(r!=-2&&c!=-2){
                        currentPlayer = currentPlayer == player::O ? player::X : player::O;
                        valid_Board = {r, c};
                        break;
                    }
                }
            }
        }
        else{
            auto [r,c] = basics[x][y].click_Event(event,currentPlayer);
            if(r!=-2&&c!=-2){
                currentPlayer = currentPlayer == player::O ? player::X : player::O;
                std::cout << "valid board <<"<<r<<" "<<c<<"\n";
                valid_Board = {r, c};
            }
        }
        check_Board();
        return;
    }
    player WhoseTurn() override{
        return currentPlayer;
    }
    void check_Board(){
        auto [x,y] = valid_Board;
        if(x==-1&&y==-1){
            return;
        }
        board[x][y] = basics[x][y].check_Win();
        if(board[x][y] != player::none){
            valid_Board = {-1, -1};
            std::cout << "valid board "<<x<<" "<<y<<"is full\n";
        }
        return;
    }
    player check_Win() override{
        int count_PlayerO = 0;
        int count_PlayerX = 0;
        for(auto &i : board){
            for(auto &j : i){
                if(j == player::O){
                    count_PlayerO++;
                }
                else if(j == player::X){
                    count_PlayerX++;
                }
            }
        }
        if(count_PlayerO+count_PlayerX == 9||abs(count_PlayerO-count_PlayerX)>=5){
            if(count_PlayerO > count_PlayerX){
                return player::O;
            }
            else if(count_PlayerO < count_PlayerX){
                return player::X;
            }
            else{
                return player::draw;
            }
        }
        else{
            return player::none;
        }
    }
    UIComponent::Screen getGameMode() override{
        return UIComponent::Screen::GAME_ULTIMATE_INTERFACE;
    }
    private:
    std::vector<std::vector<player>> board;
    std::vector<std::vector<Basic>> basics;
    std::vector<sf::RectangleShape> lines;
};

#endif
