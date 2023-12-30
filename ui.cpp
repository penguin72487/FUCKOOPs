#include <SFML/Graphics.hpp>

class Button {
public:
    sf::RectangleShape shape;
    sf::Text text;

    Button(float x, float y, float width, float height, std::string buttonText, sf::Font& font) {
        shape.setPosition(sf::Vector2f(x, y));
        shape.setSize(sf::Vector2f(width, height));
        shape.setOutlineColor(sf::Color(79, 126, 146));
        shape.setOutlineThickness(2);
        shape.setFillColor(sf::Color(145, 163, 176));

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
    sf::RenderWindow window(sf::VideoMode(800, 900), "TIC-TAC-TOC");
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
    sf::Text title("TIC-TAC-TOC", font, 80);
    title.setFillColor(sf::Color(83, 104, 120));
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 100);

    sf::Texture pic;
    if (!pic.loadFromFile("OOXX.png")) {
        // 紋理載入失敗
        return EXIT_FAILURE;
    }

    sf::Sprite picture(pic);
    picture.setScale(0.8,0.8);
    picture.setPosition(400-picture.getGlobalBounds().width/2, 400-picture.getGlobalBounds().height/2);

    // create buttons
    Button illustrateButton(650, 20, 130, 50, "Illustrate", font);
    Button settingButton(650, 90, 130, 50, "Setting", font);
    Button startGameButton(350, 700, 130, 50, "StartGame", font);
    Button exitGameButton(350, 800, 130, 50, "Exit", font);
    Button developerButton(650, 830, 130, 50, "Developer", font);

    sf::Color color(145, 163, 176);//79,126,146/156,173,206

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // check if buttons are clicked
            if (illustrateButton.isClicked(event)) {
                // do something
            }
            if (settingButton.isClicked(event)) {
                // do something
            }
            if (startGameButton.isClicked(event)) {
                // do something
            }
            if (exitGameButton.isClicked(event)) {
                window.close();
            }
            if (developerButton.isClicked(event)) {
                // do something
            }
        }

        window.clear(color);
        // draw title and buttons
        window.draw(title);
        window.draw(picture);
        window.draw(illustrateButton.shape);
        window.draw(illustrateButton.text);
        window.draw(settingButton.shape);
        window.draw(settingButton.text);
        window.draw(startGameButton.shape);
        window.draw(startGameButton.text);
        window.draw(exitGameButton.shape);
        window.draw(exitGameButton.text);
        window.draw(developerButton.shape);
        window.draw(developerButton.text);
        window.display();
    }

    return 0;
}