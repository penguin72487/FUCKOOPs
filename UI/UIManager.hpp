#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "UIComponent.hpp"
#include "MainMenu.hpp"
#include "SettingsMenu.hpp"
#include "GameSelectionMenu.hpp"
#include "GameInterface.hpp"
#include "GameEndScreen.hpp"
#include "ResultScreen.hpp"
// #include "../Game/basic.hpp"
// #include "../Game/ultimate.hpp"

// // UI 管理器
class UIManager {
public:


private:
    sf::RenderWindow window;

    MainMenu mainMenu;
    SettingsMenu settingsMenu;
    GameSelectionMenu gameSelectionMenu;
    GameInterface gameInterface;
    GameEndScreen gameEndScreen;
    ResultScreen resultScreen;
    // std::vector<UIComponent*> screens;

    UIComponent::Screen currentScreen;
    std::shared_ptr<Game> currentGame;
    


public:

    UIManager():window(sf::VideoMode(1400, 1024), "TIC-TAC-TOC"), 
        mainMenu(window), settingsMenu(window), gameSelectionMenu(window), gameInterface(window), gameEndScreen(window), resultScreen(window) {
        // 初始化 UI 管理器
        window.setFramerateLimit(60);
        currentScreen = mainMenu.render();
        currentGame = nullptr;
    }
    ~UIManager() {}
    void run() {
        while (window.isOpen()) {
            renderScreen();
        }
    }
    void renderScreen(){
    std::tuple<UIComponent::Screen, std::shared_ptr<Game>> renderResult;
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
        case UIComponent::Screen::GAME_BASIC_INTERFACE:
            renderResult = gameInterface.render(currentScreen);
            std::cout << "Game Basic Interface: [Gameplay Elements]" << std::endl;
            currentScreen = std::get<0>(renderResult);
            currentGame = std::get<1>(renderResult);
            break;
        case UIComponent::Screen::GAME_ULTIMATE_INTERFACE:
            renderResult = gameInterface.render(currentScreen);
            currentScreen = std::get<0>(renderResult);
            currentGame= std::get<1>(renderResult);
            break;
        case UIComponent::Screen::GAME_END_SCREEN:
            currentScreen = gameEndScreen.render(currentGame);
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

    // 其他 UI 管理功能
};