#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "basic.hpp"
int main() {
    // 視窗設定
    int count_P1_Victory=0;
    int count_P2_Victory=0;

    Game *game = new Basic();
    game->init();
    int result = game->gameProcess();
    if(result==1){
        count_P1_Victory++;
    }
    else if(result==2){
        count_P2_Victory++;
    }
    std::cout<<"P1 win "<<count_P1_Victory<<" times"<<std::endl;
    std::cout<<"P2 win "<<count_P2_Victory<<" times"<<std::endl;
    delete game;
    
    return 0;
}

