#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "basicOOXX.cpp"
int main() {
    // 視窗設定
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "Tic-Tac-Toe", sf::Style::Close | sf::Style::Titlebar);
    sf::Vector2u windowSize = window.getSize();

    // 繪製格線
    float lineLength = windowSize.x * 0.9;
    float lineWidth = windowSize.y * 0.01;
    sf::RectangleShape lines[4] = {
        sf::RectangleShape(sf::Vector2f(lineLength, lineWidth)),
        sf::RectangleShape(sf::Vector2f(lineLength, lineWidth)),
        sf::RectangleShape(sf::Vector2f(lineWidth, lineLength)),
        sf::RectangleShape(sf::Vector2f(lineWidth, lineLength))
    };

    // 設定格線位置
    lines[0].setPosition(windowSize.x / 2 - lineLength / 2, windowSize.y / 3 - lineWidth / 2);
    lines[1].setPosition(windowSize.x / 2 - lineLength / 2, 2 * windowSize.y / 3 - lineWidth / 2);
    lines[2].setPosition(windowSize.x / 3 - lineWidth / 2, windowSize.y / 2 - lineLength / 2);
    lines[3].setPosition(2 * windowSize.x / 3 - lineWidth / 2, windowSize.y / 2 - lineLength / 2);

    // 設定格線顏色
    for (auto &line : lines) {
        line.setFillColor(sf::Color(128, 128, 128));
    }

    // 遊戲主循環
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // 事件處理
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                int row = event.mouseButton.y / 341;
                int col = event.mouseButton.x / 341;
                if (board[row][col] == Player::None) {
                    board[row][col] = currentPlayer;
                    currentPlayer = currentPlayer == Player::O ? Player::X : Player::O;
                }
            }
        }

        // 繪製遊戲界面
        window.clear(sf::Color::White);
        for (auto &line : lines) {
            window.draw(line);
        }
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

        // 檢查勝利狀況
        Player winner = checkWin();
        if (winner != Player::None) {
            std::string resultMessage = winner == Player::O ? "O wins!\n" : (winner == Player::X ? "X wins!\n" : "Draw!\n");
            std::cout << resultMessage;
            resetGame();
        }
    }

    return 0;
}

