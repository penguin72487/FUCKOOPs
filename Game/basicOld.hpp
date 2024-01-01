#include<bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "../UI/Button.hpp"
#ifndef BASIC_HPP
#define BASIC_HPP

class Basic : public Game {
    using player = Game::player;
    public:
        Basic(sf::RenderWindow& win): window(win), windowSize(win.getSize()){
            currentPlayer = player::O;
            timeLimit = -1;
            interfaceColor = "white";
            board = std::vector<std::vector<player>>(3, std::vector<player>(3, player::none));
            init();
        }
        ~Basic(){}
        void init() override{


                // 繪製格線
                float lineLength = windowSize.x * 0.9;
                float lineWidth = windowSize.y * 0.01;
                this->lines[0] = sf::RectangleShape(sf::Vector2f(lineLength, lineWidth));
                this->lines[1] = sf::RectangleShape(sf::Vector2f(lineLength, lineWidth));
                this->lines[2] = sf::RectangleShape(sf::Vector2f(lineWidth, lineLength));
                this->lines[3] = sf::RectangleShape(sf::Vector2f(lineWidth, lineLength));

                // 設定格線位置
                this->lines[0].setPosition(this->windowSize.x / 2 - lineLength / 2, this->windowSize.y / 3 - lineWidth / 2);
                this->lines[1].setPosition(this->windowSize.x / 2 - lineLength / 2, 2 * this->windowSize.y / 3 - lineWidth / 2);
                this->lines[2].setPosition(this->windowSize.x / 3 - lineWidth / 2, this->windowSize.y / 2 - lineLength / 2);
                this->lines[3].setPosition(2 * this->windowSize.x / 3 - lineWidth / 2, this->windowSize.y / 2 - lineLength / 2);

                // 設定格線顏色
                for (auto &line : lines) {
                    line.setFillColor(sf::Color(128, 128, 128));
                }
        }
        player gameProcess() override// aka gameProcess
        {
            while (window.isOpen()) {
                    sf::Event event;
                    while (window.pollEvent(event)) {
                        // 事件處理
                        if (event.type == sf::Event::Closed)
                            window.close();

                        if (event.type == sf::Event::MouseButtonPressed) {
                            int row = event.mouseButton.y / 341;
                            int col = event.mouseButton.x / 341;
                            if (board[row][col] == player::none) {
                                board[row][col] = currentPlayer;
                                currentPlayer = currentPlayer == player::O ? player::draw : player::O;
                            }
                        }
                    }

                    // 繪製遊戲界面
                    render();

                    // 檢查勝利狀況
                    player winner = victory_Condition();
                    if (winner != player::none) {
                        std::string resultMessage = winner == player::O ? "O wins!\n" : (winner == player::X ? "X wins!\n" : "Draw!\n");
                        std::cout << resultMessage;
                        return winner;
                        // resetGame();
                    }
                }
            return player::none;
        }
        player victory_Condition() override{
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
        };

        void render() override{
                // window.clear(sf::Color::White);
                for (auto &line : lines) {
                    window.draw(line);
                }
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (board[i][j] == player::O) {
                            drawO(window, i, j);
                        }
                        if (board[i][j] == player::X) {
                            drawX(window, i, j);
                        }
                    }
                }
                window.display();
        };
        void update() override{};
        void click_Event() override{};
        void restart() override{};
        void settimeLimit(int) override{};
        void setinterfaceColor(std::string) override{};
            void whooseTurn() override{};

            // polymorphism for different game mode
        protected:
        std::vector<std::vector<player>> board;// 0:None 1:O 2:X
        bool isLineWin(player a, player b, player c) {
            return a == b && b == c && a != player::none;
        }

        void drawO(sf::RenderWindow &window, int row, int col) {
            sf::CircleShape circle(150);  // 放大圈圈的大小
            circle.setPosition(col * 341+25, row * 341+25);  // 調整圈圈的位置
            circle.setFillColor(sf::Color::Red);
            circle.setOutlineColor(sf::Color::White);
            circle.setOutlineThickness(5);
            window.draw(circle);
        }

        void drawX(sf::RenderWindow &window, int row, int col) {
            sf::RectangleShape line1(sf::Vector2f(300, 15)), line2(sf::Vector2f(300, 15));  // 放大叉叉的大小
            line1.setOrigin(150, 7.5);
            line2.setOrigin(150, 7.5);
            line1.setPosition(col * 341 + 170, row * 341 + 170);  // 調整叉叉的位置
            line2.setPosition(col * 341 + 170, row * 341 + 170);  // 調整叉叉的位置
            line1.rotate(45);
            line2.rotate(-45);
            line1.setFillColor(sf::Color::Blue);
            line2.setFillColor(sf::Color::Blue);
            window.draw(line1);
            window.draw(line2);
        }
        void resetGame() {
            currentPlayer = player::O;
            for (auto &row : board) {
                std::fill(row.begin(), row.end(), player::none);
            }
        }

    private:
        sf::RenderWindow& window;
        sf::Vector2u windowSize;
        sf::RectangleShape lines[4];
};

#endif