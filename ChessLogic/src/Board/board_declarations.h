#pragma once

#include <iostream>
#include <vector>

#include "../Pieces/piece_declarations.h" 


using namespace std;

//board_functions.cpp


int* translateSquare(string move);
string translateSquare(int* coords);

bool makeMove(string from, string to, char board[][8]);

char pieceToMove(int* coords, char board[][8]);

char pieceToMove(string move, char board[][8]);

void printCoords(int* coords);

void printCoords(string move);



/*void emptyBoard(char (*board)[8]);*/

void emptyBoard(char board[][8]);

vector<Piece*> squareIsAttacked(string square, Pieces *p, char board[][8]);

bool isValidSquare(string square);


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