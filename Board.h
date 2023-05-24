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

using std::cout, std::endl, std::cin, std::vector, std::string;

struct HexCoords{
    char x=0;
    int y=0;
};

class BoardField{
public:
    char sign;
    bool isEmpty,used = false;
    HexCoords hex_coords;
};


class Board {
private:
    vector<vector<BoardField>>  Board_vector;
    std::unordered_map<string, std::pair<int, int>> coords_to_indexes;
    int size=0;

    void assignCoords(int q,int r, int row_size);

public:
    Board (int size):size(size), Board_vector(size*2-1, vector<BoardField>(size*2-1)){}
    Board()= default;

    int loadBoard(int expected_white_pawns_left,int expected_black_pawns_left);
    void setSize(int size_value);
    void printBoard();
    std::pair<int, int> coordsToIndexes(char x, int y) const;
    void printBoardAsCoords() const;
    void printCOORDS();

    bool isCoordsValid(char x, int y) const;
};


#endif //GIPF_BOARD_H
