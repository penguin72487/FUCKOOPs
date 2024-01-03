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
    }
    ~Basic() override{}

    std::vector<std::vector<player>> board;
    std::vector<std::vector<Button>> buttons;
    std::vector<sf::RectangleShape> lines;

    UIComponent::Screen getGameMode() override{
        return UIComponent::Screen::GAME_BASIC_INTERFACE;
    }
    void render() override{
        // 繪製遊戲界面
        for (auto &button : buttons){
            for(auto &b : button){
                window.draw(b.shape);
                // window.draw(b.text);
            }
        }
        //載入格線圖片
        sf::Texture BasicUITexture;
        if(!BasicUITexture.loadFromFile("data/images/ui/basicOOXX-line.png")){
            std::cout << "BasicUITexture load failed\n";
        }
        sf::Sprite BasicUISprite;
        BasicUISprite.setTexture(BasicUITexture);
        BasicUISprite.setOrigin(BasicUISprite.getTextureRect().width / 2, BasicUISprite.getTextureRect().height / 2); //改變基準點
        auto [x,y,w,h] = GamePosition;
        BasicUISprite.setPosition(x + w/2, y + h/2); //設定位置
        BasicUISprite.setScale(static_cast<double>(w)/733,static_cast<double>(h)/733); // 放大
        window.draw(BasicUISprite);

        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j] == player::O){
                    // std::cout << "drawO\n";
                    drawO(window, i, j);
                }
                else if(board[i][j] == player::X){
                    drawX(window, i, j);
                }
            }
        }
        if(check_Win() != player::none){
            // 創建一個半透明的矩形
            sf::RectangleShape rectangle;
            rectangle.setPosition(x, y);
            rectangle.setSize(sf::Vector2f(w, h));
            rectangle.setFillColor(sf::Color(255, 255, 255, 128)); // RGBA，最後一個參數是透明度，範圍是0-255

            // // 繪製大圈圈或大叉叉
            // if (check_Win() == player::O) {
            //     // 繪製大圈圈
            //     drawO(window, 1, 1, 733, 733); // 你需要根據需要調整這些參數
            // } else if (check_Win() == player::X) {
            //     // 繪製大叉叉
            //     drawX(window, 1, 1, 733, 733); // 你需要根據需要調整這些參數
            // }

            // 在視窗上繪製半透明的矩形
            window.draw(rectangle);
        }
        return;
    }
    void setCurrentPlayer(player p){
        currentPlayer = p;
    }
    void click_Event(sf::Event &event) override{

            if (event.type == sf::Event::Closed)
                window.close();

            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    if (buttons[i][j].isClicked(window,event)) {
                        if (board[i][j] == player::none) {
                            board[i][j] = currentPlayer;
                            currentPlayer = currentPlayer == player::O ? player::X :player::O;
                        }
                    }
                }
            }
        return;
    }
    std::tuple<int,int> click_Event(sf::Event &event, player p) {

            if (event.type == sf::Event::Closed)
                window.close();
            setCurrentPlayer(p);
            // if(check_Win() != player::none){
            //     // std::cout << "also invalid board\n";
            //     return {-1,-1};
            // }
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    if (buttons[i][j].isClicked(window,event)) {
                        if (board[i][j] == player::none) {
                            board[i][j] = currentPlayer;
                            // std::cout << "board"<<i<<" "<<j<<"isClicked\n";
                            currentPlayer = currentPlayer == player::O ? player::X :player::O;
                            return {i,j};
                        }
                    }
                }
            }
        return {-2,-2};
    }
    player check_Win() override{
        // 檢查勝利狀況
        player winner = victory_Condition();
        if (winner != player::none) {
            std::string resultMessage = winner == player::O ? "O wins!\n" : (winner == player::X ? "X wins!\n" : "Draw!\n");
            // std::cout << resultMessage;
            // return winner;
            // resetGame();
        }
        return winner;
    }
    player WhoseTurn() override{
        return currentPlayer;
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

    void drawO(sf::RenderWindow &window, int row, int col , int color = 10) {
        if(color < 1 || color > 16) color = 8;
        auto [x,y,w,h] = GamePosition;
        double w_Scale = static_cast<double>(w)/330;
        double h_Scale = static_cast<double>(h)/330;

        sf::Texture OTexture;
        if(!OTexture.loadFromFile("data/images/O/O"+ std::to_string(color) +".png")){
            std::cout << "OTexture load failed\n";
        }
        sf::Sprite OSprite;
        OSprite.setTexture(OTexture);
        //根據W h 調整大小
        OSprite.setScale(w_Scale,h_Scale); // 放大
        // OSprite.setScale(1.8f, 1.8f); // 放大
        OSprite.setPosition(x + col * (w / 3) + (w / 3 - OSprite.getTextureRect().width * OSprite.getScale().x) / 2, y + row * (h / 3) + (h / 3 - OSprite.getTextureRect().height * OSprite.getScale().y) / 2);
        window.draw(OSprite);
        
        
    }
    void drawO(sf::RenderWindow &window, int row, int col ,int W,int H,int color = 10) {
        if(color < 1 || color > 16) color = 8;
        auto [x,y,w,h] = GamePosition;
        double w_Scale = static_cast<double>(W)/110;
        double h_Scale = static_cast<double>(H)/110;

        sf::Texture OTexture;
        if(!OTexture.loadFromFile("data/images/O/O"+ std::to_string(color) +".png")){
            std::cout << "OTexture load failed\n";
        }
        sf::Sprite OSprite;
        OSprite.setTexture(OTexture);
        //根據W h 調整大小
        OSprite.setScale(w_Scale,h_Scale); // 放大
        // OSprite.setScale(1.8f, 1.8f); // 放大
        OSprite.setPosition(x + col * (W) + (W - OSprite.getTextureRect().width * OSprite.getScale().x) / 2, y + row * (H) + (H - OSprite.getTextureRect().height * OSprite.getScale().y) / 2);
        window.draw(OSprite);
        
        
    }
    void drawX(sf::RenderWindow &window, int row, int col, int color = 9) {
        if(color < 1 || color > 16) color = 8;
        auto [x, y, w, h] = GamePosition;
        double w_Scale = static_cast<double>(w)/330;
        double h_Scale = static_cast<double>(h)/330;

        sf::Texture XTexture;
        if(!XTexture.loadFromFile("data/images/X/X" +  std::to_string(color) + ".png")){
            std::cout << "XTexture load failed\n";
        }
        sf::Sprite XSprite;
        XSprite.setTexture(XTexture);
        XSprite.setScale(w_Scale,h_Scale); // 放大
        XSprite.setPosition(x + col * (w / 3) + (w / 3 - XSprite.getTextureRect().width * XSprite.getScale().x) / 2, y + row * (h / 3) + (h / 3 - XSprite.getTextureRect().height * XSprite.getScale().y) / 2);
        window.draw(XSprite);
    }
    void drawX(sf::RenderWindow &window, int row, int col, int W, int H, int color = 9) {
        if(color < 1 || color > 16) color = 8;
        auto [x, y, w, h] = GamePosition;
        double w_Scale = static_cast<double>(W)/110;
        double h_Scale = static_cast<double>(H)/110;

        sf::Texture XTexture;
        if(!XTexture.loadFromFile("data/images/X/X" +  std::to_string(color) + ".png")){
            std::cout << "XTexture load failed\n";
        }
        sf::Sprite XSprite;
        XSprite.setTexture(XTexture);
        XSprite.setScale(w_Scale,h_Scale); // 放大
        XSprite.setPosition(x + col * (W) + (W - XSprite.getTextureRect().width * XSprite.getScale().x) / 2, y + row * (H) + (H - XSprite.getTextureRect().height * XSprite.getScale().y) / 2);
        window.draw(XSprite);
    }
};

#endif
