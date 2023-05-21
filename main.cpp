#include <iostream>
#include <string>
using namespace std;
#include "GameState.h"

int main() {
    string command;
    GameState gameState;
    do{
        cout<<"Type command: " <<endl;
        cin>>command;

        if(command=="LOAD_GAME_BOARD"){
            gameState.loadGameState();
        }
        else if(command=="PRINT_BOARD"){
            gameState.printGameState();
        }

    }while(command!="QUIT" && command!="q");
    return 0;
}
