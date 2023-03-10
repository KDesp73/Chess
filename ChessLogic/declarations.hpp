#include <iostream>
using namespace std;


void printBoard(char board[][8]);

int* translateMove(string move);

void makeMove(string from, string to);

int* fixCoords(int* coords);

char pieceToMove(string move, char board[][8]);

char pieceFromCoords(int x, int y, char board[][8]);

void printCoords(int* coords);
