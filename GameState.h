//
// Created by szymo on 18.05.2023.
//

#ifndef GIPF_GAMESTATE_H
#define GIPF_GAMESTATE_H
#include <iostream>
#include <string>
#include "Board.h"

class GameState {
private:
    int size,pawns_which_trigger,total_white_pawns,total_black_pawns,white_pawns_left,black_pawns_left;
    bool isWhiteTurn;
    Board * board;
public:
    GameState()
        : size(0), pawns_which_trigger(0), total_white_pawns(0), total_black_pawns(0), isWhiteTurn(true), white_pawns_left(0), black_pawns_left(0), board(new Board()){}

    void loadGameState();
    void printGameState() const;
    void updateState();
    void doMove();

    int getSize() const;
    void setSize(int size);
    int getPawnsWhichTrigger() const;
    void setPawnsWhichTrigger(int pawnsWhichTrigger);
    int getTotalWhitePawns() const;
    void setTotalWhitePawns(int totalWhitePawns);
    int getTotalBlackPawns() const;
    void setTotalBlackPawns(int totalBlackPawns);
    int getWhitePawnsLeft() const;
    void setWhitePawnsLeft(int whitePawnsLeft);
    int getBlackPawnsLeft() const;
    void setBlackPawnsLeft(int blackPawnsLeft);
    bool isWhiteTurn1() const;
    void setIsWhiteTurn(bool isWhiteTurn);
    void genAllPosMovNum();
};

#endif //GIPF_GAMESTATE_H
