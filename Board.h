//
// Created by szymo on 16.05.2023.
//

#ifndef GIPF_BOARD_H
#define GIPF_BOARD_H
#include <vector>
#include <string>
#include <iostream>
#include <limits>

using std::cout, std::endl, std::cin, std::vector, std::string;

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

    int loadBoard(int expected_white_pawns_left,int expected_black_pawns_left) {
        string line;
        vector<char> row_vector;
        int message_to_user = 0;
        //message to user:
        // 0-BOARD_STATE_OK
        // 1-WRONG_BOARD_ROW_LENGTH
        // 2-WRONG_WHITE_PAWNS_NUMBER
        // 3-WRONG_BLACK_PAWNS_NUMBER
        int fixed_size = size-1;
        int board_size = 2 * size - 1;
        int expected_row_size = 3 * size * (size - 1) + 1;
        int actual_white_pawns_left=0,actual_black_pawns_left=0;

        for (int i = 0; i < board_size; i++) {
            getline(cin >> std::ws, line);
            for (char j : line) {
                if(j!=' '){
                    if(j=='W'){
                        actual_white_pawns_left++;
                    }
                    else if(j=='B'){
                        actual_black_pawns_left++;
                    }
                    row_vector.push_back(j);
                }
            }
            line.clear();
        }


        if(actual_white_pawns_left!=expected_white_pawns_left){
            message_to_user=2;
        }
        if(actual_black_pawns_left!=expected_black_pawns_left){
            message_to_user=3;
        }
        if(row_vector.size()!=expected_row_size){
            message_to_user=1;
        }

        if(message_to_user==0){
            for (int r = 0; r < board_size; r++) {
                int row_size = (2 * fixed_size + 1) - abs(fixed_size - r);

                for (int q = 0; q < row_size; q++) {
                    Board_vector[r][q].sign = row_vector.back();
                    row_vector.pop_back();
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
        return message_to_user;
    }

    void setSize(int size_value) {
        this->size = size_value;
        int board_size = 2 * size - 1;
        Board_vector.resize(board_size, vector<BoardField>(board_size));
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
            cout << '\n';
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
            cout << '\n';
        }
    }
};


#endif //GIPF_BOARD_H
