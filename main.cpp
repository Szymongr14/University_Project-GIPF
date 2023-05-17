#include <iostream>
#include <string>
using namespace std;

int main() {
    string command;
    do{
        cout<<"Type command: ";
        cin>>command;

        if(command=="LOAD_GAME_BOARD"){
            cout<<"load"<<endl;
        }
        else if(command=="PRINT_BOARD"){
            cout<<"print"<<endl;
        }

    }while(command!="QUIT" && command!="q");
    return 0;
}
