#pragma once

#include <iostream>
#include <vector>

#include "../Pieces/piece_declarations.h" 
#include "./structs.h"


using namespace std;

//board_functions.cpp

// int* translateSquare(string square);
Coords translateSquare(string square);
string translateSquare(Coords coords);

bool makeMove(string from, string to, char board[][8]);

char pieceToMove(Coords coords, char board[][8]);

char pieceToMove(string square, char board[][8]);

void printCoords(Coords coords);

void printCoords(string square);



/*void emptyBoard(char (*board)[8]);*/

void emptyBoard(char board[][8]);

vector<Piece*> squareIsAttacked(string square, Pieces *p, char board[][8]);

bool isValidSquare(string square);


