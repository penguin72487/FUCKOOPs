#include"Button.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 900), "TIC-TAC-TOC");
    sf::Font font;
    if (!font.loadFromFile("TaipeiSansTCBeta-Regular.ttf")) {
        // handle error
    }

    // create title
    sf::Text title("TIC-TAC-TOC", font, 50);
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 50);

    // create buttons
    Button illustrateButton(650, 20, 130, 50, "Illustrate", font);
    Button settingButton(650, 90, 130, 50, "Setting", font);
    Button startGameButton(350, 600, 130, 50, "StartGame", font);
    Button exitGameButton(350, 670, 130, 50, "Exit", font);
    Button developerButton(650, 830, 130, 50, "Developer", font);

    sf::Color color(79, 126, 146);

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