//
// Created by szymo on 18.05.2023.
//

#ifndef GIPF_GAMESTATE_H
#define GIPF_GAMESTATE_H
#include <iostream>
#include <string>


class GameState {
private:
    int size,pices_which_trigger,total_white_pices,total_black_pices;
    bool isWhiteTurn;
public:
    GameState(int size, int pices_which_trigger, int total_white_pices, int total_black_pices, bool isWhiteTurn)
        :size(size),pices_which_trigger(pices_which_trigger),total_white_pices(total_white_pices),total_black_pices(total_black_pices),isWhiteTurn(isWhiteTurn)
    {

    }

    GameState()
        :size(0),pices_which_trigger(0),total_white_pices(0),total_black_pices(0),isWhiteTurn(true)
    {

    }

    void loadGameState(){
        char temp;
        std::cin>>size>>pices_which_trigger>>total_white_pices>>total_black_pices;
        std::cin>>temp;
        if(temp=='W'){
            isWhiteTurn=true;
        }
        else{
            isWhiteTurn=false;
        }
    }

    void printGameState() const{
        std::cout<<size<<" "<<pices_which_trigger<<" "<<total_white_pices<<" "<<total_black_pices<<" ";
        if(isWhiteTurn){
            std::cout<<"W"<<std::endl;
        }
        else{
            std::cout<<"B"<<std::endl;
        }
    }
};


#endif //GIPF_GAMESTATE_H
