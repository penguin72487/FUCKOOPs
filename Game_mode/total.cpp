#include <SFML/Graphics.hpp>
#include <iostream>

class CountdownTimer {
public:
    CountdownTimer(int seconds);
    void start();

private:
    int countdownSeconds;
    sf::Font font;
    sf::Text timerText;
    sf::RenderWindow window{sf::VideoMode(400, 200), "Countdown Timer"};
};


CountdownTimer::CountdownTimer(int seconds) : countdownSeconds(seconds) {
    if (!font.loadFromFile("arial.ttf")) {
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


int main() {
    CountdownTimer countdownTimer(10);  // 設定倒數時間為5秒

    // 在此處添加任何其他測試邏輯或檢查

    countdownTimer.start();  // 開始倒數計時

    return 0;
}
