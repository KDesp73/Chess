#pragma once

#include <cstring>
#include <string>
#include "../Pieces/piece_declarations.h"

using namespace std;

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

        Board(string playingAs, char board[8][8]){
            this->playingAs = playingAs;
            memcpy(this->board, board, 8*8*sizeof(char));
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

string exportFEN(char board[][8]);