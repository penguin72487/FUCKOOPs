#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

enum class Player { None, O, X, Draw };

Player currentPlayer = Player::O;
std::vector<std::vector<Player>> board(3, std::vector<Player>(3, Player::None));

bool isLineWin(Player a, Player b, Player c) {
    return (a == b) && (b == c) && (a != Player::None);
}

Player checkWin() {
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
            if (cell == Player::None) return Player::None;
        }
    }

    return Player::Draw;
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
    currentPlayer = Player::O;
    for (auto &row : board) {
        std::fill(row.begin(), row.end(), Player::None);
    }
}
