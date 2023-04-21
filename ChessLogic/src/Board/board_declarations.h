#pragma once

#include <iostream>
#include <vector>

#include "../Pieces/piece_declarations.h" 


using namespace std;

//board_functions.cpp
void printBoard(char board[][8]);
void printBoard(string playingAs, char board[][8]);
void printBigBoard(char board[][8]);
void printBigBoard(string playingAs, char board[][8]);

int* translateSquare(string move);
string translateSquare(int* coords);

bool makeMove(string from, string to, char board[][8]);

char pieceToMove(int* coords, char board[][8]);

char pieceToMove(string move, char board[][8]);

void printCoords(int* coords);

void printCoords(string move);

void scanBoard(vector<Piece*> whitePieces, vector<Piece*> blackPieces, char board[][8]);

/*void emptyBoard(char (*board)[8]);*/

void emptyBoard(char board[][8]);

vector<Piece*> squareIsAttacked(string square, Pieces *p, char board[][8]);


