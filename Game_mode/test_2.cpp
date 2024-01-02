#include <SFML/Graphics.hpp>
#include <iostream>

class UIElement {
public:
    UIElement(sf::Font& font, sf::RenderWindow& window, const std::string& defaultText);
    virtual ~UIElement() = default;
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

protected:
    sf::Text text;
    sf::RenderWindow& window;
};

UIElement::UIElement(sf::Font& font, sf::RenderWindow& window, const std::string& defaultText)
    : window(window) {
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setString(defaultText);
}

class TextInput : public UIElement {
public:
    using UIElement::UIElement;
    void handleEvent(const sf::Event& event) override;
    void update() override;
    void draw() override;
    std::string getInputString() const;

private:
    std::string inputString;
    bool inputSucceed = false;
};

void TextInput::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Backspace) {
            // Backspace key pressed
            if (!inputSucceed && !inputString.empty()) {
                inputString.pop_back();
                text.setString("Enter Time: " + inputString);
            }
        }
    } else if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode >= 48 && event.text.unicode <= 57) {
            // Only accept numeric input
            inputString += static_cast<char>(event.text.unicode);
            text.setString("Enter Time: " + inputString);
        }
    }
}

void TextInput::update() {
    // Additional logic for TextInput update if needed
}

void TextInput::draw() {
    window.draw(text);
}

std::string TextInput::getInputString() const {
    return inputString;
}

class CountdownTimer : public UIElement {
public:
    using UIElement::UIElement;
    void handleEvent(const sf::Event& event) override;
    void update() override;
    void draw() override;
    void start(int seconds);

private:
    sf::Clock clock;
    int totalSeconds; // Renamed from 'seconds' to 'totalSeconds'
    int secondsLeft;
    bool countdownInProgress = false;
};

void CountdownTimer::handleEvent(const sf::Event& event) {
    // Handle specific events for CountdownTimer if needed
}

void CountdownTimer::update() {
    if (countdownInProgress) {
        sf::Time elapsed = clock.getElapsedTime();
        secondsLeft = totalSeconds  - static_cast<int>(elapsed.asSeconds());

        if (secondsLeft >= 0) {
            text.setString(std::to_string(secondsLeft));
        } else {
            text.setString("Time's up!");
            // Additional logic for countdown completion
            countdownInProgress = false;
        }
    }
}

void CountdownTimer::draw() {
    window.draw(text);
}

void CountdownTimer::start(int seconds) {
    this->totalSeconds  = seconds;
    countdownInProgress = true;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 200), "UI Example");

    sf::Font font;
    if (!font.loadFromFile("../data/ttf/arial.ttf")) {
        std::cerr << "Error loading font." << std::endl;
        return -1;
    }

    TextInput textInput(font, window, "Enter Time:");
    CountdownTimer countdownTimer(font, window, "");

    UIElement* currentElement = &textInput;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else {
                currentElement->handleEvent(event);
            }
        }

        currentElement->update();

        window.clear();
        currentElement->draw();
        window.display();
    }

    return 0;
}
