#pragma once

#include <iostream>
#include <vector>

#include "../Pieces/piece_declarations.h" 


using namespace std;

//board_functions.cpp


int* translateSquare(string square);
string translateSquare(int* coords);

bool makeMove(string from, string to, char board[][8]);

char pieceToMove(int* coords, char board[][8]);

char pieceToMove(string square, char board[][8]);

void printCoords(int* coords);

void printCoords(string square);



/*void emptyBoard(char (*board)[8]);*/

void emptyBoard(char board[][8]);

vector<Piece*> squareIsAttacked(string square, Pieces *p, char board[][8]);

bool isValidSquare(string square);

struct Move{
    string from;
    string to;
};

