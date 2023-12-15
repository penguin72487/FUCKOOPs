#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

// 定義遊戲狀態
enum class Player { None, O, X, Draw };
Player currentPlayer = Player::O;
Player board[3][3] = {{Player::None, Player::None, Player::None}, 
                    {Player::None, Player::None, Player::None}, 
                    {Player::None, Player::None, Player::None}};

Player checkWin() {
    // 檢查橫排
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != Player::None)
            return board[i][0];
    }

    // 檢查豎排
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != Player::None)
            return board[0][i];
    }

    // 檢查對角線
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != Player::None)
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != Player::None)
        return board[0][2];

    // 檢查平手
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == Player::None)
                return Player::None;  // 還有空格，遊戲還未結束
        }
    }

    return Player::Draw;  // 沒有空格，且沒有玩家勝利，遊戲平手
}
void drawO(sf::RenderWindow &window, int row, int col) {
    sf::CircleShape circle(40);
    circle.setPosition(col * 100+12, row * 100+12);
    circle.setFillColor(sf::Color::Red);
    circle.setOutlineColor(sf::Color::White);
    circle.setOutlineThickness(5);
    window.draw(circle);
}

void drawX(sf::RenderWindow &window, int row, int col) {
    sf::RectangleShape line1(sf::Vector2f(100, 5)), line2(sf::Vector2f(100, 5));
    line1.setOrigin(50, 2.5);
    line2.setOrigin(50, 2.5);
    line1.setPosition(col * 100 + 50, row * 100 + 50);
    line2.setPosition(col * 100 + 50, row * 100 + 50);
    line1.rotate(45);
    line2.rotate(-45);
    line1.setFillColor(sf::Color::Blue);
    line2.setFillColor(sf::Color::Blue);
    window.draw(line1);
    window.draw(line2);
}
int main() {
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "Tic-Tac-Toe",sf::Style::Close | sf::Style::Titlebar); //設定視窗大小 1024*1024 並固定

    // 獲取視窗的大小
    sf::Vector2u windowSize = window.getSize();

    // 計算線條的長度和寬度
    float lineLength = windowSize.x ; 
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
            break;
        }
    }

    return 0;
}
