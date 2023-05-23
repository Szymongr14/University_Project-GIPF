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
//        else if(command=="MOVE") {
//            std::pair<int, int> indexes;
//            string coords;
//            cin >> coords;
//            char x = coords[0];
//            int y = coords[1] - '0';
//            indexes = gameState.getBoard()->coordsToIndexes(x,y);
//            cout<<indexes.first<<" "<<indexes.second<<endl;
//        }
    }
    return 0;
}
