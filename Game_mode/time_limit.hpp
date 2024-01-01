#include "time_limit.h"

CountdownTimer::CountdownTimer(int seconds) : countdownSeconds(seconds) {
    if (!font.loadFromFile("../data/ttf/arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    timerText.setFont(font);
    timerText.setCharacterSize(40);
    timerText.setFillColor(sf::Color::White);
}

void CountdownTimer::start() {
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Time elapsed = clock.getElapsedTime();
        int secondsLeft = countdownSeconds - static_cast<int>(elapsed.asSeconds());

        if (secondsLeft >= 0) {
            timerText.setString(std::to_string(secondsLeft));
        } else {
            timerText.setString("Time's up!");
        }

        window.clear();
        window.draw(timerText);
        window.display();
    }
}
