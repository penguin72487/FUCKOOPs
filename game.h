#include<bits/stdc++.h>
#ifndef GAME_H
#define GAME_H

class Game {

public:
    Game();
    virtual ~Game();
    
    virtual void init() = 0;
    virtual void start() = 0;
    virtual void victory_Condition() = 0;
    virtual void render() = 0;
    virtual void update() = 0;
    virtual void click_Event() = 0;
    virtual void restart() = 0;

    virtual void settimeLimit(int) = 0;
    virtual void setinterfaceColor(std::string) = 0;

protected:
    int currentPlayer; // 0:O 1:X
    int count_P1_Victory;
    int count_P2_Victory;
    int timeLimit; // -1 for no limit time
    std::string interfaceColor; // Different color options
};

#endif
