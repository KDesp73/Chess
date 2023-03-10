#include <iostream>
#include <bits/stdc++.h>
#include "declarations.hpp"

using namespace std;

void printBoard(char board[][8]){
	cout << "   ABCDEFGH" << endl << endl;
	for(int i=0; i < sizeof(board); i++){
		cout << 8 - i << "  ";
		for(int j=0; j < sizeof(board[i]); j++){
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << endl << "   ABCDEFGH" << endl << endl;
}

int* translateMove(string move){
	string letters = "abcdefgh";
	
	int x = letters.find(move.at(0));
	int y = move.at(1) - 48 - 1;
	
	if((move.length() < 0 || move.length() > 2) || ((x < 0 || x > 7) && (y < 0 || y > 7))) {
		cout << "Invalid move";
		return NULL;
	}
	
	static int coords[] = {x, y};
	
	return fixCoords(coords);
}

int* fixCoords(int* coords){
	int temp = *coords;
	temp = 7 - temp;
	
	*coords = temp;
	
	return coords;
}

void makeMove(string from, string to, char board[][8]){
	int* fromCoords = translateMove(from);
	int* toCoords = translateMove(to);
	
	printCoords(fromCoords);
	printCoords(toCoords);
	
	if(fromCoords == NULL || toCoords == NULL) return;
	
	char piece = pieceToMove(from, board);
	
	cout << "Piece to move: |" << piece << "|" << endl;
	
	
	
}


char pieceToMove(string move, char board[][8]){
	int* coords = translateMove(move);
	
	return pieceFromCoords(*coords, *(coords+1), board);
}

char pieceFromCoords(int x, int y, char board[][8]){
	return board[y][x];
}

void printCoords(int* coords){
	cout << "(" << *coords << ", " << *(coords+1) << ")" << endl;
}

int main(int argc, char** argv) {
	char board[][8] = {
	{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
	{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
	{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
	};
	
	printBoard(board);
	
	cout << "Piece: " << pieceFromCoords(4, 6, board) << endl;
	cout << "Piece: " << pieceToMove("e2", board);
	
	
	//printCoords(translateMove("e4"));
	
	
	return 0;
}
