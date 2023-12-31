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