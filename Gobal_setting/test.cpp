#include <SFML/Graphics.hpp>
#include <iostream>

class TicTacToe {
public:
    TicTacToe() : window(sf::VideoMode(300, 300), "Tic Tac Toe") {
        setup();
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text playerTurnText;
    sf::RectangleShape board[3][3];
    sf::Color oColor = sf::Color::Blue;
    sf::Color xColor = sf::Color::Red;
    sf::Color boardColor = sf::Color::White;

    int currentPlayer = 1; // 1 for O, 2 for X
    int boardState[3][3] = {0}; // 0 for empty, 1 for O, 2 for X

    void setup() {
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Error loading font" << std::endl;
        }

        playerTurnText.setFont(font);
        playerTurnText.setCharacterSize(20);
        playerTurnText.setFillColor(sf::Color::Black);

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                board[i][j].setSize(sf::Vector2f(100, 100));
                board[i][j].setOutlineThickness(2);
                board[i][j].setOutlineColor(sf::Color::Black);
                board[i][j].setPosition(i * 100, j * 100);
                board[i][j].setFillColor(boardColor);
            }
        }
    }

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    handleMouseClick(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }
    }

    void handleMouseClick(int x, int y) {
        int i = x / 100;
        int j = y / 100;

        if (i >= 0 && i < 3 && j >= 0 && j < 3 && boardState[i][j] == 0) {
            boardState[i][j] = currentPlayer;
            currentPlayer = 3 - currentPlayer; // Switch player (1 to 2, 2 to 1)
        }
    }

    void update() {
        checkWin();
        updatePlayerTurnText();
    }

    void checkWin() {
        // TODO: Implement win condition logic
    }

    void updatePlayerTurnText() {
        playerTurnText.setString("Player " + std::to_string(currentPlayer) + "'s turn");
        playerTurnText.setPosition(10, 260);
    }

    void render() {
        window.clear();

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                window.draw(board[i][j]);
            }
        }

        window.draw(playerTurnText);

        window.display();
    }
};

int main() {
    TicTacToe game;
    game.run();

    return 0;
}
