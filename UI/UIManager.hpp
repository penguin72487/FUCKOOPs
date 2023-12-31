#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Button.hpp"

// UI組件的基類，提供共用的UI功能和屬性
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
    virtual ~UIComponent() {}

protected:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Color color;
    sf::Image icon;


    UIComponent(sf::RenderWindow& win) : window(win), color(sf::Color(79, 126, 146)) {
        if (!font.loadFromFile("TaipeiSansTCBeta-Regular.ttf")) {
            std::cout << "Font load failed\n";
        }
        if (!icon.loadFromFile("OOXX.png")) {
            std::cout << "Icon load failed\n";
        }
    }
};

// 主菜單類
class MainMenu : public UIComponent {
private:
    sf::Text title;
    Button illustrateButton, settingButton, startGameButton, exitGameButton, developerButton;
    sf::Texture pic;
    sf::Sprite picture;

public:
    MainMenu(sf::RenderWindow& window) : UIComponent(window), 
        illustrateButton(57, 650, 200, 70, "ILLUSTRATE", font),
        settingButton(57, 500, 200, 70, "SETTING", font),
        startGameButton(57, 350, 200, 70, "START GAME", font),
        exitGameButton(57, 800, 200, 70, "EXIT", font),
        developerButton(1150, 900, 200, 70, "DEVELOPER", font) {

        title = sf::Text("TIC-TAC-TOC", font, 170);
        title.setFillColor(sf::Color::White);
        title.setPosition(57, 57);

        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        if (!pic.loadFromFile("OOXX.png")) {
            std::cout << "Texture load failed\n";
        }
        picture.setTexture(pic);
        picture.setScale(1.2, 1.2);
        picture.setPosition(540, 314);

        color = sf::Color(224, 171, 114);
    }

    Screen render() override {
        while (window.isOpen()) {
            window.clear(color);
            // Draw title and buttons
            window.draw(title);
            window.draw(picture);
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

                // Handle button clicks
                if (illustrateButton.isClicked(event)) {
                    // Implement action
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
                    // Implement action
                }
            }
        }
        return Screen::EXIT;
    }
};

// 設置菜單類
class SettingsMenu : public UIComponent {
public:
    sf::Text colorset, timeset;
    Button menuButton;

    SettingsMenu(sf::RenderWindow& window) : UIComponent(window),
        menuButton(57, 36, 160, 70, "MENU", font) {

        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        colorset = sf::Text("SETTING COLOR", font, 50);
        colorset.setFillColor(sf::Color::White);
        colorset.setPosition(50, 377);    

        timeset = sf::Text("SETTING TIME", font, 50);
        timeset.setFillColor(sf::Color::White);
        timeset.setPosition(50, 622);

        color = sf::Color(224, 171, 114);
    }

    Screen render() override {
        while (window.isOpen()) {
            window.clear(color);
            // Draw text and button
            window.draw(colorset);
            window.draw(timeset);
            window.draw(menuButton.shape);
            window.display();

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (menuButton.isClicked(event)) {
                    return Screen::MAIN_MENU;
                }
            }
        }
        return Screen::MAIN_MENU;
    }
};

// 遊戲選擇菜單類
class GameSelectionMenu : public UIComponent {
public:
    Button menuButton, basicButton, advanceButton;
    sf::Text basicText, advanceText;

    GameSelectionMenu(sf::RenderWindow& window) : UIComponent(window),
        menuButton(57, 36, 160, 70, "MENU", font),
        basicButton(333, 164, 734, 348, "", font),
        advanceButton(333, 586, 734, 347, "", font) {

        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        basicText = sf::Text("BASIC\n3*3", font, 65);
        basicText.setFillColor(sf::Color::Black);
        basicText.setPosition(722, 262);

        advanceText = sf::Text("ADVANCE\n9*9", font, 65);
        advanceText.setFillColor(sf::Color::Black);
        advanceText.setPosition(722, 683);

        color = sf::Color(224, 171, 114);
    }

    Screen render() override {
        while (window.isOpen()) {
            window.clear(color);
            // Draw buttons and text
            window.draw(menuButton.shape);
            window.draw(menuButton.text);
            window.draw(basicButton.shape);
            window.draw(advanceButton.shape);
            window.draw(basicText);
            window.draw(advanceText);
            window.display();

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (menuButton.isClicked(event)) {
                    return Screen::MAIN_MENU;
                }
                if (basicButton.isClicked(event)) {
                    return Screen::GAME_INTERFACE;
                }
                if (advanceButton.isClicked(event)) {
                    return Screen::GAME_INTERFACE;
                }
            }
        }
        return Screen::GAME_INTERFACE;
    }
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

    UIManager():window(sf::VideoMode(1400, 1024), "TIC-TAC-TOC"), mainMenu(window), settingsMenu(window),gameSelectionMenu(window), gameInterface(window), resultScreen(window) {
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