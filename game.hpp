#include<bits/stdc++.h>
# ifndef GAME_HPP
# define GAME_HPP

class Game{

public:
    Game();
    ~Game();
    virtual void init() = 0;
    virtual void start() = 0;
    virtual void victory_Condition() = 0;
    virtual void render() = 0;
    virtual void update() = 0;
    // virtual void draw() = 0;
    // virtual void end() = 0;
    virtual void click_Event() = 0;
    virtual void restart() = 0;
    virtual void settimeLimit(int) = 0;
    virtual void setinterfaceColor(std::string) = 0;
    virtual void whooseTurn() = 0;

protected:
    int currentPlayer;// 0:O 1:X
    int timeLimit;// -1 for no limit time
    std::string interfaceColor;// "black" or "white" or "blue" or "red" or "green" or "yellow" or "purple" or "cyan" etc.
    time_t get_Timestamp(){
        return time(0);
    }
};

# endif