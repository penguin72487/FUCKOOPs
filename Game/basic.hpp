#include<bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "../UI/Button.hpp"
#ifndef BASIC_HPP
#define BASIC_HPP

class Basic : public Game {
    using player = Game::player;
    public:
    // Button button;
    Basic(sf::RenderWindow& win,std::tuple<int,int,int,int> g_P ): Game(win, g_P){
        auto [x,y,w,h] = g_P;
        board = std::vector<std::vector<player>>(3, std::vector<player>(3, player::none));
        buttons.resize(3);
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                buttons[i].push_back(Button(x + j * (w / 3), y + i * (h / 3), w / 3, h / 3, " ", font));
            }
        }
        lines = std::vector<sf::RectangleShape>(4, sf::RectangleShape());
        // 繪製格線
        float lineLength = w * 0.9;
        float lineWidth = h * 0.01;
        lines[0] = sf::RectangleShape(sf::Vector2f(lineLength, lineWidth));
        lines[1] = sf::RectangleShape(sf::Vector2f(lineLength, lineWidth));
        lines[2] = sf::RectangleShape(sf::Vector2f(lineWidth, lineLength));
        lines[3] = sf::RectangleShape(sf::Vector2f(lineWidth, lineLength));
        for(auto &line : lines){
            line.setFillColor(sf::Color(128, 128, 128));
        }
        // 設定格線位置
        lines[0].setPosition(x + w / 2 - lineLength / 2, y + h / 3 - lineWidth / 2);
        lines[1].setPosition(x + w / 2 - lineLength / 2, y + 2 * h / 3 - lineWidth / 2);
        lines[2].setPosition(x + w / 3 - lineWidth / 2, y + h / 2 - lineLength / 2);
        lines[3].setPosition(x + 2 * w / 3 - lineWidth / 2, y + h / 2 - lineLength / 2);
    }
    ~Basic() override{}

    std::vector<std::vector<player>> board;
    std::vector<std::vector<Button>> buttons;
    std::vector<sf::RectangleShape> lines;

    void render() override{
        // 繪製遊戲界面
        
        //window.clear(sf::Color::White);

        for (auto &button : buttons){
            for(auto &b : button){
                window.draw(b.shape);
                window.draw(b.text);
            }
        }
        for (auto &line : lines) {
            window.draw(line);
        }
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j] == player::O){
                    drawO(window, i, j);
                }
                else if(board[i][j] == player::X){
                    drawX(window, i, j);
                }
            }
        }

        // window.display();
        return;
    }
    void click_Event(sf::Event &event) override{

            if (event.type == sf::Event::Closed)
                window.close();

            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    if (buttons[i][j].isClicked(event)) {
                        if (board[i][j] == player::none) {
                            board[i][j] = currentPlayer;
                            currentPlayer = currentPlayer == player::O ? player::X :player::O;
                        }
                    }
                }
            }
        return;
    }
    player check_Win() override{
        // 檢查勝利狀況
        player winner = victory_Condition();
        if (winner != player::none) {
            std::string resultMessage = winner == player::O ? "O wins!\n" : (winner == player::X ? "X wins!\n" : "Draw!\n");
            std::cout << resultMessage;
            // return winner;
            // resetGame();
        }
        return winner;
    }
    player victory_Condition() {
        // 檢查所有行和列
        for (int i = 0; i < 3; i++) {
            if (isLineWin(board[i][0], board[i][1], board[i][2])) return board[i][0];
            if (isLineWin(board[0][i], board[1][i], board[2][i])) return board[0][i];
        }

        // 檢查對角線
        if (isLineWin(board[0][0], board[1][1], board[2][2])) return board[0][0];
        if (isLineWin(board[0][2], board[1][1], board[2][0])) return board[0][2];

        // 檢查平手
        for (auto &row : board) {
            for (auto cell : row) {
                if (cell == player::none) return player::none;
            }
        }

        return player::draw;
    }
    bool isLineWin(player c1, player c2, player c3) {
        return c1 != player::none && c1 == c2 && c2 == c3;
    }


    void drawO(sf::RenderWindow &window, int row, int col) {
        auto [x,y,w,h] = game_Possition;
        sf::CircleShape circle(75);  // 放大圓圈的大小
        circle.setPosition(x + col * (w / 3) + (w / 3 - circle.getRadius() * 2) / 2, y + row * (h / 3) + (h / 3 - circle.getRadius() * 2) / 2);
        circle.setFillColor(sf::Color::Red);
        circle.setOutlineColor(sf::Color::White);
        circle.setOutlineThickness(5);
        window.draw(circle);
        
        
    }
    void drawX(sf::RenderWindow &window, int row, int col) {
        auto [x, y, w, h] = game_Possition;
        sf::RectangleShape line1(sf::Vector2f(150, 10)), line2(sf::Vector2f(150, 10));

        // 计算X的中心位置
        float centerX = x + col * (w / 3) + (w / 3) / 2;
        float centerY = y + row * (h / 3) + (h / 3) / 2;

        // 设置第一条线的位置和旋转
        line1.setPosition(centerX, centerY);
        line1.setOrigin(150 / 2, 10 / 2);
        line1.setRotation(45);

        // 设置第二条线的位置和旋转
        line2.setPosition(centerX, centerY);
        line2.setOrigin(150 / 2, 10 / 2);
        line2.setRotation(-45);

        // 设置线的颜色
        line1.setFillColor(sf::Color::Blue);
        line2.setFillColor(sf::Color::Blue);

        // 绘制两条线
        window.draw(line1);
        window.draw(line2);
    }

        

    

};

#endif