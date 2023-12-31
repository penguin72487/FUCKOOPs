#include <SFML/Graphics.hpp>
#include "Button.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1400, 1024), "SETTING");
    sf::Font font;
    if (!font.loadFromFile("TaipeiSansTCBeta-Regular.ttf")) {
        // handle error
    }

    sf::Image icon;
    if (!icon.loadFromFile("OOXX.png")) {
        // ???蝷箄????亙仃???
        return EXIT_FAILURE;
    }

    // 閮剖??蝒???????蝷?
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Text s1("Player__ Win!!", font, 80);
    s1.setFillColor(sf::Color(255, 255, 255));
    s1.setPosition(420, 83); 


    Button AgainButton(560, 512, 280, 85, "Again", font);
    Button ResultButton(560, 687, 280, 85, "Result", font);
    Button BackButton(560, 862, 280, 85, "Menu", font);

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
        window.draw(AgainButton.shape);
        window.draw(AgainButton.text);
        window.draw(ResultButton.shape);
        window.draw(ResultButton.text);
        window.draw(BackButton.shape);
        window.draw(BackButton.text);
        window.display();
    }
    
    return 0;
}