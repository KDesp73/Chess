#pragma once

#include <iostream>

#include "piece_declarations.h"


using namespace std;

//board_functions.cpp
void printBoard(char board[][8]);

int* translateSquare(string move);

void makeMove(string from, string to, char board[][8]);

char pieceToMove(int* coords, char board[][8]);

char pieceToMove(string move, char board[][8]);

void printCoords(int* coords);

void printCoords(string move);

void scanBoard(Piece* whitePieces, Piece* blackPieces, char board[][8]);

void emptyBoard(char board[][8]);


//game_logic.cpp
void start();

void promt(Pieces p, char board[][8]);

