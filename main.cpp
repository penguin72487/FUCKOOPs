#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "basicOOXX.cpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "Tic-Tac-Toe",sf::Style::Close | sf::Style::Titlebar); //設定視窗大小 1024*1024 並固定

    // 獲取視窗的大小
    sf::Vector2u windowSize = window.getSize();

    // 計算格線的長度和寬度
    float lineLength = windowSize.x*0.9;/*11111111111*/ 
    float lineWidth = windowSize.y * 0.01; // 1% 的視窗高度
    sf::RectangleShape line1(sf::Vector2f(lineLength, lineWidth)), line2(sf::Vector2f(lineLength, lineWidth)),
                    line3(sf::Vector2f(lineWidth, lineLength)), line4(sf::Vector2f(lineWidth, lineLength));

    // 計算線條的位置
    float line1PositionX = windowSize.x / 2 - lineLength / 2;
    float line1PositionY = windowSize.y / 3 - lineWidth / 2;
    float line2PositionX = windowSize.x / 2 - lineLength / 2;
    float line2PositionY = 2 * windowSize.y / 3 - lineWidth / 2;
    float line3PositionX = windowSize.x / 3 - lineWidth / 2;
    float line3PositionY = windowSize.y / 2 - lineLength / 2;
    float line4PositionX = 2 * windowSize.x / 3 - lineWidth / 2;
    float line4PositionY = windowSize.y / 2 - lineLength / 2;

    // 設置線條的位置
    line1.setPosition(line1PositionX, line1PositionY);
    line2.setPosition(line2PositionX, line2PositionY);
    line3.setPosition(line3PositionX, line3PositionY);
    line4.setPosition(line4PositionX, line4PositionY);

    line1.setFillColor(sf::Color(128,128,128));
    line2.setFillColor(sf::Color(128,128,128));
    line3.setFillColor(sf::Color(128,128,128));
    line4.setFillColor(sf::Color(128,128,128));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                int row = event.mouseButton.y / 341;  // 調整滑鼠點擊的位置計算
                int col = event.mouseButton.x / 341;  // 調整滑鼠點擊的位置計算
                if (board[row][col] == Player::None) {
                    board[row][col] = currentPlayer;
                    currentPlayer = currentPlayer == Player::O ? Player::X : Player::O;
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(line1);
        window.draw(line2);
        window.draw(line3);
        window.draw(line4);

        // 繪製 O 和 X
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == Player::O) {
                    drawO(window, i, j);
                }
                if (board[i][j] == Player::X) {
                    drawX(window, i, j);
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
