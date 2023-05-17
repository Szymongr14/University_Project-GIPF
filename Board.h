//
// Created by szymo on 16.05.2023.
//

#ifndef GIPF_BOARD_H
#define GIPF_BOARD_H
#include <vector>
#include <string>
using namespace std;

class BoardField{
private:
    char sign;
    bool isEmpty;
};


class Board {
private:
    vector<vector<Board>>  BoardField;
    int size;

};


#endif //GIPF_BOARD_H
