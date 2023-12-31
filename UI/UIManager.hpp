#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Button.hpp"
class UIComponent {
public:
    enum class Screen {
        MAIN_MENU,
        SETTINGS_MENU,
        GAME_SELECTION_MENU,
        GAME_INTERFACE,
        RESULT_SCREEN,
        EXIT

    };
    virtual Screen render() = 0;
    sf::Font font;
    sf::Color color = sf::Color(79, 126, 146);
    sf::RenderWindow& window;

    UIComponent(sf::RenderWindow& win) : window(win){
        if (!font.loadFromFile("TaipeiSansTCBeta-Regular.ttf")) {
            // handle error
        }
    }
    virtual ~UIComponent() {}

    // 其他通用 UI 功能
};

class MainMenu : public UIComponent {
private:
    sf::Text title;
    Button illustrateButton;
    Button settingButton;
    Button startGameButton;
    Button exitGameButton;
    Button developerButton;

public:
    MainMenu(sf::RenderWindow& window) : UIComponent(window), 
                                      illustrateButton(650, 20, 130, 50, "Illustrate", font),
                                      settingButton(650, 90, 130, 50, "Setting", font),
                                      startGameButton(350, 600, 130, 50, "StartGame", font),
                                      exitGameButton(350, 670, 130, 50, "Exit", font),
                                      developerButton(650, 830, 130, 50, "Developer", font) {
        title = sf::Text("TIC-TAC-TOC", font, 50);
        title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 50);
    }

    Screen render() override {
        while (window.isOpen()) {
                window.clear(color);
                // draw title and buttons
                window.draw(title);
                window.draw(illustrateButton.shape);
                window.draw(illustrateButton.text);
                window.draw(settingButton.shape);
                window.draw(settingButton.text);
                window.draw(startGameButton.shape);
                window.draw(startGameButton.text);
                window.draw(exitGameButton.shape);
                window.draw(exitGameButton.text);
                window.draw(developerButton.shape);
                window.draw(developerButton.text);
                window.display();
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();

                    // check if buttons are clicked
                    if (illustrateButton.isClicked(event)) {
                        // do something
                    }
                    if (settingButton.isClicked(event)) {
                        return Screen::SETTINGS_MENU;
                    }
                    if (startGameButton.isClicked(event)) {
                        return Screen::GAME_SELECTION_MENU;
                    }
                    if (exitGameButton.isClicked(event)) {
                        return Screen::EXIT;
                    }
                    if (developerButton.isClicked(event)) {
                        // do something
                    }
                }


        }
        return Screen::EXIT;
    }
};

// 設置菜單
class SettingsMenu : public UIComponent {
public:
    SettingsMenu(sf::RenderWindow& window) : UIComponent(window) {

    }
    Screen render() override {
        std::cout << "Settings Menu: [Settings Options]" << std::endl;
        return Screen::MAIN_MENU;
    }
    // 其他設置功能
};

// 遊戲選擇菜單
class GameSelectionMenu : public UIComponent {
public:
    GameSelectionMenu(sf::RenderWindow& window) : UIComponent(window) {

    }

    Screen render() override {
        std::cout << "Game Selection Menu: [List of Games]" << std::endl;
        return Screen::MAIN_MENU;
    }
    // 其他遊戲選擇功能
};

// 遊戲介面
class GameInterface : public UIComponent {
public:
    GameInterface(sf::RenderWindow& window) : UIComponent(window) {

    }
    Screen render() override {
        std::cout << "Game Interface: [Gameplay Elements]" << std::endl;
        return Screen::MAIN_MENU;
    }
    // 其他遊戲功能
};

// 結果/得分頁面
class ResultScreen : public UIComponent {
public:
    ResultScreen(sf::RenderWindow& window) : UIComponent(window) {

    }
    Screen render() override {
        std::cout << "Result Screen: [Results and Scores]" << std::endl;
        return Screen::MAIN_MENU;
    }
    // 其他結果展示功能
};

// // UI 管理器
class UIManager {
public:


private:
    sf::RenderWindow window;

    MainMenu mainMenu;
    SettingsMenu settingsMenu;
    GameSelectionMenu gameSelectionMenu;
    GameInterface gameInterface;
    ResultScreen resultScreen;
    // std::vector<UIComponent*> screens;

    UIComponent::Screen currentScreen;
    


public:

    UIManager():window(sf::VideoMode(800, 900), "TIC-TAC-TOC"), mainMenu(window), settingsMenu(window),gameSelectionMenu(window), gameInterface(window), resultScreen(window) {
        // 初始化 UI 管理器
        // sf::RenderWindow window(sf::VideoMode(800, 900), "TIC-TAC-TOC");
        
    }
    ~UIManager() {}
    void run() {
        while (window.isOpen()) {
            renderScreen();
        }
    }
    void renderScreen(){
        currentScreen = mainMenu.render();
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
            case UIComponent::Screen::GAME_INTERFACE:
                currentScreen=gameInterface.render();
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