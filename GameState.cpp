//
// Created by szymo on 18.05.2023.
//

#include "GameState.h"

void GameState::loadGameState(){
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
            cout<<"BOARD_STATE_OK"<<'\n'<<'\n';
            break;
        case 1:
            cout<<"WRONG_BOARD_ROW_LENGTH"<<'\n'<<'\n';
            break;
        case 2:
            cout<<"WRONG_WHITE_PAWNS_NUMBER"<<'\n'<<'\n';
            break;
        case 3:
            cout<<"WRONG_BLACK_PAWNS_NUMBER"<<'\n'<<'\n';
            break;
    }
}


void GameState::printGameState() const{
    cout << size << " " << pawns_which_trigger << " " << total_white_pawns << " " << total_black_pawns <<'\n'<< white_pawns_left << " " << black_pawns_left << " ";
    if(isWhiteTurn){
        cout<<"W"<<endl;
    }
    else{
        cout<<"B"<<endl;
    }
    board->printBoard();
    board->printCOORDS();
}



