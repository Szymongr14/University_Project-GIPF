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
    vector<vector<BoardField>>  Board_vector;
    int size=0;
public:
    Board (int size)
        :size(size), Board_vector(size*2-1, vector<BoardField>(size*2-1))
    {
    }

    Board()= default;

    void loadBoard(){
    }


};


#endif //GIPF_BOARD_H
