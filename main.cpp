#include "ChessBoard.h"

int main(){
    ChessBoard game;    
    game.printHelp();
    bool gameon=true;
    while(gameon){
        game.reset();
        string pick_side = "";
        while(pick_side != "b" && pick_side != "w" && pick_side != "q"){
            cout<<endl<<"(b)lack or (w)hite or (q)uit? ";
            cin>>pick_side;
        }
        if(pick_side == "q"){
            cout<<"Bye."<<endl;
            break;
        }

        if(pick_side == "b")
            game.AIMove();
        else
            game.printBoard();

        while(gameon = game.promptInput()){
            if(!game.hasKing()){
                cout<<"* Victory!!!!"<<endl;
                break;
            }
            game.AIMove();
            if(!game.hasKing()){
                cout<<"* You Lost!!!"<<endl;
                break;
            }
        }
    }
    return 0;   
}



