#ifndef COUNTDOWNTIMER_H
#define COUNTDOWNTIMER_H

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

#endif // COUNTDOWNTIMER_H
