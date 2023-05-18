#include <iostream>
#include <string>
using namespace std;
#include "Board.h"
#include "GameState.h"

int main() {
    string command;
    GameState gameState;
    Board board;
    do{
        cout<<"Type command: ";
        cin>>command;

        if(command=="LOAD_GAME_BOARD"){
            gameState.loadGameState();
            gameState.printGameState();
            board.loadBoard();

        }
        else if(command=="PRINT_BOARD"){
            cout<<"print"<<endl;
        }

    }while(command!="QUIT" && command!="q");
    return 0;
}
