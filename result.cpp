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
        text.setCharacterSize(60); // in pixels
        text.setFillColor(sf::Color::Black);
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
        // ???ç¤ºè????¥å¤±???
        return EXIT_FAILURE;
    }

    // è¨­å??çª???????ç¤?
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Text s1("Congratuation Player__!!", font, 80);
    s1.setFillColor(sf::Color(255, 255, 255));
    s1.setPosition(234, 60); 

    // create title
    sf::Text s2("You have played __", font, 65);
    s2.setFillColor(sf::Color(255, 255, 255));
    s2.setPosition(110, 206);

    sf::Text s3("Player1\nwin:__(__)%\nlose:__(__)%", font, 65);

    s3.setFillColor(sf::Color(255, 255, 255));
    s3.setPosition(110, 359);

    sf::Text s4("Player1\nwin:__(__)%\nlose:__(__)%", font, 65);
    s4.setFillColor(sf::Color(255, 255, 255));
    s4.setPosition(110,650);


    Button BackButton(490, 914, 420, 85, "menu", font);

    sf::Color color(224, 171, 114);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // check if buttons are clicked
            if (BackButton.isClicked(event)) {
                // do something
            }
        }

        window.clear(color);
        // draw title and buttons
        window.draw(s1);
        window.draw(s2);
        window.draw(s3);
        window.draw(s4);
        window.draw(BackButton.shape);
        window.draw(BackButton.text);
        window.display();
    }
    
    return 0;
}