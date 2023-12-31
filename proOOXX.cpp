#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Game/basicOOXX.hpp"
int main() {
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "Tic-Tac-Toe",sf::Style::Close | sf::Style::Titlebar); //設定視窗大小 1024*1024 並固定

    // 獲取視窗的大小
    // sf::Vector2u windowSize = window.getSize();
    
    sf::Texture bg;
    sf::Texture o;
    sf::Texture x;
    // 載入圖片
    if (!bg.loadFromFile("png/game/ui/ProOOXX-line.png")){
        std::cout << "Failed to load background image" << std::endl;
        return -1;
    }
    if(!o.loadFromFile("png/game/O/o1.png")){
        std::cout << "Failed to load O image" << std::endl;
        return -1;
    }
    if(!x.loadFromFile("png/game/X/x1.png")){
        std::cout << "Failed to load X image" << std::endl;
        return -1;
    }
    // 創建一個 sf::Sprite 物件，並將 texture 設定為其紋理
    sf::Sprite background(bg);
    sf::Sprite oSprite(o);
    sf::Sprite xSprite(x);

    // 在視窗中繪製背景
    


    // // 計算線條的長度和寬度
    // float lineLength = col ; 
    // float lineWidth = row * 0.01; // 1% 的視窗高度
    // sf::RectangleShape line1(sf::Vector2f(lineLength, lineWidth)), line2(sf::Vector2f(lineLength, lineWidth)),
    //                 line3(sf::Vector2f(lineWidth, lineLength)), line4(sf::Vector2f(lineWidth, lineLength));

    // // 計算線條的位置
    // float line1PositionX = col / 2 - lineLength / 2;
    // float line1PositionY = row / 3 - lineWidth / 2;
    // float line2PositionX = col / 2 - lineLength / 2;
    // float line2PositionY = 2 * row / 3 - lineWidth / 2;
    // float line3PositionX = col / 3 - lineWidth / 2;
    // float line3PositionY = row / 2 - lineLength / 2;
    // float line4PositionX = 2 * col / 3 - lineWidth / 2;
    // float line4PositionY = row / 2 - lineLength / 2;

    // // 設置線條的位置
    // line1.setPosition(line1PositionX, line1PositionY);
    // line2.setPosition(line2PositionX, line2PositionY);
    // line3.setPosition(line3PositionX, line3PositionY);
    // line4.setPosition(line4PositionX, line4PositionY);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                int row = event.mouseButton.y / 100;
                int col = event.mouseButton.x / 100;
                if (board[row][col] == Player::None) {
                    board[row][col] = currentPlayer;
                    currentPlayer = currentPlayer == Player::O ? Player::X : Player::O;
                }
            }
        }

        window.clear();
        window.draw(background);
        // window.draw(line1);
        // window.draw(line2);
        // window.draw(line3);
        // window.draw(line4);

        // 繪製 O 和 X
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == Player::O) {
                    oSprite.setPosition(j * 113, i * 113);
                    window.draw(oSprite);
                    // drawO(window, i, j);
                }
                if (board[i][j] == Player::X) {
                    xSprite.setPosition(j * 113, i * 113);
                    window.draw(xSprite);
                    // drawX(window, i, j);
                }
            }
        }

        window.display();

        // 檢查勝利
        Player winner = checkWin();
        if (winner != Player::None) {
            switch(winner) {
                case Player::O:
                    std::cout << "O wins!" << std::endl;
                    break;
                case Player::X:
                    std::cout << "X wins!" << std::endl;
                    break;
                default:
                    std::cout << "Draw!" << std::endl;
                    break;

            }
            // break;
        }
        if (checkWin() != Player::None) {
            resetGame();
        }

    }

    return 0;
}
