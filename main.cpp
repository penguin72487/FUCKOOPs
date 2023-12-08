#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

// 定義遊戲狀態
enum class Player { None, O, X };
Player currentPlayer = Player::O;
Player board[3][3] = {{Player::None, Player::None, Player::None}, 
                      {Player::None, Player::None, Player::None}, 
                      {Player::None, Player::None, Player::None}};

// 檢查勝利條件
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

    return Player::None;
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
    sf::RenderWindow window(sf::VideoMode(300, 300), "Tic-Tac-Toe");
    sf::RectangleShape line1(sf::Vector2f(300, 5)), line2(sf::Vector2f(300, 5)),
                        line3(sf::Vector2f(5, 300)), line4(sf::Vector2f(5, 300));

    line1.setPosition(0, 100);
    line2.setPosition(0, 200);
    line3.setPosition(100, 0);
    line4.setPosition(200, 0);

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
            std::cout << (winner == Player::O ? "O wins!" : "X wins!") << std::endl;
            break;
        }
    }

    return 0;
}
