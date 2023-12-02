#include <SFML/Graphics.hpp>
#include <array>

// Define some constants for the game
const int cellSize = 200;
const sf::Vector2f cellSizeVec(cellSize, cellSize);
const sf::Vector2i boardSize(3, 3);

// Enum to represent each player and empty cells
enum class Player { None, O, X };

// Game board is a 3x3 array
typedef std::array<std::array<Player, 3>, 3> Board;

// Function to draw X and O
void drawXO(sf::RenderWindow& window, const sf::Vector2f& position, Player player) {
    sf::CircleShape circle(80);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(10);
    circle.setOutlineColor(sf::Color::Blue);
    circle.setPosition(position);

    sf::RectangleShape line1(sf::Vector2f(10, 200));
    line1.setFillColor(sf::Color::Red);
    line1.setPosition(position);
    line1.rotate(45);

    sf::RectangleShape line2(sf::Vector2f(10, 200));
    line2.setFillColor(sf::Color::Red);
    line2.setPosition(position.x + cellSize, position.y);
    line2.rotate(135);

    if (player == Player::O) {
        window.draw(circle);
    } else if (player == Player::X) {
        window.draw(line1);
        window.draw(line2);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(cellSize * boardSize.x, cellSize * boardSize.y), "Tic-Tac-Toe");
    Board board{};
    Player currentPlayer = Player::X;
    bool gameOver = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed && !gameOver) {
                int row = event.mouseButton.y / cellSize;
                int col = event.mouseButton.x / cellSize;
                if (board[row][col] == Player::None) {
                    board[row][col] = currentPlayer;
                    currentPlayer = (currentPlayer == Player::O) ? Player::X : Player::O;
                    // Check for win or draw here
                }
            }
        }

        window.clear(sf::Color::White);

        // Draw the game board grid lines
        for (int i = 1; i < boardSize.x; ++i) {
            sf::RectangleShape line(sf::Vector2f(cellSize * boardSize.x, 5));
            line.setFillColor(sf::Color::Black);
            line.setPosition(0, cellSize * i);
            window.draw(line);
        }
        for (int i = 1; i < boardSize.y; ++i) {
            sf::RectangleShape line(sf::Vector2f(5, cellSize * boardSize.y));
            line.setFillColor(sf::Color::Black);
            line.setPosition(cellSize * i, 0);
            window.draw(line);
        }

        // Draw the X's and O's
        for (int row = 0; row < boardSize.x; ++row) {
            for (int col = 0; col < boardSize.y; ++col) {
                if (board[row][col] != Player::None) {
                    drawXO(window, sf::Vector2f(col * cellSize, row * cellSize), board[row][col]);
                }
            }
        }

        window.display();
    }

    return 0;
}
