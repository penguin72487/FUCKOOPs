#include <SFML/Graphics.hpp>
#include <iostream>

class CountdownTimer {
public:
    CountdownTimer(sf::Font& font, sf::RenderWindow& window);
    void start(int seconds);

private:
    sf::Text timerText;
    sf::RenderWindow& window;
};

CountdownTimer::CountdownTimer(sf::Font& font, sf::RenderWindow& window) : window(window) {
    timerText.setFont(font);
    timerText.setCharacterSize(40);
    timerText.setFillColor(sf::Color::White);
}

void CountdownTimer::start(int seconds) {
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Time elapsed = clock.getElapsedTime();
        int secondsLeft = seconds - static_cast<int>(elapsed.asSeconds());

        if (secondsLeft >= 0) {
            timerText.setString(std::to_string(secondsLeft));
        } else {
            timerText.setString("Time's up!");
            // 计时结束，回到 "Enter Time" 状态
            window.clear();
            window.display();
            break;
        }

        window.clear();
        window.draw(timerText);
        window.display();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 200), "UI Example");

    sf::Font font;
    if (!font.loadFromFile("../data/ttf/arial.ttf")) {
        std::cerr << "Error loading font." << std::endl;
        return -1;
    }

    sf::Text uiText("", font, 20);
    uiText.setPosition(10, 50);

    std::string inputString;
    bool inputSucceed = false;
    bool countdownInProgress = false;  // 新增倒數計時狀態

    CountdownTimer countdownTimer(font, window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                else if (event.key.code == sf::Keyboard::Return) {
                    // Enter key pressed
                    if (!inputSucceed && !countdownInProgress) {
                        std::cout << "Input successful: " << inputString << std::endl;
                        inputSucceed = true;
                        uiText.setString("Input successful: " + inputString);

                        // Start countdown timer
                        int seconds = std::stoi(inputString);  // Convert input string to integer
                        countdownInProgress = true;
                        countdownTimer.start(seconds);

                        // Reset input fields
                        inputSucceed = false;
                        countdownInProgress = false;  // 回到 "Enter Time" 狀態
                        uiText.setString("Enter Time:");
                        inputString.clear();
                    } else {
                        inputSucceed = false;
                        countdownInProgress = false;  // 如果在倒數計時過程中按下 Enter，也回到 "Enter Time" 狀態
                        uiText.setString("Enter Time:");
                        inputString.clear();
                    }
                }
                else if (event.key.code == sf::Keyboard::Backspace) {
                    // Backspace key pressed
                    if (!inputSucceed) {
                        if (!inputString.empty()) {
                            inputString.pop_back();
                            uiText.setString("Enter Time: " + inputString);
                        }
                    }
                }
            }
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode >= 48 && event.text.unicode <= 57) {
                    // Only accept numeric input
                    inputString += static_cast<char>(event.text.unicode);
                    uiText.setString("Enter Time: " + inputString);
                }
            }
        }

        window.clear();
        window.draw(uiText);
        window.display();
    }

    return 0;
}
