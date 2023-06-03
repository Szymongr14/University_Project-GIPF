//
// Created by szymo on 16.05.2023.
//

#ifndef GIPF_BOARD_H
#define GIPF_BOARD_H
#include <vector>
#include <string>
#include <iostream>
#include <limits>
#include <unordered_map>
class GameState;
using std::cout, std::endl, std::cin, std::vector, std::string;

struct HexCoords{
    char x=0;
    int y=0;
};

struct BoardField{
    char sign;
    bool isEmpty,used,border = false;
    HexCoords hex_coords;
};

struct Pawn {
    char sign;
    int x,y;
    bool to_remove=false;
};


class Board {
private:
    vector<vector<BoardField>>  Board_vector;
    std::unordered_map<string, std::pair<int, int>> coords_to_indexes;
    GameState* gameState;
    int size=0;
    bool invalid_board= true;

    void assignCoords(int q,int r, int row_size);

public:
    Board()= default;
    Board (int size,GameState* state):size(size), Board_vector(size*2-1, vector<BoardField>(size*2-1)),gameState(state){}

    int loadBoard(int expected_white_pawns_left,int expected_black_pawns_left);
    void setSize(int size_value);
    void printBoard();
    std::pair<int, int> coordsToIndexes(char x, int y) const;
    void printCOORDS();
    bool isInvalidBoard() const;
    bool isCoordsValid(char x, int y) const;
    bool isBorder(char x, int y) const;
    bool isDirectionValid(char x, int y, char x1, int y1) const;
    vector <std::pair<int,int>> getRow(char x, int y, char x1, int y1) const;
    vector <std::pair<int,int>> getRow_by_passing_indexes(int x, int y, int x1, int y1) const;
    bool isRowFull(const vector <std::pair<int,int>>& row) const;
    void movePawns(vector <std::pair<int,int>> row,bool isWhiteTurn);
    int checkBoard(int k,bool isWhiteTurn,bool delete_pawns = false);
    int checkSWandNE(int k,bool isWhiteTurn, bool delete_pawns = false);
    int checkSEandNW(int k,bool isWhiteTurn,bool delete_pawns = false);
    int checkHorizontalLines(int k,bool isWhiteTurn, bool delete_pawns = false);
    void deletePawns(int k,const vector <Pawn>& pawns,bool isWhiteTurn,int which_color);
    void setGameState(GameState* state) {gameState = state;}
    vector<vector<char>> returnCopyOfBoardAfterMove(vector<std::pair<int, int>> row);
    int genAllPosMovNums();

};
#endif //GIPF_BOARD_H
