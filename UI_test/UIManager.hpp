#include "UIManager.h"

UIManager::UIManager() : window(sf::VideoMode(1400, 1024), "TIC-TAC-TOC"),
    mainMenu(window), settingsMenu(window), gameSelectionMenu(window),
    gameInterface(window), gameEndScreen(window), resultScreen(window) {
    window.setFramerateLimit(120);
    currentScreen = mainMenu.render();
}

UIManager::~UIManager() {}

void UIManager::run() {
    while (window.isOpen()) {
        renderScreen();
    }
}

void UIManager::renderScreen() {
    switch (currentScreen) {
        case UIComponent::Screen::MAIN_MENU:
            currentScreen = mainMenu.render();
            break;
        case UIComponent::Screen::SETTINGS_MENU:
            currentScreen = settingsMenu.render();
            break;
        case UIComponent::Screen::GAME_SELECTION_MENU:
            currentScreen = gameSelectionMenu.render();
            break;
        case UIComponent::Screen::GAME_INTERFACE:
            currentScreen = gameInterface.render();
            break;
        case UIComponent::Screen::GAME_END_SCREEN:
            currentScreen = gameEndScreen.render();
            break;
        case UIComponent::Screen::RESULT_SCREEN:
            currentScreen = resultScreen.render();
            break;
        case UIComponent::Screen::EXIT:
            window.close();
            break;
        default:
            break;
    }
}
