#include <bits/stdc++.h>

#include <iostream>

#include "../Pieces/piece_declarations.h"
#include "board_declarations.h"

using namespace std;

Coords translateSquare(string square) {
    string letters = "abcdefgh";

    int x = square.at(1) - 48 - 1;
    int y = letters.find(square.at(0));

    if ((square.length() < 0 || square.length() > 2) ||
        ((x < 0 || x > 7) && (y < 0 || y > 7))) {
        cout << "Invalid square";
        return {};
    }

    Coords coords{x, y};

    return coords;
}

string translateSquare(Coords coords) {
    string letters = "abcdefgh";

    string rank, file;

    rank = letters[(coords.y)];
    file = coords.x + 48 + 1;

    return rank + file;
}

char pieceToMove(Coords coords, char board[][8]) {
    return board[coords.x][coords.y];
}

char pieceToMove(string square, char board[][8]) {
    Coords coords = translateSquare(square);

    return pieceToMove(coords, board);
}

bool makeMove(string from, string to, char board[][8]) {
    Coords fromCoords = translateSquare(from);
    Coords toCoords = translateSquare(to);

    /*if (sizeof(fromCoords) || sizeof(toCoords)) {
        cout << "Empty coords" << endl;
        return false;
    }*/

    char piece = pieceToMove(from, board);

    // cout << "Piece to move: |" << piece << "|" << endl;

    board[fromCoords.x][fromCoords.y] = ' ';
    board[toCoords.x][toCoords.y] = piece;

    return true;
}

void printCoords(Coords coords) {
    cout << "(" << coords.x << ", " << coords.y << ")" << endl;
}

void printCoords(string square) {
    Coords coords = translateSquare(square);

    cout << square << " is "
         << "(" << coords.x << ", " << coords.y << ")" << endl;
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
    if(square.length() != 2){
        // cout << "Move not 2 characters" << endl;
        return false;
    }
    if(!isalpha(square[0])) {
        // cout << "First character not in alphabet" << endl;
        return false;
    }
    if(!isdigit(square[1])) {
        // cout << "Second character not a digit" << endl;
        return false;
    }
    if(square[1] - 48 < 1 || square[1] - 48 > 8) {
        // cout << "Rank number less than 1 or grater than 8" << endl;
        return false;
    }
    if(square[0] < 'a' || square[0] > 'h') {
        // cout << "File character less than a or grater than h" << endl;
        return false;
    }

    return true;
}