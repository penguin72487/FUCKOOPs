#include <SFML/Graphics.hpp>
#include <iostream>

class UIElement {
public:
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(sf::RenderWindow& window) = 0;
};

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
            // Countdown ends, return to "Enter Time" state
            window.clear();
            window.display();
            break;
        }

        window.clear();
        window.draw(timerText);
        window.display();
    }
}

class TextInput : public UIElement {
public:
    TextInput(sf::Font& font, sf::RenderWindow& window);
    void handleEvent(const sf::Event& event) override;
    void update() override;
    const std::string& getText() const;
    bool isInputSucceed() const;
    bool isCountingDown() const;
    void reset();
    void update(sf::RenderWindow& window) override {
        window.draw(text);
    }

private:
    std::string inputString;
    bool inputSucceed;
    bool countingDown;
    sf::Text text;
};

TextInput::TextInput(sf::Font& font, sf::RenderWindow& window) : inputSucceed(false), countingDown(false) {
    text.setFont(font);
    text.setCharacterSize(20);
    text.setPosition(10, 50);
    text.setString("Enter Time: ");
}

void TextInput::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Return) {
            if (!inputSucceed && !countingDown) {
                std::cout << "Input successful: " << inputString << std::endl;
                inputSucceed = true;
                text.setString("Input successful: " + inputString);
                countingDown = true;
            } else {
                inputSucceed = false;
                countingDown = false;
                text.setString("Enter Time: ");
            }
        }
        else if (event.key.code == sf::Keyboard::Backspace) {
            if (!inputSucceed) {
                if (!inputString.empty()) {
                    inputString.pop_back();
                    text.setString("Enter Time: " + inputString);
                }
            }
        }
    }
    else if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode >= 48 && event.text.unicode <= 57) {
            // Only accept numeric input
            inputString += static_cast<char>(event.text.unicode);
            text.setString("Enter Time: " + inputString);
        }
    }
}

void TextInput::update() {
    window.draw(text);
}

const std::string& TextInput::getText() const {
    return inputString;
}

bool TextInput::isInputSucceed() const {
    return inputSucceed;
}

bool TextInput::isCountingDown() const {
    return countingDown;
}

void TextInput::reset() {
    inputString.clear();
    inputSucceed = false;
    countingDown = false;
    text.setString("Enter Time: ");
}

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 200), "UI Example");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font." << std::endl;
        return -1;
    }

    std::unique_ptr<UIElement> uiElement = std::make_unique<TextInput>(font, window);
    CountdownTimer countdownTimer(font, window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            uiElement->handleEvent(event);
        }

        window.clear();
        uiElement->update();

        if (dynamic_cast<TextInput*>(uiElement.get())->isInputSucceed() &&
            !dynamic_cast<TextInput*>(uiElement.get())->isCountingDown()) {
            try {
                countdownTimer.start(std::stoi(dynamic_cast<TextInput*>(uiElement.get())->getText()));
                dynamic_cast<TextInput*>(uiElement.get())->reset();  // 重置輸入狀態
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid input: " << e.what() << std::endl;
                // Handle the invalid input error
                dynamic_cast<TextInput*>(uiElement.get())->reset();  // 重置輸入狀態
            }
        }

        window.display();
    }

    return 0;
}
