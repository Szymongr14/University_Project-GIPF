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
    Board * board;
public:
    GameState()
        : size(0), pawns_which_trigger(0), total_white_pawns(0), total_black_pawns(0), isWhiteTurn(true), white_pawns_left(0), black_pawns_left(0), board(new Board())
    {

    }



    void loadGameState(){
        char temp;
        cin >> size >> pawns_which_trigger >> total_white_pawns >> total_black_pawns >> white_pawns_left >> black_pawns_left;
        cin>>temp;

        if(temp=='W'){
            isWhiteTurn=true;
        }
        else{
            isWhiteTurn=false;
        }
        board->setSize(size);

        switch(board->loadBoard(total_white_pawns-white_pawns_left,total_black_pawns-black_pawns_left)){
            case 0:
                cout<<"BOARD_STATE_OK"<<endl;
                break;
            case 1:
                cout<<"WRONG_BOARD_ROW_LENGTH"<<endl;
                break;
            case 2:
                cout<<"WRONG_WHITE_PAWNS_NUMBER"<<endl;
                break;
            case 3:
                cout<<"WRONG_BLACK_PAWNS_NUMBER"<<endl;
                break;
        }
    }

    void printGameState() const{
        cout << size << " " << pawns_which_trigger << " " << total_white_pawns << " " << total_black_pawns <<'\n'<< white_pawns_left << " " << black_pawns_left << " ";
        if(isWhiteTurn){
            cout<<"W"<<endl;
        }
        else{
            cout<<"B"<<endl;
        }
        board->printBoard();
//        board->printCOORDS();
    }

    Board* getBoard(){
        return board;
    }
};


#endif //GIPF_GAMESTATE_H
