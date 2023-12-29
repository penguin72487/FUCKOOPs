#include <iostream>
#include <string>
#include <vector>

// 基礎 UI 元件類別
class UIComponent {
public:
    virtual void render() = 0;
    // 其他通用 UI 功能
};

// 主菜單
class MainMenu : public UIComponent {
public:
    void render() override {
        std::cout << "Main Menu: Start Game, Settings, Game Instructions" << std::endl;
    }
    // 其他主菜單功能
};

// 設置菜單
class SettingsMenu : public UIComponent {
public:
    void render() override {
        std::cout << "Settings Menu: [Settings Options]" << std::endl;
    }
    // 其他設置功能
};

// 遊戲選擇菜單
class GameSelectionMenu : public UIComponent {
public:
    void render() override {
        std::cout << "Game Selection Menu: [List of Games]" << std::endl;
    }
    // 其他遊戲選擇功能
};

// 遊戲介面
class GameInterface : public UIComponent {
public:
    void render() override {
        std::cout << "Game Interface: [Gameplay Elements]" << std::endl;
    }
    // 其他遊戲功能
};

// 結果/得分頁面
class ResultScreen : public UIComponent {
public:
    void render() override {
        std::cout << "Result Screen: [Results and Scores]" << std::endl;
    }
    // 其他結果展示功能
};

// UI 管理器
class UIManager {
private:
    std::vector<UIComponent*> screens;

public:
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

int main() {
    UIManager uiManager;
    MainMenu mainMenu;
    SettingsMenu settingsMenu;
    GameSelectionMenu gameSelectionMenu;
    GameInterface gameInterface;
    ResultScreen resultScreen;

    // 添加各種 UI 畫面
    uiManager.addScreen(&mainMenu);
    uiManager.addScreen(&settingsMenu);
    uiManager.addScreen(&gameSelectionMenu);
    uiManager.addScreen(&gameInterface);
    uiManager.addScreen(&resultScreen);

    // 渲染主菜單
    uiManager.renderScreen(0);

    // 根據用戶輸入或遊戲邏輯，切換並渲染不同的 UI 畫面
    // ...

    return 0;
}