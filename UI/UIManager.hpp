#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Button.hpp"
class UIManager;
enum Screen {
    MAIN_MENU,
    // SETTINGS_MENU,
    GAME_SELECTION_MENU,
    // GAME_INTERFACE,
    // RESULT_SCREEN
};
// class SettingsMenu;
// class GameInterface;
// class ResultScreen;

class UIComponent {
public:
    virtual void render() = 0;
    sf::Font font;
    sf::Color color = sf::Color(79, 126, 146);
    sf::RenderWindow& window;
    UIManager& uiManager;

    UIComponent(sf::RenderWindow& win,UIManager& manager) : window(win), uiManager(manager) {
        if (!font.loadFromFile("TaipeiSansTCBeta-Regular.ttf")) {
            // handle error
        }
    }

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
    MainMenu(sf::RenderWindow& window,UIManager& manager) : UIComponent(window,manager), 
                                      illustrateButton(650, 20, 130, 50, "Illustrate", font),
                                      settingButton(650, 90, 130, 50, "Setting", font),
                                      startGameButton(350, 600, 130, 50, "StartGame", font),
                                      exitGameButton(350, 670, 130, 50, "Exit", font),
                                      developerButton(650, 830, 130, 50, "Developer", font) {
        title = sf::Text("TIC-TAC-TOC", font, 50);
        title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 50);
    }

    void render() override {
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
                        // do something
                    }
                    if (startGameButton.isClicked(event)) {
                        uiManager.changeScreen(Screen::GAME_SELECTION_MENU);
                    }
                    if (exitGameButton.isClicked(event)) {
                        window.close();
                    }
                    if (developerButton.isClicked(event)) {
                        // do something
                    }
                }


        }
    }
};

// 設置菜單
// class SettingsMenu : public UIComponent {
// public:
//     void render() override {
//         std::cout << "Settings Menu: [Settings Options]" << std::endl;
//     }
//     // 其他設置功能
// };

// 遊戲選擇菜單
class GameSelectionMenu : public UIComponent {
public:
    GameSelectionMenu(sf::RenderWindow& window,UIManager& manager) : UIComponent(window,manager) {

    }

    void render() override {
        std::cout << "Game Selection Menu: [List of Games]" << std::endl;
    }
    // 其他遊戲選擇功能
};

// // 遊戲介面
// class GameInterface : public UIComponent {
// public:
//     void render() override {
//         std::cout << "Game Interface: [Gameplay Elements]" << std::endl;
//     }
//     // 其他遊戲功能
// };

// // 結果/得分頁面
// class ResultScreen : public UIComponent {
// public:
//     void render() override {
//         std::cout << "Result Screen: [Results and Scores]" << std::endl;
//     }
//     // 其他結果展示功能
// };

// // UI 管理器
class UIManager {
public:


private:
    sf::RenderWindow window;

    MainMenu mainMenu;
    // SettingsMenu settingsMenu;
    GameSelectionMenu gameSelectionMenu;
    // GameInterface gameInterface;
    // ResultScreen resultScreen;
    // std::vector<UIComponent*> screens;
    Screen currentScreen;
    


public:

    UIManager():window(sf::VideoMode(800, 900), "TIC-TAC-TOC"), mainMenu(window,*this), gameSelectionMenu(window,*this),currentScreen(MAIN_MENU) {
        // 初始化 UI 管理器
        // sf::RenderWindow window(sf::VideoMode(800, 900), "TIC-TAC-TOC");
        
    }
    ~UIManager() {}
    void run() {
        while (window.isOpen()) {
            renderScreen();
        }
    }
    void changeScreen(Screen screen) {
        currentScreen = screen;
    }
    void renderScreen(){
        switch (currentScreen) {
            case MAIN_MENU:
                mainMenu.render();
                break;
            // case SETTINGS_MENU:
            //     settingsMenu.render();
            //     break;
            case GAME_SELECTION_MENU:
                gameSelectionMenu.render();
                break;
            // case GAME_INTERFACE:
            //     gameInterface.render();
            //     break;
            // case RESULT_SCREEN:
            //     resultScreen.render();
            //     break;
            default:
                break;
        }
    }

    // 其他 UI 管理功能
};