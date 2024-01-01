#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(sf::RenderWindow& window) : UIComponent(window),
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

    // load illustrate
    std::wstring illustrateCon = L"終極版圈圈叉叉\n\n遊戲介紹：\n終極版圈圈叉叉是由9個3X3的基礎版圈圈叉叉所構成，其中3X3的棋盤稱作為局部棋盤，\n而由9個3X3棋盤所組成的棋盤稱作為全局棋盤。\n玩家們輪流玩較小的井字棋盤(即3X3圈圈叉叉)，而當任一3X3的棋盤分出勝負後，將該棋盤標記為勝出玩家的符號(O or X)，\n即當玩家佔領此3X3棋盤，直到所有9個3X3的井字棋盤都分出勝負，依據玩家所佔領的井字棋盤多寡分出最終勝負。\n\n遊戲說明：\n遊戲一開始，O可以在81個空格中任選一個位置下棋，例如O選擇下在中間的局部棋盤左上，則接下來，\nX便可以在全局棋盤中左上的局部棋盤再任意選擇一個位置下棋，接著便循環同樣的模式繼續進行遊戲，直到所有局部棋盤都分出勝負。\n值得注意的是，若當玩家該下棋的區域已經分出勝負了，那麼此玩家可在全域棋盤中，任選一個剩餘的空格下棋。\n";
    illustrateText = sf::Text(illustrateCon, font, 18);
    illustrateText.setFillColor(sf::Color(255, 255, 255));
    illustrateText.setPosition(300, 400);

    // load developer
    std::wstring developerCon = L"Developer: Credits\nCreated by 企鵝, Siroku, 西瓜, sun thing, isn't from NUK ";
    developerText = sf::Text(developerCon, font, 30);
    developerText.setFillColor(sf::Color(255, 255, 255));
    developerText.setPosition(300, 400);
}

UIComponent::Screen MainMenu::render() {
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

        switch (show) {
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