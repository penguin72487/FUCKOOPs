#pragma once

#include "MainMenu.hpp"
#include "SettingsMenu.hpp"
#include "GameSelectionMenu.hpp"
#include "GameInterface.hpp"
#include "GameEndScreen.hpp"
#include "ResultScreen.hpp"

class UIManager {
private:
    sf::RenderWindow window;

    MainMenu mainMenu;
    SettingsMenu settingsMenu;
    GameSelectionMenu gameSelectionMenu;
    GameInterface gameInterface;
    GameEndScreen gameEndScreen;
    ResultScreen resultScreen;

    UIComponent::Screen currentScreen;

public:
    UIManager();

    ~UIManager();

    void run();

    void renderScreen();

    // Other UI manager functionality
};
