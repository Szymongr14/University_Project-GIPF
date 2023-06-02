//
// Created by szymo on 16.05.2023.
//

#include "Board.h"
#include "GameState.h"


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

    if(actual_white_pawns_left>expected_white_pawns_left){
        message_to_user=2;
        invalid_board= true;
    }
    if(actual_black_pawns_left>expected_black_pawns_left){
        message_to_user=3;
        invalid_board= true;
    }
    if(row_vector.size()!=expected_row_size){
        message_to_user=1;
        invalid_board= true;
    }

    if(message_to_user==0){
        invalid_board=false;
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

void Board::printCOORDS(){
    for(auto & i : Board_vector){
        for(auto & j : i){
            cout<<j.hex_coords.x<<j.hex_coords.y<<" ";
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
    int current_line_size = (2 * size + 1) - abs(size - height_index);

    if(height_index==-1 || width_index==-1 || height1_index==-1 || width1_index==-1){
        return false;
    }
    if(Board_vector[height1_index][width1_index].border){
        return false;
    }

    if(height_index==0){
        if(height_index+1==height1_index && width_index==width1_index){
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

vector<std::pair<int, int>> Board::getRow(char x, int y, char x1, int y1) const {
    vector<std::pair<int, int>> row;
    int size_with_borders = (size+1)*2-1;
    int height_index = coordsToIndexes(x,y).first;
    int width_index = coordsToIndexes(x,y).second;
    int height1_index = coordsToIndexes(x1,y1).first;
    int width1_index = coordsToIndexes(x1,y1).second;
    int temp_x=height1_index, temp_y=width1_index;

    if(height_index+1==height1_index && width_index+1==width1_index){
        while(!Board_vector[temp_x][temp_y].border){
            row.emplace_back(temp_x,temp_y);
            if(temp_x<(size_with_borders-1)/2){
                temp_x++;
                temp_y++;
            }
            else{
                temp_x++;
            }
        }
        return row;
    }
    else if(height_index+1==height1_index && width_index==width1_index){
        while(!Board_vector[temp_x][temp_y].border){
            row.emplace_back(temp_x,temp_y);
            if(temp_x<(size_with_borders-1)/2){
                temp_x++;
            }
            else{
                temp_x++;
                temp_y--;
            }
        }
        return row;
    }
    else if(height_index==height1_index && width_index+1==width1_index){
        while(!Board_vector[temp_x][temp_y].border){
            row.emplace_back(temp_x,temp_y);
            temp_y++;
        }
        return row;
    }
    else if(height_index==height1_index && width_index-1==width1_index){
        while(!Board_vector[temp_x][temp_y].border){
            row.emplace_back(temp_x,temp_y);
            temp_y--;
        }
        return row;
    }
    else if(height_index-1==height1_index && width_index==width1_index){
        while(!Board_vector[temp_x][temp_y].border){
            row.emplace_back(temp_x,temp_y);
            if(temp_x<=(size_with_borders-1)/2){
                temp_x--;
                temp_y--;
            }
            else{
                temp_x--;
            }
        }
        return row;
    }
    else if(height_index-1==height1_index && width_index+1==width1_index){
        while(!Board_vector[temp_x][temp_y].border){
            row.emplace_back(temp_x,temp_y);
            if(temp_x<=(size_with_borders-1)/2){
                temp_x--;
            }
            else{
                temp_x--;
                temp_y++;
            }
        }
        return row;
    }

    return row;
}

bool Board::isRowFull(const vector <std::pair<int,int>>& row) const {
    for(auto & pair: row){
        if(Board_vector[pair.first][pair.second].sign=='_'){
            return false;
        }
    }
    return true;
}

void Board::movePawns(vector<std::pair<int, int>> row, bool isWhite) {
    int temp_x, temp_y;
    temp_x = row[0].first;
    temp_y = row[0].second;
    int i=1;

    while(Board_vector[temp_x][temp_y].sign!='_'){
        temp_x = row[i].first;
        temp_y = row[i].second;
        i++;
    }

    for(int j = i-1; j>0; j--){
        Board_vector[row[j].first][row[j].second].sign = Board_vector[row[j-1].first][row[j-1].second].sign;
    }

    if(isWhite){
        Board_vector[row[0].first][row[0].second].sign = 'W';
    }
    else{
        Board_vector[row[0].first][row[0].second].sign = 'B';
    }
}

void Board::deletePawns(int k,const vector<Pawn>& pawns, bool isWhiteTurn,int which_color) {
    for(auto & pawn: pawns){
        if(pawn.sign=='W' && pawn.to_remove){
            if(which_color==1){
                gameState->setWhitePawnsLeft(gameState->getWhitePawnsLeft()+1);
            }
        }
        else if(pawn.sign=='B'&& pawn.to_remove){
            if(which_color==2){
                gameState->setBlackPawnsLeft(gameState->getBlackPawnsLeft()+1);
            }
        }
        else{
            continue;
        }

        if(pawn.to_remove) Board_vector[pawn.x][pawn.y].sign = '_';
    }
}

int hasNFollowing(vector<Pawn> &vec, int n) {
    //0 - no n following
    //1 - white
    //2 - black

    if (vec.size() < n) {
        return 0;
    }

    for (int i = 0; i <= vec.size() - n; ++i) {
        bool are_same = true;
        for (int j = 1; j < n; ++j) {
            if (vec[i + j].sign != vec[i].sign || vec[i].sign == '_') {
                are_same = false;
                break;
            }
        }
        if (are_same) {
            //which color has N following
            int color = vec[i].sign == 'W' ? 1 : 2;

            while (vec[i - 1].sign != '_' && i > 0) {
                i--;
            }
            while (vec[i].sign != '_' && i <= vec.size() - 1) {
                vec[i].to_remove = true;
                i++;
            }
            if(color==1){
                return 1;
            }
            else{
                return 2;
            }
        }
    }
    return 0;
}

int Board::checkHorizontalLines(int k,bool isWhiteTurn,bool delete_pawns) {
    vector<Pawn> pawns;
    Pawn temp_pawn;
    int invalid_rows=0;
    int size_with_borders = (size + 1) * 2 - 1;

    for(int i=0; i<size_with_borders; i++){
        int current_line_size = (2 * size + 1) - abs(size - i);
        for(int j=0; j<current_line_size; j++){
            if(Board_vector[i][j].border){
                continue;
            }
            else{
                temp_pawn.sign = Board_vector[i][j].sign;
                temp_pawn.x = i;
                temp_pawn.y = j;
                pawns.push_back(temp_pawn);
            }
        }
        int return_value = hasNFollowing(pawns,k);
        if(return_value){
            invalid_rows++;
            if(delete_pawns){
                deletePawns(k,pawns,isWhiteTurn,return_value);
            }
        }
        pawns.clear();
    }
    return invalid_rows;
}

int Board::checkSWandNE(int k,bool isWhiteTurn,bool delete_pawns){
    vector<Pawn> pawns;
    Pawn temp_pawn;
    int temp_x=0, temp_y=0, temp_x_to_slant, temp_y_to_slant,invalid_rows=0;
    int size_with_borders = (size + 1) * 2 - 1;

    //first diagonal
    int j = 0;
    for (int i = 0; i < size_with_borders; i++) {
        if (j < size+1) {
            temp_x_to_slant = temp_x;
            temp_y_to_slant = temp_y;
            do{
                temp_pawn.sign = Board_vector[temp_x_to_slant][temp_y_to_slant].sign;
                temp_pawn.x = temp_x_to_slant;
                temp_pawn.y = temp_y_to_slant;
                pawns.push_back(temp_pawn);
                if(temp_x_to_slant<(size_with_borders-1)/2){
                    temp_x_to_slant++;
                }
                else{
                    temp_x_to_slant++;
                    temp_y_to_slant--;
                }
            }while(!Board_vector[temp_x_to_slant][temp_y_to_slant].border);
            temp_y++;
            j++;
        }
        else {
            temp_x++;
            temp_x_to_slant = temp_x;
            temp_y_to_slant = temp_y;
            do{
                temp_pawn.sign = Board_vector[temp_x_to_slant][temp_y_to_slant].sign;
                temp_pawn.x = temp_x_to_slant;
                temp_pawn.y = temp_y_to_slant;
                pawns.push_back(temp_pawn);
                if(temp_x_to_slant<(size_with_borders-1)/2){
                    temp_x_to_slant++;
                }
                else{
                    temp_x_to_slant++;
                    temp_y_to_slant--;
                }
            }while(!Board_vector[temp_x_to_slant][temp_y_to_slant].border);
            temp_y++;
        }
        int return_value = hasNFollowing(pawns,k);
        if(return_value){
            invalid_rows++;
            if(delete_pawns){
                deletePawns(k,pawns,isWhiteTurn,return_value);
            }
        }
        pawns.clear();
    }
    return invalid_rows;
}

int Board::checkSEandNW(int k,bool isWhiteTurn,bool delete_pawns) {
    vector<Pawn> pawns;
    Pawn temp_pawn{};
    int temp_x=0, temp_y=(size+1)-1, temp_x_to_slant, temp_y_to_slant,invalid_rows=0;
    int size_with_borders = (size + 1) * 2 - 1;
    int j = 0;

    //second diagonal
    for (int i = 0; i < size_with_borders; i++) {
        if (j < size+1) {
            temp_x_to_slant = temp_x;
            temp_y_to_slant = temp_y;
            do{
                temp_pawn.sign = Board_vector[temp_x_to_slant][temp_y_to_slant].sign;
                temp_pawn.x = temp_x_to_slant;
                temp_pawn.y = temp_y_to_slant;
                pawns.push_back(temp_pawn);
                if(temp_x_to_slant<(size_with_borders-1)/2){
                    temp_x_to_slant++;
                    temp_y_to_slant++;
                }
                else{
                    temp_x_to_slant++;
                }
            }while(!Board_vector[temp_x_to_slant][temp_y_to_slant].border);
            temp_y--;
            j++;
        }
        else {
            temp_y=0;
            temp_x++;
            temp_x_to_slant = temp_x;
            temp_y_to_slant = temp_y;
            do{
                temp_pawn.sign = Board_vector[temp_x_to_slant][temp_y_to_slant].sign;
                temp_pawn.x = temp_x_to_slant;
                temp_pawn.y = temp_y_to_slant;
                pawns.push_back(temp_pawn);
                if(temp_x_to_slant<(size_with_borders-1)/2){
                    temp_x_to_slant++;
                    temp_y_to_slant++;
                }
                else{
                    temp_x_to_slant++;
                }
            }while(!Board_vector[temp_x_to_slant][temp_y_to_slant].border);
        }
        int return_value = hasNFollowing(pawns,k);
        if(return_value){
            invalid_rows++;
            if(delete_pawns){
                deletePawns(k,pawns,isWhiteTurn,return_value);
            }
        }
        pawns.clear();
    }
    return invalid_rows;
}

int Board::checkBoard(int k,bool isWhiteTurn,bool delete_pawns) {
    int invalid_rows=0;

    // checking every diagonal and horizontal line
    invalid_rows += checkSWandNE(k,isWhiteTurn,delete_pawns);
    invalid_rows += checkSEandNW(k,isWhiteTurn,delete_pawns);
    invalid_rows += checkHorizontalLines(k,isWhiteTurn,delete_pawns);

    if(invalid_rows && !delete_pawns) invalid_board = true;
    return invalid_rows;
}

bool Board::isInvalidBoard() const {
    return invalid_board;
}
