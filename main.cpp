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
            gameState.doMove();
        }
    }
    return 0;
}
