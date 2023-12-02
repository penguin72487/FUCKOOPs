#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Test");

    sf::Font font;
    // 在 Windows 系統中，可以嘗試加載 "C:\\Windows\\Fonts\\arial.ttf"
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        return -1;
    }

    sf::Text text("Hello SFML", font, 40);
    text.setFillColor(sf::Color::Red);
    text.setPosition(200, 220);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(text);
        window.display();
    }

    return 0;
}
