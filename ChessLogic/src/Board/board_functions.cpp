#include <bits/stdc++.h>

#include <iostream>

#include "../Pieces/piece_declarations.h"
#include "board_declarations.h"

using namespace std;

void printBoard(char board[][8]) { printBoard("white", board); }

void printBoard(string playingAs, char board[][8]) {
    if (playingAs == "white") {
        cout << "   ABCDEFGH" << endl << endl;
        for (int i = 7; i >= 0; i--) {
            cout << i + 1 << "  ";
            for (int j = 0; j < sizeof(board[i]); j++) {
                cout << board[i][j];
            }
            cout << "  " << i + 1 << endl;
        }
        cout << endl << "   ABCDEFGH" << endl << endl;
    } else if (playingAs == "black") {
        cout << "   HGFEDCBA" << endl << endl;
        for (int i = 0; i <= 7; i++) {
            cout << i + 1 << "  ";
            for (int j = 0; j < sizeof(board[i]); j++) {
                cout << board[i][j];
            }
            cout << "  " << i + 1 << endl;
        }
        cout << endl << "   HGFEDCBA" << endl << endl;
    } else {
        cout << "Incorrect argument" << endl;
    }
}

void printBigBoard(char board[][8]) { printBigBoard("white", board); }

void printBigBoard(string playingAs, char board[][8]) {
    if (playingAs == "white") {
        cout << "     A   B   C   D   E   F   G   H " << endl;
        cout << "   +---+---+---+---+---+---+---+---+" << endl;
        for (int i = 7; i >= 0; i--) {
            cout << i + 1 << "  ";
            for (int j = 0; j < sizeof(board[i]); j++) {
                cout << "| " << board[i][j] << " ";
            }
            cout << "|  " << i + 1 << endl;
            cout << "   +---+---+---+---+---+---+---+---+" << endl;
        }
        cout << "     A   B   C   D   E   F   G   H " << endl;
    } else if (playingAs == "black") {
        cout << "     H   G   F   E   D   C   B   A " << endl;
        cout << "   +---+---+---+---+---+---+---+---+" << endl;
        for (int i = 0; i <= 7; i++) {
            cout << i + 1 << "  ";
            for (int j = 0; j < sizeof(board[i]); j++) {
                cout << "| " << board[i][j] << " ";
            }
            cout << "|  " << i + 1 << endl;
            cout << "   +---+---+---+---+---+---+---+---+" << endl;
        }
        cout << "     H   G   F   E   D   C   B   A " << endl;

    } else {
        cout << "Incorrect argument" << endl;
    }
}

void scanBoard(vector<Piece*> whitePieces, vector<Piece*> blackPieces, char board[][8]) {
    string white_square, black_square;
    int *white_coords, *black_coords;

    for (int i = 0; i < 16; i++) {
        white_square = whitePieces.at(i)->currentSquare;
        black_square = blackPieces.at(i)->currentSquare;

        white_coords = translateSquare(white_square);
        black_coords = translateSquare(black_square);

        board[*white_coords][*(white_coords + 1)] =
            whitePieces.at(i)->boardChar;
        board[*black_coords][*(black_coords + 1)] =
            blackPieces.at(i)->boardChar;
    }
}

int* translateSquare(string square) {
    string letters = "abcdefgh";

    int x = square.at(1) - 48 - 1;
    int y = letters.find(square.at(0));

    if ((square.length() < 0 || square.length() > 2) ||
        ((x < 0 || x > 7) && (y < 0 || y > 7))) {
        cout << "Invalid square";
        return NULL;
    }

    int* coords = new int[2];

    coords[0] = x;
    coords[1] = y;

    return coords;
}

string translateSquare(int* coords) {
    string letters = "abcdefgh";

    string rank, file;

    rank = letters[(coords[1])];
    file = coords[0] + 48 + 1;

    return rank + file;
}

char pieceToMove(int* coords, char board[][8]) {
    return board[*coords][*(coords + 1)];
}

char pieceToMove(string square, char board[][8]) {
    int* coords = translateSquare(square);

    return pieceToMove(coords, board);
}

bool makeMove(string from, string to, char board[][8]) {
    int* fromCoords = new int[2];
    fromCoords = translateSquare(from);
    int* toCoords = new int[2];
    toCoords = translateSquare(to);

    if (fromCoords == NULL || toCoords == NULL) return false;

    char piece = pieceToMove(from, board);

    // cout << "Piece to move: |" << piece << "|" << endl;

    board[*fromCoords][*(fromCoords + 1)] = ' ';
    board[*toCoords][*(toCoords + 1)] = piece;

    return true;
}

void printCoords(int* coords) {
    cout << "(" << *coords << ", " << *(coords + 1) << ")" << endl;
}

void printCoords(string square) {
    int* coords = translateSquare(square);

    cout << square << " is "
         << "(" << *coords << ", " << *(coords + 1) << ")" << endl;
}

void emptyBoard(char board[][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = ' ';
        }
    }
}

vector<Piece*> squareIsAttacked(string square, Pieces* p, char board[][8]) {
    vector<Piece*> list;
    for (int i = 0; i < p->pieces.size(); i++) {
        if ((p->pieces.at(i)->isValidMove(square, board) &&
             p->pieces.at(i)->type != "Pawn") ||
            (p->pieces.at(i)->type == "Pawn" &&
             (dynamic_cast<Pawn*>(p->pieces.at(i)))
                 ->isValidCapture(square, board))) {
            list.push_back(p->pieces.at(i));
        }
    }
    return list;
}

bool isValidSquare(string square){
    if(square.length() != 2) return false;
    if(!isalpha(square[0])) return false;
    if(!isdigit(square[1])) return false;

    return true;
}