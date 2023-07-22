#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#ifndef _CHESSB_H_
#define _CHESSB_H_

using namespace std;

 struct Pos{
        int x,y;
        Pos(const Pos &p, int dx=0, int dy=0){ *this = p; x+=dx; y+=dy;}
        Pos(int _x, int _y){  x=_x; y=_y; }
        bool operator<(const Pos & p) const { return (x < p.x) || (x==p.x && y < p.y); }
        bool operator==(const Pos & p) const { return x==p.x && y==p.y; }
        Pos(){x=-1;y=-1;}
    };   

    struct Move{
       Pos from,to;
       int score;
    };

class ChessBoard
{
    enum class Turn {white, black} turn;
    enum class Piece {king, queen, white_pawn, black_pawn, rook, bishop, knight};    

    map<Pos,Piece> white_pieces, black_pieces;
    map<Pos,Piece> & moverPieces(){ return turn == Turn::white ? white_pieces : black_pieces; }
    map<Pos,Piece> & opponentPieces(){ return turn == Turn::white ? black_pieces : white_pieces; }

    //static map<Piece,int> pieceValues;
    bool show_coordinates = false;
    
    map<Piece,int> pieceValues {{Piece::king, 10000},
    {Piece::queen, 9}, {Piece::black_pawn, 1}, {Piece::white_pawn, 1},
    {Piece::bishop, 3},{Piece::knight, 3},{Piece::rook, 5}};
    
    public:
    string ReplaceString(std::string subject, std::string search, std::string replace);
    string replacemoves(std::string moves);
    void reset();
    void flipTurn();
    bool makeMove(Pos from, Pos to);
    vector<Pos> possibleMoves(const Pos & from);
    void printBoard();
    void printHelp();
    bool promptInput();
    int score();
    bool hasKing();
    Move minimax(int depth, bool minimize);
    void AIMove();

};

#endif
