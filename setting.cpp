#include <SFML/Graphics.hpp>

class Button {
public:
    sf::RectangleShape shape;
    sf::Text text;

    Button(float x, float y, float width, float height, std::string buttonText, sf::Font& font) {
        shape.setPosition(sf::Vector2f(x, y));
        shape.setSize(sf::Vector2f(width, height));
        shape.setOutlineColor(sf::Color(0, 0, 0));
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
    sf::RenderWindow window(sf::VideoMode(1400, 1024), "TIC-TAC-TOC");
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
    sf::Text title("TIC-TAC-TOC!!!", font, 170);
    title.setFillColor(sf::Color(255, 255, 255));
    title.setPosition(57, 57);

    sf::Texture pic;
    if (!pic.loadFromFile("OOXX.png")) {
        // 紋理載入失敗
        return EXIT_FAILURE;
    }

    sf::Sprite picture(pic);
    picture.setScale(1.2,1.2);
    picture.setPosition(540,314);

    // create buttons
    Button illustrateButton(57, 650, 160, 70, "ILLUSTRATE", font);
    Button settingButton(57, 500, 160, 70, "SETTING", font);
    Button startGameButton(57, 350, 160, 70, "STARTGAME", font);
    Button exitGameButton(57, 800, 160, 70, "EXIT", font);
    Button developerButton(1200, 900, 160, 70, "DEVELOPER", font);

    sf::Color color(224, 171, 114);

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