#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <locale>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Text File Display Test");
    sf::Font font;

    // 載入字體
    if (!font.loadFromFile("TaipeiSansTCBeta-Regular.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }

    // 設置用於讀取文件的 locale 為系統默認 locale，通常支持 UTF-8
    // std::locale::global(std::locale(""));
    // std::locale::global(std::locale("zh_TW.UTF-8"));

    // 讀取文件，使用 wifstream 和 wstring
    std::wifstream file("illustrate.txt");
    file.imbue(std::locale());  // 為文件流設置 locale
    std::wstringstream buffer;
    buffer << file.rdbuf();
    std::wstring textContent = buffer.str();

    if (!file) {
        std::wcerr << L"Failed to open file" << std::endl;
        return 1;
    } else {
        std::wcout << L"File opened successfully" << std::endl;
    }

    // 設置文本
    sf::Text text;
    sf::String str;
    str.fromUtf32(textContent.begin(), textContent.end());
    text.setFont(font);
    // text.setString(textContent);  // sf::Text 的 setString 方法可以直接接受 wstring
    text.setString(str);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(50, 50);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(text);
        window.display();
    }

    return 0;
}
