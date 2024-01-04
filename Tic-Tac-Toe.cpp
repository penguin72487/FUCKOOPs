#include <windows.h>
#include "UI/UIManager.hpp"
#include <iostream>
#include <fstream>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    std::ofstream logFile("log.txt");
    std::cerr.rdbuf(logFile.rdbuf()); // 重定向 std::cerr 到 log.txt 文件
    std::cout.rdbuf(logFile.rdbuf()); // 重定向 std::cout 到 log.txt 文件
    UIManager uiManager;
    uiManager.run();
    logFile.close(); // 別忘了在程序結束時關閉文件
    return 0;
}
