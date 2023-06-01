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

    int error_code;
    switch(board->loadBoard(total_white_pawns-white_pawns_left,total_black_pawns-black_pawns_left)){
        case 0:
            error_code=board->checkBoard(pawns_which_trigger);
            if(!error_code){
                cout<<"BOARD_STATE_OK"<<'\n';
            } else if(error_code==1){
                cout<<"ERROR_FOUND_1_ROW_OF_LENGTH_K"<<'\n';
            }
            else{
                cout<<"ERROR_FOUND_"<<error_code<<"_ROWS_OF_LENGTH_K"<<'\n';
            }
            break;
        case 1:
            cout<<"WRONG_BOARD_ROW_LENGTH"<<'\n';
            break;
        case 2:
            cout<<"WRONG_WHITE_PAWNS_NUMBER"<<'\n';
            break;
        case 3:
            cout<<"WRONG_BLACK_PAWNS_NUMBER"<<'\n';
            break;
    }
}


void GameState::printGameState() const{
    if(board->isInvalidBoard()){
        cout<<"EMPTY_BOARD"<<'\n';
        return;
    }
    cout << size << " " << pawns_which_trigger << " " << total_white_pawns << " " << total_black_pawns <<'\n'<< white_pawns_left << " " << black_pawns_left << " ";
    if(isWhiteTurn){
        cout<<"W"<<endl;
    }
    else{
        cout<<"B"<<endl;
    }
    board->printBoard();
//    board->printCOORDS();
}

bool GameState::getIsWhiteTurn() const {
    return isWhiteTurn;
}

void GameState::setIsWhiteTurn(bool isWhiteTurn_value) {
    isWhiteTurn = isWhiteTurn_value;
}

void GameState::updateState() {
    if(isWhiteTurn){
        white_pawns_left--;
    }
    else{
        black_pawns_left--;
    }
    isWhiteTurn=!isWhiteTurn;
}



