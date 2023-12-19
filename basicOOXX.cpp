// 定義遊戲狀態
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
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