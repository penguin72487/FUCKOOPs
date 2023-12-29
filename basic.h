#include<bits/stdc++.h>
#include "game.hpp"
#ifndef BASIC_H
#define BASIC_H

class Basic : public Game {
    public:
        Basic();
        ~Basic();
        void init() override;
        void start() override;
        void victory_Condition() override;
        void render() override;
        void update() override;
        void click_Event() override;
        void restart() override;
        void settimeLimit(int) override;
        void setinterfaceColor(std::string) override;
        void whooseTurn() override;

        // polymorphism for different game mode
    protected:
        std::vector<std::vector<int>> board;// 0:None 1:O 2:X


};

#endif