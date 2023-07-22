#include "ChessBoard.h"


	string ChessBoard::ReplaceString(std::string subject, std::string search, std::string replace)
	{
    size_t pos = 0;
		while((pos = subject.find(search, pos)) != std::string::npos) {
			 subject.replace(pos, search.length(), replace);
			 pos += replace.length();
		}
    return subject;
	}
	
	string ChessBoard::replacemoves(std::string moves)
	{
		moves = ReplaceString(moves, "a", "1");
		moves = ReplaceString(moves, "b", "2");
		moves = ReplaceString(moves, "c", "3");
		moves = ReplaceString(moves, "d", "4");
		moves = ReplaceString(moves, "e", "5");
		moves = ReplaceString(moves, "f", "6");
		moves = ReplaceString(moves, "g", "7");
		moves = ReplaceString(moves, "h", "8");
		return moves;		
	}

    void ChessBoard::reset(){
        turn = Turn::white;
        white_pieces.clear();
        black_pieces.clear();
        for(int i=1; i < 9; ++i){
            white_pieces[Pos(i,7)]=Piece::white_pawn;
            black_pieces[Pos(i,2)]=Piece::black_pawn;
        }
        int n=1;
        for(auto piece : {Piece::rook,Piece::knight,Piece::bishop,Piece::king}){
            white_pieces[Pos(n,8)]=white_pieces[Pos(9-n,8)]=black_pieces[Pos(n,1)]=black_pieces[Pos(9-n,1)]=piece;
            ++n;
        }
        white_pieces[Pos(4,8)]=black_pieces[Pos(4,1)]=Piece::queen;
    }

    void ChessBoard::flipTurn(){ turn = turn == Turn::white? Turn::black : Turn::white; }

    bool ChessBoard::makeMove(Pos from, Pos to){
        vector<Pos> allowed = possibleMoves(from);
        if(find(allowed.begin(), allowed.end(), to) == allowed.end())
            return false;
        opponentPieces().erase(to);
        moverPieces()[to]=moverPieces()[from];
        moverPieces().erase(from);
        if((moverPieces()[to]==Piece::white_pawn || moverPieces()[to]==Piece::black_pawn) && (to.y == 1 || to.y == 8))
            moverPieces()[to]=Piece::queen;
        flipTurn();
        return true;
    }

    vector<Pos> ChessBoard::possibleMoves(const Pos & from){
        vector<Pos> moves;
        auto isOwn = [&] (int dx, int dy) -> bool { return moverPieces().count(Pos(from,dx,dy));};
        auto isOpponent = [&] (int dx, int dy) -> bool { return opponentPieces().count(Pos(from,dx,dy));};
        auto isInsideBoard = [&] (int dx, int dy) -> bool { Pos p(from,dx,dy); return p.x < 9 && p.x > 0 && p.y < 9 && p.y > 0; };
        auto isFree = [&] (int dx, int dy) -> bool { return !isOwn(dx,dy) && isInsideBoard(dx,dy) && !isOpponent(dx,dy); };

        auto addMove = [&] (int dx, int dy) -> bool {
            if(isFree(dx,dy) || isOpponent(dx,dy)){
                moves.push_back(Pos(from,dx,dy));
                return true;
            }
            return false;
        };

        if(!isOwn(0,0))
            return moves;

        auto moving_piece = moverPieces()[from];
        switch(moving_piece){
            case Piece::white_pawn:
                if(isFree(0,-1)) addMove(0,-1);
                if(isFree(0,-1) && isFree(0,-2) && from.y==7) addMove(0,-2);
                if(isOpponent(-1,-1)) addMove(-1,-1);
                if(isOpponent(1,-1)) addMove(1,-1);
                break;

            case Piece::black_pawn:
                if(isFree(0,1)) addMove(0,1);
                if(isFree(0,1) && isFree(0,2) && from.y==2) addMove(0,2);
                if(isOpponent(-1,1)) addMove(-1,1);
                if(isOpponent(1,1)) addMove(1,1);
                break;

            case Piece::knight:
                addMove(-2,-1); addMove(-2,1); addMove(2,-1); addMove(2,1);
                addMove(-1,-2); addMove(-1,2); addMove(1,-2); addMove(1,2);
                break;

            case Piece::king:
                for(auto dy : {-1,0,1})
                for(auto dx : {-1,0,1})
                addMove(dy,dx);
                break;

            case Piece::queen:
            case Piece::rook:
                for(int n=1; n < 9 && addMove(0,n) && !isOpponent(0,n); ++n);
                for(int n=1; n < 9 && addMove(0,-n) && !isOpponent(0,-n); ++n);
                for(int n=1; n < 9 && addMove(n,0) && !isOpponent(n,0); ++n);
                for(int n=1; n < 9 && addMove(-n,0) && !isOpponent(-n,0); ++n);
                if(moving_piece != Piece::queen)
                    break;

            case Piece::bishop:
                for(int n=1; n < 9 && addMove(n,n) && !isOpponent(n,n); ++n);
                for(int n=1; n < 9 && addMove(n,-n) && !isOpponent(n,-n); ++n);
                for(int n=1; n < 9 && addMove(-n,n) && !isOpponent(-n,n); ++n);
                for(int n=1; n < 9 && addMove(-n,-n) && !isOpponent(-n,-n); ++n);
                break;
        }

        return moves;
    }

    void ChessBoard::printBoard(){
        static map<Piece, char> sprites =
         { {Piece::white_pawn,'P'},
		   {Piece::black_pawn,'P'},
		   {Piece::rook,'R'},
		   {Piece::knight,'N'},
           {Piece::bishop,'B'},
           {Piece::king,'K'},
           {Piece::queen,'Q'}
         };
         
        cout<<endl<<"        a     b     c     d     e     f     g     h   "<<endl;
        cout<<"      _____ _____ _____ _____ _____ _____ _____ _____ ";
        for(int y=1; y < 9; ++y){
            if(show_coordinates)
                cout<<endl<<"     |1"<<y<<"   |2"<<y<<"   |3"<<y<<"   |4"<<y<<"   |5"<<y<<"   |6"<<y<<"   |7"<<y<<"   |8"<<y<<"   |";
            else
                cout<<endl<<"     |     |     |     |     |     |     |     |     |";
            cout<<endl<<"  "<<y<<"  ";
            for(int x=1; x < 9; ++x){
                cout<<"|  ";
                if(white_pieces.count(Pos(x,y)))
                    cout<<sprites[white_pieces[Pos(x,y)]];
                else if(black_pieces.count(Pos(x,y)))
                    cout<<(char)tolower(sprites[black_pieces[Pos(x,y)]]);
                else 
                    cout<<" ";
                cout<<"  ";
            }
            cout<<"|  "<<y<<endl<<"     |_____|_____|_____|_____|_____|_____|_____|_____|";
        }
        cout<<endl<<endl<<"        a     b    c     d     e     f     g     h   "<<endl<<endl;
    }

    void ChessBoard::printHelp(){
        cout<<endl<<"* h: help, q: quit, p: show board, s: toggle show coordinates"<<endl<<"* Input: yxyx is from-to or cell number."<<endl<<endl;
    }

    /* False to exit */
    bool ChessBoard::promptInput(){
        string move;
        illegalmove:
        if(turn==Turn::white)
            cout<<"White move: ";
        else
            cout<<"Black move: ";
        if(move == "")
            cin>>move;
            move = replacemoves(move);
        if(move == "q"){
            cout<<"Good bye"<<endl<<endl;
            return false;
        }
        if(move == "?" || move == "h" || move == "help"){
            printHelp();
            move="";
            goto illegalmove;
        }
        if(move == "s"){
            show_coordinates = !show_coordinates;
            printBoard();
            move="";
            goto illegalmove;
        }

        if(move == "p"){
            printBoard();
            move="";
            goto illegalmove;
        }
                        
        Pos from(-1,-1),to(-1,-1);
        if(move.length() == 4){			
            from.x = move[0] - '0';
            from.y = move[1] - '0';
            to.x = move[2] - '0';
            to.y = move[3] - '0';
        }
        if(!makeMove(from,to)){
            cout<<"* Illegal move"<<endl;
            move = "";
            goto illegalmove;
        }
        printBoard();
        return true;
    }

    int ChessBoard::score(){
        int sumWhite = 0;
        for(auto & p : white_pieces)
            sumWhite += pieceValues[p.second];
        int sumBlack = 0;
        for(auto & p : black_pieces)
            sumBlack += pieceValues[p.second];
        return sumWhite-sumBlack;
    }

    bool ChessBoard::hasKing(){
        for(auto & p : moverPieces())
            if(p.second == Piece::king)
                return true;
        return false;
    }  

    Move ChessBoard::minimax(int depth, bool minimize){
        Move best_move;
        best_move.score = -1000000 + 2000000*minimize;
        if(0 == depth){
            best_move.score = score();
            return best_move;
        }

        for(auto & from : moverPieces()){
            for(auto & to : possibleMoves(from.first)){
                ChessBoard branch = *this;
                branch.makeMove(from.first,to);
                Move option = branch.minimax(depth-1, !minimize);
                if((option.score > best_move.score && !minimize) || (option.score < best_move.score && minimize)){
                    best_move.score = option.score;
                    best_move.from = from.first;
                    best_move.to = to;
                }
            }
        }
        return best_move;
    }

    void ChessBoard::AIMove(){
        bool minimize = turn == Turn::black ? true : false;
        Move m = minimax(4,minimize);
        makeMove(m.from,m.to);
        printBoard();
    }




