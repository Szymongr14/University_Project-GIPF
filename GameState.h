//
// Created by szymo on 18.05.2023.
//

#ifndef GIPF_GAMESTATE_H
#define GIPF_GAMESTATE_H
#include <iostream>
#include <string>
#include <memory>
#include "Board.h"

class GameState {
private:
    int size,pawns_which_trigger,total_white_pawns,total_black_pawns,white_pawns_left,black_pawns_left;
    bool isWhiteTurn;
    unique_ptr<Board> board;
public:
    GameState(int size, int pices_which_trigger, int total_white_pices, int total_black_pices, bool isWhiteTurn, int current_white_pices, int current_black_pices)
        : size(size), pawns_which_trigger(pices_which_trigger), total_white_pawns(total_white_pices), total_black_pawns(total_black_pices), isWhiteTurn(isWhiteTurn), white_pawns_left(current_white_pices), black_pawns_left(current_black_pices)
    {

    }

    GameState()
        : size(0), pawns_which_trigger(0), total_white_pawns(0), total_black_pawns(0), isWhiteTurn(true), white_pawns_left(0), black_pawns_left(0), board(std::make_unique<Board>())
    {

    }

    void loadGameState(){
        char temp;
        std::cin >> size >> pawns_which_trigger >> total_white_pawns >> total_black_pawns >> white_pawns_left >> black_pawns_left;
        std::cin>>temp;
        if(temp=='W'){
            isWhiteTurn=true;
        }
        else{
            isWhiteTurn=false;
        }
        board->setSize(size);

        if(!board->loadBoard()){
            cout<<"WRONG_BOARD_ROW_LENGTH"<<endl;
        } else{
            cout<<"OK"<<endl;
        }



    }

    void printGameState() const{
        std::cout << size << " " << pawns_which_trigger << " " << total_white_pawns << " " << total_black_pawns << " " << white_pawns_left << " " << black_pawns_left << " ";
        if(isWhiteTurn){
            std::cout<<"W"<<std::endl;
        }
        else{
            std::cout<<"B"<<std::endl;
        }
        cout<<endl<<endl<<endl;
        board->printBoard();
    }

    int getSize() const {
        return size;
    }
};


#endif //GIPF_GAMESTATE_H
