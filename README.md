# Tic-Tac-Toe
oop final project
![image](https://github.com/penguin72487/Tic-Tac-Toe/assets/70788551/f2e73925-56ca-4b49-bb8b-eb4d882ed756)
![image (1)](https://github.com/penguin72487/Tic-Tac-Toe/assets/70788551/9f9cbd6a-9ff9-4cc7-bdd7-e4ee1a04a2fd)
![image (2)](https://github.com/penguin72487/Tic-Tac-Toe/assets/70788551/f389986c-d840-4238-b7d3-c99afda8b576)

# UML
![http-bw](https://raw.githubusercontent.com/penguin72487/Tic-Tac-Toe/9cacbc84bcb720e6ac0a413a78910128a6aa37d3/Tic-Tac-Toe%20(2).svg)
# PPT
https://www.canva.com/design/DAF4VraFUoo/tIMCwhm__TCUUqJHkyjXZA/edit?utm_content=DAF4VraFUoo&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton

# 開發者心得

## 企鵝
我來補充一點技術細節，我在game的多型使用了智慧指標，因為如果要維持可讀性，在哪裡new一個指標就要在哪裡delete，但是我們會把game指標傳入endscreem，直接使用game的render顯示最終結果，使用智慧指標就不用管了，哈哈哈哈。

## 劉沛辰
這次做專題，從發想主題，討論了很久該如何實現封裝繼承多型，確定主題，畫usercase，站在使用者角度設計按鍵，設計UI、顏色、區塊，然後再畫uml，
設計封裝多形繼承，再到實現uml，程式碼。

過程遇到許多困難，SFML的環境建構，git共同協作，github的branch推動，再來到SFML實作UI，多形繼承UI Component，PlayerO X實作，check的繼承，
把上課學到的理論變成實作才讓我更熟悉OOP

## 孫健淳
在這次專題中，除了懂得該如何應用物件導向思維的方式（利用封裝，類別關係的方式去思考如何組織程式碼）去設計程式專案外，也從其他隊友中學習到之前從未踏過的領域，以下是我這次從專題所學到的其他領域。

（一）	github整合程式碼

首先是為了整合大家的程式，避免大家在資訊上的不對稱，造成程式碼重複修改，不同步的情形，因此我們使用git來解決這個問題。這也是我第一次對git有了具體的概念。這將成為我日後撰寫程式的一大利器。

（二）	SMLF與chatgpt的應用

SMFL是專門提供圖形化介面的函示庫，這是大家第一次接觸到SMFL的函示庫，所以對裡面擁有的function並不熟悉。但在與chatgpt的配合下，算是邊用邊學，大致知道裡面的函示庫該如何使用。這也讓我意識到之後AI對於程式設計的重要性，該如何有效的對AI下指令是我必須學會的課題。

## 黃羿禎
在這次的專題中，我從同儕之間學到了更多關於程式的知識，像是如何使用git等，也第一次從頭與別人協同合作撰寫程式碼，除了更加熟悉OOP三大特性外，也學會了該如何與他人合作、溝通。
在過程中我覺得最為困難的點是學會如何以物件導向程式語言的思維去撰寫程式碼，以往都是撰寫程序性程式語言為主，所以一開始要開始理解、撰寫程式碼非常困難，在這部分我非常感謝並佩服我們組長--企鵝，程式碼幾乎都是由他所完成的，透過觀摩他的程式碼才讓我更加對物件導向語言有更加清晰的了解，漸漸熟悉撰寫物件導向程式語言。

## 劉柏均(Siroku)

這次的期末專題，我們選擇了井字遊戲，但因為不是只有簡單的井字遊戲，我們還加入了一些特殊的規則，我們找到了SFML來開發我們的期末專題，我主要是做UI設計，除了物件導向以外，我還學到了如何讓整個UI看起來比較順眼，還有學到到了如何使用繪圖軟體，在未來跨領域結合受益良多。

---


# 程式碼高光時刻

在UImanerger，存了很多UI介面，要怎麼通知換畫面呢?
```cpp
class UIComponent {
public:
    enum class Screen {//定義畫面的所有狀態
        MAIN_MENU,
        SETTINGS_MENU,
        GAME_SELECTION_MENU,
        GAME_BASIC_INTERFACE,
        GAME_ULTIMATE_INTERFACE,
        GAME_END_SCREEN,
        RESULT_SCREEN,
        EXIT
    };
    virtual Screen render() = 0;//這裡我讓所有渲染完的時候要回傳下一幀要渲染哪個螢幕狀態。
    //.....
};
```
在UIManager currentScreen 存現在的螢幕狀態。  
而進階版跟基本版都用同一個GameInterface，這樣才能凸顯動態連結的多型多好玩。  
他們的render要傳入currentScreen，確保要選染哪種遊戲，而且回傳整個遊戲的動態指標，讓GameEndScreen渲染遊戲最後的結果。  

```cpp
// // UI 管理器
class UIManager {
public:
    //....
    UIComponent::Screen currentScreen;
    std::shared_ptr<Game> currentGame;
    //...
    void renderScreen(){
    std::tuple<UIComponent::Screen, std::shared_ptr<Game>> renderResult;
    switch (currentScreen) {
        case UIComponent::Screen::MAIN_MENU:
            currentScreen = mainMenu.render();//回傳時改現在的畫面就可以改下一幀選染啥囉
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
};
```
進階版以及基本版都用一樣的渲染框架，很好的表示多型的玩法。
```cpp
class GameInterface : public UIComponent {
//...
    Screen render() override {
        // Render the game interface including buttons and game elements
        std::cout << "Game Invidual Interface: [Gameplay Elements]" << std::endl;//用原本的方式進來是不合法的喔
        return Screen::EXIT;
    }
    std::tuple<Screen,std::shared_ptr<Game>> render(Screen &GameMod) {
        gameMode = GameMod;

        if(gameMode == Screen::GAME_BASIC_INTERFACE){
            std::cout << "Game Basic new [Gameplay Elements]" << std::endl;
            game = std::make_shared<Basic>(window, GamePosition);  // 使用智能指標，動態連結game
        }
        else if(gameMode == Screen::GAME_ULTIMATE_INTERFACE){
            //std::cout << "Game Ultimate new [Gameplay Elements]" << std::endl;
                game = std::make_shared<Ultimate>(window, GamePosition);
                // return {Screen::GAME_SELECTION_MENU,nullptr};
            }
        else{
            std::cout << "Game Ultimate Interface: [Gameplay Elements]" << std::endl;
        }
//...
        backgroundSprite.setTexture(backgroundTexture);
                // 更新游戏状态
                // 渲染游戏和界面
                window.clear(color);
                window.draw(backgroundSprite);
                game->render(); // 渲染游戏
                window.draw(MenuButton.shape);
                window.draw(MenuButton.text);
                window.draw(RestartButton.shape);
                window.draw(RestartButton.text); // 渲染界面元素，例如菜单和重新开始按钮
                window.display(); // 更新窗口显示

                // 检查游戏是否结束
                Game::player win_Player=game->check_Win();
                if(win_Player != Game::player::none){
                    return {Screen::GAME_END_SCREEN,game};
                }
            }
        return {Screen::EXIT,nullptr};
    }
    // 其他遊戲功能
```
Basic4U唸法是 Basic for Ultimate，繼承basic增加回傳被按九宮格的哪個位子，使用tuple傳回Ultimate，以實現在大棋盤的對應位子下OX。
還有要增加現在換誰，現在換誰是basic本來就會控制的，會影響渲染的OX順序，但是主導權要在Ultimate，所以有一個setcurrentplayer

```cpp
class Basic4U : public Basic{
    std::tuple<int,int> click_Event(sf::Event &event, player p) {

            if (event.type == sf::Event::Closed)
                window.close();
            setCurrentPlayer(p);
            // if(check_Win() != player::none){
            //                 //     return {-1,-1};
            // }
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    if (buttons[i][j].isClicked(window,event)) {
                        if (board[i][j] == player::none) {
                            board[i][j] = currentPlayer;
                                                        currentPlayer = currentPlayer == player::O ? player::X :player::O;
                            return {i,j};
                        }
                    }
                }
            }
        return {-2,-2};
    }
    void setCurrentPlayer(player p){
        currentPlayer = p;
    }
};
```
以上大部分的代碼細節就分享完成了

# quick start
[git](https://git-scm.com/)  
[VSCODEE](https://code.visualstudio.com/)  
[MSYS2](https://www.msys2.org/)


打開MSYS2的終端機
```shell
pacman -Syu
pacman -Sy
pacman -S mingw-w64-x86_64-toolchain
pacman -S mingw-w64-x86_64-sfml
pacman -Sy
pacman -Syu
```

加入系統變數  
對windows右鍵
![Alt text](image.png)
選擇系統(Y)
![Alt text](image-1.png)
右方藍字進階系統->環境變數(N)->使用者的使用者變數->往下拉一點，雙擊Path->新增(N)->輸入C:\msys64\mingw64\bin->確定->確定->套用->確定

重開機
看看有沒有成功安裝

```shell
gcc --version
g++ --version
gdb --version
```

VScode插件
code running
c++

設置 .vscode 資料夾

.vscode.sample把.sample去掉
然後去code running的擴充設定，進去工作區點setting.json，使用工作區的.json而不是全域的



參考
https://blog.roy4801.tw/2020/07/14/SFML/sfml_intro/  


