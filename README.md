# ChessBoard
A minimal example (+-300 lines of code) of implementing a chess game in _C++_.
This program sends the state of the chess board to std::out.

Introduction:
Chess is a widely popular and well-respected turn-based centuries-old game played on an 8x8 board
with white and black pieces (pawns, knights, bishops, rooks, queens, and kings) that move according to
the rules that can be quickly learned even by young kids. 

I have written a chess game. No castling or en passant, pawn gets promoted to queen. Game isn't drawn after 50 moves. The AI is a naive minimax implementation.

The chess AI algorithms can be improved, more tricks can be used. Alpha-beta pruning, negimax. But that is not my intent. My goal is not to make a great chess engine.

The art of the game is not easy to master, though, so many software products have been developed to implement chess as a video game on numerous platforms and assist the beginner, amateur, and professional chess players alike. Some of these
software products are free and open source, letting the developers learn by examining the existing solu-
tions. Chess programming involves the development of the following products.

How to compile:
g++ *.cpp

