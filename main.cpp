#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "basic.hpp"
int main() {
    // 視窗設定
    // int count_P1_Victory=0;
    // int count_P2_Victory=0;

    Game *game = new Basic();
    game->init();
    game->start();


    return 0;
}

