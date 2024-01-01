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
    


public:

    UIManager():window(sf::VideoMode(1400, 1024), "TIC-TAC-TOC"), 
        mainMenu(window), settingsMenu(window), gameSelectionMenu(window), gameInterface(window), gameEndScreen(window), resultScreen(window) {
        // 初始化 UI 管理器
        // sf::RenderWindow window(sf::VideoMode(800, 900), "TIC-TAC-TOC");
        window.setFramerateLimit(60);
        currentScreen = mainMenu.render();
    }
    ~UIManager() {}
    void run() {
        while (window.isOpen()) {
            renderScreen();
        }
    }
    void renderScreen(){
        switch (currentScreen) {
            case UIComponent::Screen::MAIN_MENU:
                currentScreen =mainMenu.render();
                break;
            case UIComponent::Screen::SETTINGS_MENU:
                currentScreen =settingsMenu.render();
                break;
            case UIComponent::Screen::GAME_SELECTION_MENU:
                currentScreen=gameSelectionMenu.render();
                break;
            case UIComponent::Screen::GAME_BASIC_INTERFACE:
                currentScreen=gameInterface.render(currentScreen);
                break;
            case UIComponent::Screen::GAME_ULTIMATE_INTERFACE:
                currentScreen=gameInterface.render(currentScreen);
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

    // 其他 UI 管理功能
};