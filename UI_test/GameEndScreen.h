#pragma once

#include "UIComponent.hpp"
#include "Button.hpp"

class GameEndScreen : public UIComponent {
private:
    sf::Text winMessege;
    Button AgainButton;
    Button ResultButton;
    Button BackButton;

public:
    GameEndScreen(sf::RenderWindow& window);

    Screen render() override;
};
