#ifndef ULTIMATE_H
#define ULTIMATE_H
#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include "../UI/Button.hpp"
#include "Basic4U.hpp"
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
                    basics[i].push_back(Basic4U(window, {x + j * (w / 3), y + i * (h / 3), w / 3, h / 3}));
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
    // player check_Win() override{
    //     int count_PlayerO = 0;
    //     int count_PlayerX = 0;
    //     int count_Draw = 0;
    //     for(auto &i : board){
    //         for(auto &j : i){
    //             if(j == player::O){
    //                 count_PlayerO++;
    //             }
    //             else if(j == player::X){
    //                 count_PlayerX++;
    //             }
    //             else{
    //                 count_Draw++;
    //             }
    //         }
    //     }
    //     if(count_PlayerO + count_PlayerX + count_Draw != 9){
    //         return player::none;
    //     }
    //     if(count_PlayerO > count_PlayerX){
    //         return player::O;
    //     }
    //     else if(count_PlayerO < count_PlayerX){
    //         return player::X;
    //     }
    //     else{
    //         return player::draw;
    //     }
    // }
    player check_Win() override {
        // 檢查每一行
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] != player::none && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
                return board[i][0];
            }
        }

        // 檢查每一列
        for (int i = 0; i < 3; ++i) {
            if (board[0][i] != player::none && board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
                return board[0][i];
            }
        }

        // 檢查對角線
        if (board[0][0] != player::none && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
            return board[0][0];
        }
        if (board[0][2] != player::none && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
            return board[0][2];
        }

        // 檢查是否還有空格，如果有，則遊戲還未結束
        for (auto &i : board) {
            for (auto &j : i) {
                if (j == player::none) {
                    return player::none;
                }
            }
        }

        // 如果棋盤已滿且沒有玩家獲勝，則為平局
        return player::draw;
    }
    UIComponent::Screen getGameMode() override{
        return UIComponent::Screen::GAME_ULTIMATE_INTERFACE;
    }
    private:
    std::vector<std::vector<player>> board;
    std::vector<std::vector<Basic4U>> basics;
    std::vector<sf::RectangleShape> lines;
};

#endif
