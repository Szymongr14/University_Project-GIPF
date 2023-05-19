//
// Created by szymo on 16.05.2023.
//

#ifndef GIPF_BOARD_H
#define GIPF_BOARD_H
#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct HexCoords{
    char x;
    int y;
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
    int size=0;
public:
    Board (int size)
        :size(size), Board_vector(size*2-1, vector<BoardField>(size*2-1))
    {
    }

    Board()= default;

    void loadBoard() {
        int fixed_size = size-1;
        int board_size = 2 * size - 1;

        for (int r = 0; r < board_size; r++) {
            int row_size = (2 * fixed_size + 1) - abs(fixed_size - r);

            for (int q = 0; q < row_size; q++) {
                cin >> Board_vector[r][q].sign;
                Board_vector[r][q].used = true;

                //handle coords
                if(r<=size){
                    Board_vector[r][q].hex_coords.x = 'a' + q;
                    Board_vector[r][q].hex_coords.y = size - r +q;
                }
                else if(r>size){
                    Board_vector[r][q].hex_coords.x = 'a' + q;
                    Board_vector[r][q].hex_coords.y = size - r;
                }

                if (Board_vector[r][q].sign == '_') {
                    Board_vector[r][q].isEmpty = true;
                } else if (Board_vector[r][q].sign == 'W' || Board_vector[r][q].sign == 'B') {
                    Board_vector[r][q].isEmpty = false;
                }
            }
        }
    }


    void printBoard() const {
        int fixed_size = size-1;
        int board_size = 2 * size - 1;
        bool wasSpacing;

        for (int r = 0; r < board_size; r++) {
            int row_size = (2 * fixed_size + 1) - abs(fixed_size - r);
            wasSpacing = false;
            for (int q = 0; q < row_size; q++) {

                if(!wasSpacing){
                    for(int t=0;t<board_size-row_size;t++){
                        cout<<" ";
                    }
                    wasSpacing = true;
                }
                cout << Board_vector[r][q].sign << " ";
            }
            cout << endl;
        }
    }

    void printBoardWithCoords() const {
        int fixed_size = size-1;
        int board_size = 2 * size - 1;
        bool wasSpacing;

        for (int r = 0; r < board_size; r++) {
            int row_size = (2 * fixed_size + 1) - abs(fixed_size - r);
            wasSpacing = false;
            for (int q = 0; q < row_size; q++) {

                if(!wasSpacing){
                    for(int t=0;t<board_size-row_size;t++){
                        cout<<" ";
                    }
                    wasSpacing = true;
                }
                cout << Board_vector[r][q].hex_coords.x << Board_vector[r][q].hex_coords.y << " ";
            }
            cout << endl;
        }
    }
};


#endif //GIPF_BOARD_H
