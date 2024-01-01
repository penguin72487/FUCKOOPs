#pragma once

#include "UIComponent.hpp"
#include "Button.hpp"

class ResultScreen : public UIComponent {
private:
    sf::Text playerCongratulationText;
    sf::Text gamePlayedText;
    sf::Text player1StatsText;
    sf::Text player2StatsText;
    Button BackButton;

public:
    ResultScreen(sf::RenderWindow& window);

    Screen render() override;
};
