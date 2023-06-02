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
    board->setGameState(this);

    int error_code;
    switch(board->loadBoard(total_white_pawns-white_pawns_left,total_black_pawns-black_pawns_left)){
        case 0:
            error_code=board->checkBoard(pawns_which_trigger, isWhiteTurn);
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

void GameState::updateState() {
    if(isWhiteTurn){
        white_pawns_left--;
    }
    else{
        black_pawns_left--;
    }
    isWhiteTurn=!isWhiteTurn;
}

void GameState::doMove() {
    string coords;
    cin >> coords;
    char x = coords[0];
    int y = coords[1] - '0';
    char x1 = coords[3];
    int y1 = coords[4] - '0';
    if(board->isCoordsValid(x,y) && board->isCoordsValid(x1,y1)){
        if(!board->isBorder(x,y)){
            cout<<"BAD_MOVE_"<<x<<y<<"_IS_WRONG_STARTING_FIELD"<<endl<<endl;
        }
        else if(board->isBorder(x1,y1)){
            cout<<"BAD_MOVE_"<<x1<<y1<<"_IS_WRONG_DESTINATION_FIELD"<<endl<<endl;
        }
        else if(!board->isDirectionValid(x,y,x1,y1)) {
            cout<<"UNKNOWN_MOVE_DIRECTION"<<endl<<endl;
        }
        else{
            vector <std::pair<int,int>> row = board->getRow(x,y,x1,y1);
            if(board->isRowFull(row)){
                cout<<"BAD_MOVE_ROW_IS_FULL"<<endl<<endl;
            }
            else {
                board->movePawns(row, isWhiteTurn);
                updateState();
                board->checkBoard(pawns_which_trigger,isWhiteTurn,true);
                cout << "MOVE_COMMITTED" << endl << endl;
            }
        }
    }
    else{
        if(!board->isCoordsValid(x,y)){
            cout<<"BAD_MOVE_"<<x<<y<<"_IS_WRONG_INDEX"<<endl<<endl;
        }
        else{
            cout<<"BAD_MOVE_"<<x1<<y1<<"_IS_WRONG_INDEX"<<endl<<endl;
        }
    }
}

int GameState::getSize() const {
    return size;
}

void GameState::setSize(int size) {
    GameState::size = size;
}

int GameState::getPawnsWhichTrigger() const {
    return pawns_which_trigger;
}

void GameState::setPawnsWhichTrigger(int pawnsWhichTrigger) {
    pawns_which_trigger = pawnsWhichTrigger;
}

int GameState::getTotalWhitePawns() const {
    return total_white_pawns;
}

void GameState::setTotalWhitePawns(int totalWhitePawns) {
    total_white_pawns = totalWhitePawns;
}

int GameState::getTotalBlackPawns() const {
    return total_black_pawns;
}

void GameState::setTotalBlackPawns(int totalBlackPawns) {
    total_black_pawns = totalBlackPawns;
}

int GameState::getWhitePawnsLeft() const {
    return white_pawns_left;
}

void GameState::setWhitePawnsLeft(int whitePawnsLeft) {
    white_pawns_left = whitePawnsLeft;
}

int GameState::getBlackPawnsLeft() const {
    return black_pawns_left;
}

void GameState::setBlackPawnsLeft(int blackPawnsLeft) {
    black_pawns_left = blackPawnsLeft;
}

bool GameState::isWhiteTurn1() const {
    return isWhiteTurn;
}

void GameState::setIsWhiteTurn(bool isWhiteTurn) {
    GameState::isWhiteTurn = isWhiteTurn;
}



