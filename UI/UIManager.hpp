#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "../Game//game.hpp"
#include "../Game/basic.hpp"

// UI組件的基類，提供共用的UI功能和屬性
class UIComponent {
public:
    enum class Screen {
        MAIN_MENU,
        SETTINGS_MENU,
        GAME_SELECTION_MENU,
        GAME_BASIC_INTERFACE,
        GAME_ULTIMATE_INTERFACE,
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
        if (!font.loadFromFile("../data/ttf/TaipeiSansTCBeta-Regular.ttf")) {
            std::cout << "Font load failed\n";
        }
        if (!icon.loadFromFile("../data/png/ui/icon.png")) {
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

        if (!pic.loadFromFile("../data/png/ui/OOXX.png")) {
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

// 遊戲選擇菜單類
class GameSelectionMenu : public UIComponent {
private:
    sf::Text basictext;
    sf::Text advancetext;
    Button MenuButton;
    Button BasicButton;
    Button AdvanceButton;

public:
    GameSelectionMenu(sf::RenderWindow& window) : UIComponent(window),
                                                MenuButton(57, 36, 160, 70, "MENU", font),
                                                BasicButton(333, 164, 734, 348, "", font),
                                                AdvanceButton(333, 586, 734, 347, "", font){
        basictext=sf::Text("BASIC\n3x3", font, 65);
        basictext.setFillColor(sf::Color(0, 0, 0));
        basictext.setPosition(722, 262);    
        
        advancetext=sf::Text("ADVANCE\n9x9", font, 65);
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
                        return Screen::GAME_BASIC_INTERFACE;
                    }
                    if (AdvanceButton.isClicked(event)) {
                        return Screen::GAME_ULTIMATE_INTERFACE;
                    }
                    if (MenuButton.isClicked(event)) {
                        return Screen::MAIN_MENU;
                    }
                    
                }

        }
        return Screen::MAIN_MENU;
    }
};


// 遊戲介面
class GameInterface : public UIComponent {
private:
    Button MenuButton;
    Button RestartButton;
    Button board;//棋盤
    Screen gameMode;


public:
    GameInterface(sf::RenderWindow& window) : UIComponent(window),MenuButton(57, 36, 160, 70, "MENU", font),
    RestartButton(57, 900, 160, 70, "RESTART", font),board(333, 164, 734, 734, "", font)
    {

    }
    Screen render() override {
        std::cout << "Game Interface: [Gameplay Elements]" << std::endl;
        return Screen::EXIT;
    }
    Screen render(Screen &gamemod) {
        gameMode = gamemod;
        Game* game;
        if(gameMode == Screen::GAME_BASIC_INTERFACE){
            game = new Basic();
        }
        else if(gameMode == Screen::GAME_ULTIMATE_INTERFACE){
            game = new Ultimate();
        }
        else{
            std::cout << "Game Interface: [Gameplay Elements]" << std::endl;
        }


        while (window.isOpen()) {
            window.clear(color);
            // draw title and buttons
            window.draw(MenuButton.shape);
            window.draw(MenuButton.text);
            window.draw(RestartButton.shape);
            window.draw(RestartButton.text);
            window.draw(board.shape);
            window.draw(board.text);
            window.display();
            

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                // check if buttons are clicked
                if (MenuButton.isClicked(event)) {
                    return Screen::MAIN_MENU;
                }
                if (RestartButton.isClicked(event)) {
                    return gameMode;
                }
                if(board.isClicked(event)){
                    //棋盤被點擊
                    return Screen::GAME_END_SCREEN;
                }
            }
        }

        return Screen::EXIT;
    }
    // 其他遊戲功能
};

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
                    return Screen::GAME_BASIC_INTERFACE;
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
        playerCongratulationText = sf::Text ("Congratulation Player__!!", font, 80);
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
                currentScreen=gameInterface.render();
                break;
            case UIComponent::Screen::GAME_ULTIMATE_INTERFACE:
                currentScreen=gameInterface.render();
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