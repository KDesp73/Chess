#pragma once

#include <string>
#include "../Pieces/piece_declarations.h"

class Board{
    public:
        string playingAs;
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

        void importFEN(string fen);
        string exportFEN();
        void printBoard();
        void printBoard(string playingAs);
        void printBigBoard();
        void printBigBoard(string playingAs);

        void scanBoard(vector<Piece*> whitePieces, vector<Piece*> blackPieces);
};