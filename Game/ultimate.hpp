#ifndef ULTIMATE_H
#define ULTIMATE_H
#include "Game.hpp"
#include <vector>

class Ultimate : public Game{
public:
    void rule();
    int count_win();
    Ultimate(){};// constructor
    ~Ultimate(){};// destructor
    void init() override{};
    player gameProcess() override{
        return player::none;
    };
    player victory_Condition() override{
        return player::none;
    };
    void render() override{};
    void update() override{};
    // void draw() override;
    // void end() override;
    void click_Event() override{};
    void restart() override{};
    void settimeLimit(int) override{};
    void setinterfaceColor(std::string) override{};
    void whooseTurn() override{};

private:
    // vector<vector<basic>> tic_tac_toe(3, 3);
    
};

#endif