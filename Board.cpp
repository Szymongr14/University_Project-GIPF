//
// Created by szymo on 16.05.2023.
//

#include "Board.h"


void Board::assignCoords(int q,int r, int row_size){
    Board_vector[r][q].used = true;

    if(r<size+1){

        Board_vector[r][q].hex_coords.x = 'a' + q;
        if(q>=row_size-r){
            Board_vector[r][q].hex_coords.y = Board_vector[r][q-1].hex_coords.y;
        } else{
            Board_vector[r][q].hex_coords.y = size+1 - r +q;
        }
    }
    else if(r>=size+1){
        Board_vector[r][q].hex_coords.x = Board_vector[r-1][q+1].hex_coords.x;
        Board_vector[r][q].hex_coords.y = Board_vector[r-1][q+1].hex_coords.y-1;
    }
    coords_to_indexes[std::to_string(Board_vector[r][q].hex_coords.x) + std::to_string(Board_vector[r][q].hex_coords.y)] = std::make_pair(r,q);
}


int Board::loadBoard(int expected_white_pawns_left,int expected_black_pawns_left) {
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
        coords_to_indexes.clear();
        int size_with_borders = (size+1)*2-1;
        for (int r = 0; r < size_with_borders; r++) {
            int row_size = (2 * size + 1) - abs(size - r);

            for (int q = 0; q < row_size; q++) {
                if(q==0 || q==row_size-1 || r==0 || r==size_with_borders-1){
                    Board_vector[r][q].sign = '+';
                    Board_vector[r][q].border = true;
                    assignCoords(q,r,row_size);
                    continue;
                }
                Board_vector[r][q].sign = row_vector.front();
                row_vector.erase(row_vector.begin());

                assignCoords(q,r,row_size);


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


void Board::setSize(int size_value) {
    this->size = size_value;
    int board_size = 2 * size - 1;
    Board_vector.clear();
    Board_vector.resize(board_size+2, vector<BoardField>(board_size+2));
}


std::pair<int, int> Board::coordsToIndexes(char x, int y) const {
    try {
        return coords_to_indexes.at(std::to_string(x) + std::to_string(y));
    }
    catch (const std::out_of_range& oor) {
        return std::make_pair(-1,-1);
    }
}

void Board::printBoard(){
    int board_size = 2 * size - 1;
    bool wasSpacing;
    int size_with_borders = (size+1)*2-1;


    for (int r = 0; r < size_with_borders; r++) {
        int row_size = (2 * size + 1) - abs(size - r);
        wasSpacing = false;
        for (int q = 0; q < row_size; q++) {
            if(q==0 || q==row_size-1 || r==0 || r==size_with_borders-1){
                continue;
            }

            if(!wasSpacing){
                for(int t=0;t<size_with_borders-row_size;t++){
                    cout<<" ";
                }
                wasSpacing = true;
            }
            cout << Board_vector[r][q].sign << " ";
        }
        if(r!=0) cout << '\n';
    }
}


void Board::printBoardAsCoords() const {
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

void Board::printCOORDS(){
    for(auto & i : Board_vector){
        for(int j=0;j<i.size();j++){
            cout<<i[j].hex_coords.x<<i[j].hex_coords.y<<" ";
        }
        cout<<endl;
    }
}

bool Board::isCoordsValid(char x, int y) const {
    return coordsToIndexes(x,y).first!=-1;
}

bool Board::isBorder(char x, int y) const {
    return Board_vector[coordsToIndexes(x,y).first][coordsToIndexes(x,y).second].border;
}

bool Board::isDirectionValid(char x, int y, char x1, int y1) const{
    int size_with_borders = (size+1)*2-1;
    int height_index = coordsToIndexes(x,y).first;
    int width_index = coordsToIndexes(x,y).second;
    int height1_index = coordsToIndexes(x1,y1).first;
    int width1_index = coordsToIndexes(x1,y1).second;
    vector <std::pair<int,int>> possible_directions;
    int current_line_size = (2 * size + 1) - abs(size - height_index);

    if(height_index==-1 || width_index==-1 || height1_index==-1 || width1_index==-1){
        return false;
    }
    if(Board_vector[height1_index][width1_index].border){
        return false;
    }

    if(height_index==0){
        if(height_index-1==height1_index && width_index==width1_index){
            return true;
        }
        else if(height_index-1==height1_index && width_index+1==width1_index){
            return true;
        }
    }

    if(height_index==size_with_borders-1){
        if(height_index-1==height1_index && width_index==width1_index){
            return true;
        }
        else if(height_index-1==height1_index && width_index+1==width1_index){
            return true;
        }
    }

    if(height_index==height1_index && (width_index-1==width1_index || width_index+1==width1_index)){
        return true;
    }



    if(height_index<(size_with_borders-1)/2){
        if(width_index==0){
            if(height_index+1==height1_index && width_index+1==width1_index){
                return true;
            }
        }
        if(width_index==current_line_size-2){
            if(height_index+1==height1_index && width_index==width1_index){
                return true;
            }
        }
    }
    else if(height_index>(size_with_borders-1)/2){
        if(width_index==0){
            if(height_index-1==height1_index && width_index+1==width1_index){
                return true;
            }
        }
        if(width_index==current_line_size-2){
            if(height_index-1==height1_index && width_index==width1_index){
                return true;
            }
        }
    }
    return false;
}


//bool Board::isDirectionValid(char x, int y, char x1, int y1) const {
//    int height_index = coordsToIndexes(x,y).first;
//    int width_index = coordsToIndexes(x,y).second;
//    int x1_index = coordsToIndexes(x1,y1).first;
//    int y1_index = coordsToIndexes(x1,y1).second;
//
//    if(height_index==-1 || width_index==-1 || x1_index==-1 || y1_index==-1){
//        return false;
//    }
//    if(Board_vector[height_index][width_index].border){
//        return false;
//    }
//
//    if(height_index==x1_index && (width_index-1==y1_index || width_index+1==y1_index)){
//        return true;
//    }
//
//    if(height_index<size+1){
//
//
//    }
//    else if(height_index>=size+1){
//
//    }
//
//    return false;
//
//}
