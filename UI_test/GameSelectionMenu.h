#pragma once

#include "UIComponent.hpp"
#include "Button.hpp"

class GameSelectionMenu : public UIComponent {
private:
    sf::Text basictext;
    sf::Text advancetext;
    Button MenuButton;
    Button BasicButton;
    Button AdvanceButton;

public:
    GameSelectionMenu(sf::RenderWindow& window);

    Screen render() override;
};
