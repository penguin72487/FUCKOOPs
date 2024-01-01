#pragma once

#include "UIComponent.hpp"
#include "Button.hpp"

class SettingsMenu : public UIComponent {
private:
    sf::Text colorset;
    sf::Text timeset;
    Button MenuButton;

public:
    SettingsMenu(sf::RenderWindow& window);

    Screen render() override;
};
