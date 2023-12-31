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
<<<<<<< HEAD
    virtual Screen render() = 0;
    sf::Font font;
    sf::Color color = sf::Color(224, 171, 114);//79,126,146
    sf::Image icon;
    sf::RenderWindow& window;
=======
>>>>>>> 12b5ce6856bc09da6d9eefa484241d5e78ad0556

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
private:
    sf::Text colorset;
    sf::Text timeset;
    Button MenuButton;
public:
<<<<<<< HEAD
    SettingsMenu(sf::RenderWindow& window) : UIComponent(window),MenuButton(57, 36, 160, 70, "MENU", font) {
        colorset = sf::Text("SETTING COLOR", font, 50);
        colorset.setFillColor(sf::Color(255, 255, 255));
        colorset.setPosition(50, 377);    
        
        timeset = sf::Text("SETTING TIME", font, 50);
        timeset.setFillColor(sf::Color(255, 255, 255));
        timeset.setPosition(50, 622);
=======
    sf::Text colorset, timeset;
    Button menuButton;
>>>>>>> 12b5ce6856bc09da6d9eefa484241d5e78ad0556

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
<<<<<<< HEAD
        std::cout << "Settings Menu: [Settings Options]" << std::endl;
        while (window.isOpen()) {
=======
        while (window.isOpen()) {
            window.clear(color);
            // Draw text and button
            window.draw(colorset);
            window.draw(timeset);
            window.draw(menuButton.shape);
            window.display();

>>>>>>> 12b5ce6856bc09da6d9eefa484241d5e78ad0556
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

<<<<<<< HEAD
                // check if buttons are clicked
                if (MenuButton.isClicked(event)) {
                    return Screen::MAIN_MENU;
                }
            }

            window.clear(color);
            // draw title and buttons
            window.draw(colorset);
            window.draw(timeset);
            window.draw(MenuButton.shape);
            window.draw(MenuButton.text);
            window.display();


=======
                if (menuButton.isClicked(event)) {
                    return Screen::MAIN_MENU;
                }
            }
>>>>>>> 12b5ce6856bc09da6d9eefa484241d5e78ad0556
        }
        return Screen::MAIN_MENU;
    }
};

// 遊戲選擇菜單類
class GameSelectionMenu : public UIComponent {
private:
    sf::Text basictext;
    sf::Text advancetext;
    Button MenuButton;
    Button BasicButton;
    Button AdvanceButton;

public:
<<<<<<< HEAD
    GameSelectionMenu(sf::RenderWindow& window) : UIComponent(window),
                                                MenuButton(57, 36, 160, 70, "MENU", font),
                                                BasicButton(333, 164, 734, 348, "", font),
                                                AdvanceButton(333, 586, 734, 347, "", font){
        basictext=sf::Text("BASIC\n3*3", font, 65);
        basictext.setFillColor(sf::Color(0, 0, 0));
        basictext.setPosition(722, 262);    
        
        advancetext=sf::Text("ADVANCE\n9*9", font, 65);
        advancetext.setFillColor(sf::Color(0, 0, 0));
        advancetext.setPosition(722, 683);
        
    }
    Screen render() override {
        std::cout << "Game Selection Menu: [List of Games]" << std::endl;
        while(window.isOpen()){
            window.clear(color);

            
            window.draw(BasicButton.shape);
            window.draw(BasicButton.text);
            window.draw(AdvanceButton.shape);
            window.draw(AdvanceButton.text);
            window.draw(MenuButton.shape);
            window.draw(MenuButton.text);
            window.draw(basictext);
            window.draw(advancetext);

            window.display();
            sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();

                    // check if buttons are clicked
                    if (BasicButton.isClicked(event)) {
                        // do something
                    }
                    if (AdvanceButton.isClicked(event)) {
                    }
                    if (MenuButton.isClicked(event)) {
                        return Screen::MAIN_MENU;
                    }
                    
                }

        }
        return Screen::MAIN_MENU;
=======
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
>>>>>>> 12b5ce6856bc09da6d9eefa484241d5e78ad0556
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

//結束畫面
class GameEndScreen : public UIComponent {
private:
    sf::Text s1;
    Button AgainButton;
    Button ResultButton;
    Button BackButton;
public:
    GameEndScreen(sf::RenderWindow& window) : UIComponent(window),AgainButton(560, 512, 280, 85, "Again", font)
    ,ResultButton(560, 687, 280, 85, "Result", font),BackButton(560, 862, 280, 85, "Menu", font) {
        
        s1 = sf::Text("Player__ Win!!", font, 80);
        s1.setFillColor(sf::Color(255, 255, 255));
        s1.setPosition(420, 83); 
    }
    Screen render() override {
        std::cout << "Game End: [Gameplay Elements]" << std::endl;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                // check if buttons are clicked
                if (AgainButton.isClicked(event)) {
                    return Screen::GAME_INTERFACE;
                }
                if(ResultButton.isClicked(event)){
                    return Screen::RESULT_SCREEN;
                }
                if (BackButton.isClicked(event)) {
                    return Screen::MAIN_MENU;
                }
            }

            window.clear(color);
            // draw title and buttons
            window.draw(s1);
            window.draw(AgainButton.shape);
            window.draw(AgainButton.text);
            window.draw(ResultButton.shape);
            window.draw(ResultButton.text);
            window.draw(BackButton.shape);
            window.draw(BackButton.text);
            window.display();
        }
        return Screen::MAIN_MENU;
    }
    // 其他遊戲功能
};

// 結算畫面
class ResultScreen : public UIComponent {
private:
    sf::Text s1;
    sf::Text s2;
    sf::Text s3;
    sf::Text s4;
    Button BackButton;
public:
    ResultScreen(sf::RenderWindow& window) : UIComponent(window),BackButton(490, 914, 420, 85, "menu", font){
        s1 = sf::Text ("Congratuation Player__!!", font, 80);
        s1.setFillColor(sf::Color(255, 255, 255));
        s1.setPosition(234, 60); 

        s2 = sf::Text ("You have played __", font, 65);
        s2.setFillColor(sf::Color(255, 255, 255));
        s2.setPosition(110, 206);

        s3 = sf::Text ("Player1\nwin:__(__)%\nlose:__(__)%", font, 65);
        s3.setFillColor(sf::Color(255, 255, 255));
        s3.setPosition(110, 359);

        s4 = sf::Text ("Player1\nwin:__(__)%\nlose:__(__)%", font, 65);
        s4.setFillColor(sf::Color(255, 255, 255));
        s4.setPosition(110,650);
    }
    Screen render() override {
        std::cout << "Result Screen: [Results and Scores]" << std::endl;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                // check if buttons are clicked
                if (BackButton.isClicked(event)) {
                    return Screen::MAIN_MENU;
                }
            }

            window.clear(color);
            // draw title and buttons
            window.draw(s1);
            window.draw(s2);
            window.draw(s3);
            window.draw(s4);
            window.draw(BackButton.shape);
            window.draw(BackButton.text);
            window.display();
        }
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