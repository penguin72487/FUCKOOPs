#include "Basic.hpp"
#ifndef BASIC4U_HPP
#define BASIC4U_HPP

class Basic4U : public Basic{
    using player = Game::player;
    public:
    Basic4U(sf::RenderWindow& win,std::tuple<int,int,int,int> g_P ): Basic(win, g_P){

    }
    ~Basic4U() override{}
    void click_Event(sf::Event &event) override{
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if (buttons[i][j].isClicked(window,event)) {
                    if (board[i][j] == player::none) {
                        board[i][j] = currentPlayer;
                        // std::cout << "board"<<i<<" "<<j<<"isClicked\n";
                        currentPlayer = currentPlayer == player::O ? player::X :player::O;
                        return;
                    }
                }
            }
        }
    }
    std::tuple<int,int> click_Event(sf::Event &event, player p) {

            if (event.type == sf::Event::Closed)
                window.close();
            setCurrentPlayer(p);
            // if(check_Win() != player::none){
            //     // std::cout << "also invalid board\n";
            //     return {-1,-1};
            // }
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    if (buttons[i][j].isClicked(window,event)) {
                        if (board[i][j] == player::none) {
                            board[i][j] = currentPlayer;
                            // std::cout << "board"<<i<<" "<<j<<"isClicked\n";
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

#endif //BASIC4U_HPP