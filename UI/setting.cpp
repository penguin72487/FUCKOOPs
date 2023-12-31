#include <SFML/Graphics.hpp>

class Button {
public:
    sf::RectangleShape shape;
    sf::Text text;

    Button(float x, float y, float width, float height, std::string buttonText, sf::Font& font) {
        shape.setPosition(sf::Vector2f(x, y));
        shape.setSize(sf::Vector2f(width, height));
        shape.setOutlineColor(sf::Color(224, 171, 114));
        shape.setOutlineThickness(2);
        shape.setFillColor(sf::Color(173, 216, 230));

        text.setFont(font);
        text.setString(buttonText);
        text.setCharacterSize(24); // in pixels
        text.setFillColor(sf::Color::White);
        text.setPosition(
            shape.getPosition().x + (shape.getSize().x / 2) - (text.getGlobalBounds().width / 2),
            shape.getPosition().y + (shape.getSize().y / 2) - (text.getGlobalBounds().height / 2)-8
        );
    }

    bool isClicked(sf::Event event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (shape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1400, 1024), "SETTING");
    sf::Font font;
    if (!font.loadFromFile("TaipeiSansTCBeta-Regular.ttf")) {
        // handle error
    }

    sf::Image icon;
    if (!icon.loadFromFile("OOXX.png")) {
        // 圖示載入失敗
        return EXIT_FAILURE;
    }

    // 設定窗口圖示
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // create title
    sf::Text colorset("SETTING COLOR", font, 50);
    colorset.setFillColor(sf::Color(255, 255, 255));
    colorset.setPosition(50, 377);    
    
    sf::Text timeset("SETTING TIME", font, 50);
    timeset.setFillColor(sf::Color(255, 255, 255));
    timeset.setPosition(50, 622);

    Button MenuButton(57, 36, 160, 70, "MENU", font);

    sf::Color color(224, 171, 114);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // check if buttons are clicked
            if (MenuButton.isClicked(event)) {
                // do something
            }
        }

        window.clear(color);
        // draw title and buttons
        window.draw(colorset);
        window.draw(timeset);
        window.draw(MenuButton.shape);
        window.draw(MenuButton.text);
        window.display();


    }
    
    return 0;
}