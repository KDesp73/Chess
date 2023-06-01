#pragma once

#include <cstring>
#include <string>
#include "../Pieces/piece_declarations.h"

using namespace std;

class Board{
    public:
        string playingAs;
        string moveFor = "white";
        char board[8][8] = {
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
        };
        Pieces *wp = new WhitePieces();
        Pieces *bp = new BlackPieces();


        ~Board(){}
        Board(string playingAs, string fen){
            this->playingAs = playingAs;
            importFEN(fen);
            wp->loadPieces(board);
            bp->loadPieces(board);
        }

        Board(string playingAs, char board[8][8]){
            this->playingAs = playingAs;
            memcpy(this->board, board, 8*8*sizeof(char));
            wp->loadPieces(board);
            bp->loadPieces(board);
        }

        void importFEN(string fen);
        static string exportFEN(Board *board);
        static string exportFEN(char board[][8]);
        void printBoard();
        void printBoard(string playingAs);
        void printBigBoard();
        void printBigBoard(string playingAs);
        void scanBoard(vector<Piece*> whitePieces, vector<Piece*> blackPieces);

        static bool movePiece(Move move, Board *board);
        static void moveFreely(Move move, Board *board);
        static bool removePiece(string square, Board *board);
        static bool removePieceFreely(string square, Board *board);

        static bool promotePawn(string square, Pawn *pawn, Board *board);
        static bool enpassantPawn(string square, Pawn *pawn, Board *board);
        static bool castleKing(string square, King *king, Board *board);
};
