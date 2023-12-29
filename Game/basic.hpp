#include<bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "game.hpp"
#ifndef BASIC_HPP
#define BASIC_HPP

class Basic : public Game {
    public:
        Basic(){
            currentPlayer = 0;
            timeLimit = -1;
            interfaceColor = "white";
            board = std::vector<std::vector<int>>(3, std::vector<int>(3, 0));
            window.create(sf::VideoMode(1024, 1024), "Tic-Tac-Toe", sf::Style::Close | sf::Style::Titlebar);
            windowSize = window.getSize();
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
        int gameProcess() override// aka gameProcess
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
                            if (board[row][col] == 0) {
                                board[row][col] = currentPlayer;
                                currentPlayer = currentPlayer == 1 ? 2 : 1;
                            }
                        }
                    }

                    // 繪製遊戲界面
                    render();

                    // 檢查勝利狀況
                    int winner = victory_Condition();
                    if (winner != 0) {
                        std::string resultMessage = winner == 1 ? "O wins!\n" : (winner == 2 ? "X wins!\n" : "Draw!\n");
                        std::cout << resultMessage;
                        return winner;
                        // resetGame();
                    }
                }
            return 0;
        }
        int victory_Condition() override{
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
                        if (cell == 0) return 0;
                    }
                }

                return 3;
        };
        void render() override{
                window.clear(sf::Color::White);
                for (auto &line : lines) {
                    window.draw(line);
                }
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (board[i][j] == 1) {
                            drawO(window, i, j);
                        }
                        if (board[i][j] == 2) {
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
        std::vector<std::vector<int>> board;// 0:None 1:O 2:X
        bool isLineWin(int a, int b, int c) {
            return (a == b) && (b == c) && (a != 0);
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
            currentPlayer = 1;
            for (auto &row : board) {
                std::fill(row.begin(), row.end(), 0);
            }
        }

    private:
        sf::RenderWindow window;
        sf::Vector2u windowSize;
        sf::RectangleShape lines[4];
};

#endif