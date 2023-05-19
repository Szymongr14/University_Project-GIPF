#include <iostream>
#include <string>
using namespace std;
#include "Board.h"
#include "GameState.h"

int main() {
    string command;
    GameState gameState;
    Board board(4);
    do{
        cout<<"Type command: ";
        cin>>command;

        if(command=="LOAD_GAME_BOARD"){
//            gameState.loadGameState();
//            gameState.printGameState();

            //cout<<"elo"<<endl;
            board.loadBoard();

        }
        else if(command=="PRINT_BOARD"){
            board.printBoard();
            cout<<endl<<endl<<endl;
            board.printBoardWithCoords();
        }

    }while(command!="QUIT" && command!="q");
    return 0;
}
