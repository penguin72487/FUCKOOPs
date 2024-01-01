#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "UTF-8 Test with SFML");
    sf::Font font;

    // 確保替換下面的路徑為你的系統上的字體文件路徑
    if (!font.loadFromFile("TaipeiSansTCBeta-Regular.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }

    sf::Text text;
    text.setFont(font);
    text.setString(L"測試繁體中文顯示");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(100, 100);

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
