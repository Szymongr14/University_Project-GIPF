#include <iostream>
#include <string>
#include "GameState.h"
using std::cout, std::endl, std::cin,std::string;

int main() {
    string command;
    GameState gameState;
    while (cin >> command) {
        if (command == "LOAD_GAME_BOARD") {
            gameState.loadGameState();
        } else if (command == "PRINT_GAME_BOARD") {
            gameState.printGameState();
        }
        else if(command=="DO_MOVE") {
            std::pair<int, int> indexes;
            std::pair<int, int> indexes1;
            string coords;
            cin >> coords;
            char x = coords[0];
            int y = coords[1] - '0';
            char x1 = coords[3];
            int y1 = coords[4] - '0';
            if(gameState.getBoard()->isCoordsValid(x,y) && gameState.getBoard()->isCoordsValid(x1,y1)){
                if(!gameState.getBoard()->isBorder(x,y)){
                    cout<<"BAD_MOVE_"<<x<<y<<"_IS_WRONG_STARTING_FIELD"<<endl<<endl;
                }
                else if(gameState.getBoard()->isBorder(x1,y1)){
                    cout<<"BAD_MOVE_"<<x1<<y1<<"_IS_WRONG_DESTINATION_FIELD"<<endl<<endl;
                }
                else if(!gameState.getBoard()->isDirectionValid(x,y,x1,y1)) {
                    cout<<"UNKNOWN_MOVE_DIRECTION"<<endl<<endl;
                }
                else{
                    indexes = gameState.getBoard()->coordsToIndexes(x,y);
                    indexes1 = gameState.getBoard()->coordsToIndexes(x1,y1);
//                    cout<<indexes.first<<" "<<indexes.second<<endl;
//                    cout<<indexes1.first<<" "<<indexes1.second<<endl;
                    cout<<"MOVE_COMMITTED"<<endl<<endl;
                }
            }
            else{
                if(!gameState.getBoard()->isCoordsValid(x,y)){
                    cout<<"BAD_MOVE_"<<x<<y<<"_IS_WRONG_INDEX"<<endl<<endl;
                }
                else{
                    cout<<"BAD_MOVE_"<<x1<<y1<<"_IS_WRONG_INDEX"<<endl<<endl;
                }
            }
        }
    }
    return 0;
}
