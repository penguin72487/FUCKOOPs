#pragma once

#include "UIComponent.hpp"
#include "Button.hpp"

class GameInterface : public UIComponent {
private:
    Button MenuButton;
    Button RestartButton;
    Button board;  // 棋盤

public:
    GameInterface(sf::RenderWindow& window);

    Screen render() override;
};
