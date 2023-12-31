#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
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

// UI組件的基類，提供共用的UI功能和屬性
class UIComponent {
public:
    enum class Screen {
        MAIN_MENU,
        SETTINGS_MENU,
        GAME_SELECTION_MENU,
        GAME_INTERFACE,
        GAME_END_SCREEN,
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


    UIComponent(sf::RenderWindow& win) : window(win), color(sf::Color(224, 171, 114)) {
        if (!font.loadFromFile("TaipeiSansTCBeta-Regular.ttf")) {
            std::cout << "Font load failed\n";
        }
        if (!icon.loadFromFile("OOXX.png")) {
            std::cout << "Texture load failed\n";
        }
    }
};

// 主菜單類
class MainMenu : public UIComponent {
private:
    enum class Show
    {
        Picture,
        ILLUSTRATE,
        DEVELOPER
    };
    sf::Text title;
    Button illustrateButton, settingButton, startGameButton, exitGameButton, developerButton;
    sf::Texture pic;
    sf::Sprite picture;
    Show show = Show::Picture;
    sf::Text illustrateText;
    sf::Text developerText;


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
        
        
        //load illustrate
        std::wstring illustrateCon= L"終極版圈圈叉叉\n\n遊戲介紹：\n終極版圈圈叉叉是由9個3X3的基礎版圈圈叉叉所構成，其中3X3的棋盤稱作為局部棋盤，\n而由9個3X3棋盤所組成的棋盤稱作為全局棋盤。\n玩家們輪流玩較小的井字棋盤(即3X3圈圈叉叉)，而當任一3X3的棋盤分出勝負後，將該棋盤標記為勝出玩家的符號(O or X)，\n即當玩家佔領此3X3棋盤，直到所有9個3X3的井字棋盤都分出勝負，依據玩家所佔領的井字棋盤多寡分出最終勝負。\n\n遊戲說明：\n遊戲一開始，O可以在81個空格中任選一個位置下棋，例如O選擇下在中間的局部棋盤左上，則接下來，\nX便可以在全局棋盤中左上的局部棋盤再任意選擇一個位置下棋，接著便循環同樣的模式繼續進行遊戲，直到所有局部棋盤都分出勝負。\n值得注意的是，若當玩家該下棋的區域已經分出勝負了，那麼此玩家可在全域棋盤中，任選一個剩餘的空格下棋。\n";
        illustrateText = sf::Text(illustrateCon, font, 18);
        illustrateText.setFillColor(sf::Color(255, 255, 255));
        illustrateText.setPosition(300, 400);
        //load developer
        std::wstring developerCon = L"Developer: Credits\nCreated by 企鵝, Siroku, 西瓜, sun thing, isn't from NUK ";
        developerText = sf::Text(developerCon, font, 30);
        developerText.setFillColor(sf::Color(255, 255, 255));
        developerText.setPosition(300, 400);
    }

    Screen render() override {
        while (window.isOpen()) {
            window.clear(color);
            // Draw title and buttons
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
            
            switch(show){
                case Show::Picture:
                    window.draw(picture);
                    break;
                case Show::ILLUSTRATE:
                    window.draw(illustrateText);
                    break;
                case Show::DEVELOPER:
                    window.draw(developerText);
                    break;
            }
            window.display();


            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                // Handle button clicks
                if (illustrateButton.isClicked(event)) {
                    if(show==Show::Picture)
                        show = Show::ILLUSTRATE;
                    else
                        show = Show::Picture;
                }
                else if (settingButton.isClicked(event)) {
                    return Screen::SETTINGS_MENU;
                }
                else if (startGameButton.isClicked(event)) {
                    return Screen::GAME_SELECTION_MENU;
                }
                else if (exitGameButton.isClicked(event)) {
                    return Screen::EXIT;
                }
                else if (developerButton.isClicked(event)) {
                    if(show==Show::Picture)
                        show = Show::DEVELOPER;
                    else
                        show = Show::Picture;
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
    SettingsMenu(sf::RenderWindow& window) : UIComponent(window),MenuButton(57, 36, 160, 70, "MENU", font) {
        colorset = sf::Text("SETTING COLOR", font, 50);
        colorset.setFillColor(sf::Color(255, 255, 255));
        colorset.setPosition(50, 377);    
        
        timeset = sf::Text("SETTING TIME", font, 50);
        timeset.setFillColor(sf::Color(255, 255, 255));
        timeset.setPosition(50, 622);
    }
    Screen render() override {
        std::cout << "Settings Menu: [Settings Options]" << std::endl;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

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


        }
        return Screen::MAIN_MENU;
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

// // 遊戲選擇菜單
// class GameSelectionMenu : public UIComponent {
// public:
//     void render() override {
//         std::cout << "Game Selection Menu: [List of Games]" << std::endl;
//     }
//     // 其他遊戲選擇功能
// };

//結束畫面
class GameEndScreen : public UIComponent {
private:
    sf::Text winMessege;
    Button AgainButton;
    Button ResultButton;
    Button BackButton;
public:
    GameEndScreen(sf::RenderWindow& window) : UIComponent(window),AgainButton(560, 512, 280, 85, "Again", font)
    ,ResultButton(560, 687, 280, 85, "Result", font),BackButton(560, 862, 280, 85, "Menu", font) {
        
        winMessege = sf::Text("Player__ Win!!", font, 80);
        winMessege.setFillColor(sf::Color(255, 255, 255));
        winMessege.setPosition(420, 83); 
    }
    Screen render() override {
        // std::cout << "Game End: [Gameplay Elements]" << std::endl;
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
            window.draw(winMessege);
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
    sf::Text playerCongratulationText;
    sf::Text gamePlayedText;
    sf::Text player1StatsText;
    sf::Text player2StatsText;
    Button BackButton;
public:
    ResultScreen(sf::RenderWindow& window) : UIComponent(window),BackButton(490, 914, 420, 85, "menu", font){
        playerCongratulationText = sf::Text ("Congratuation Player__!!", font, 80);
        playerCongratulationText.setFillColor(sf::Color(255, 255, 255));
        playerCongratulationText.setPosition(234, 60); 

        gamePlayedText = sf::Text ("You have played __", font, 65);
        gamePlayedText.setFillColor(sf::Color(255, 255, 255));
        gamePlayedText.setPosition(110, 206);

        player1StatsText = sf::Text ("Player1\nwin:__(__)%\nlose:__(__)%", font, 65);
        player1StatsText.setFillColor(sf::Color(255, 255, 255));
        player1StatsText.setPosition(110, 359);

        player2StatsText = sf::Text ("Player1\nwin:__(__)%\nlose:__(__)%", font, 65);
        player2StatsText.setFillColor(sf::Color(255, 255, 255));
        player2StatsText.setPosition(110,650);
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
            window.draw(playerCongratulationText);
            window.draw(gamePlayedText);
            window.draw(player1StatsText);
            window.draw(player2StatsText);
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
    GameEndScreen gameEndScreen;
    ResultScreen resultScreen;
    // std::vector<UIComponent*> screens;

    UIComponent::Screen currentScreen;
    


public:

    UIManager():window(sf::VideoMode(1400, 1024), "TIC-TAC-TOC"), 
        mainMenu(window), settingsMenu(window), gameSelectionMenu(window), gameInterface(window), gameEndScreen(window), resultScreen(window) {
        // 初始化 UI 管理器
        // sf::RenderWindow window(sf::VideoMode(800, 900), "TIC-TAC-TOC");
        window.setFramerateLimit(120);
        currentScreen = mainMenu.render();
    }
    ~UIManager() {}
    void addScreen(UIComponent* screen) {
        screens.push_back(screen);
    }

    void renderScreen(int index) {
        if (index >= 0 && index < screens.size()) {
            screens[index]->render();
        }
    }

    // 其他 UI 管理功能
};