#include <iostream>
#include <bits/stdc++.h>
#include "declarations.hpp"

using namespace std;

void printBoard(char board[][8]){
	cout << "   ABCDEFGH" << endl << endl;
	for(int i=sizeof(board)-1; i >= 0 ; i--){
		cout << i+1 << "  ";
		for(int j=0; j < sizeof(board[i]); j++){
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << endl << "   ABCDEFGH" << endl << endl;
}

int* translateMove(string move){
	string letters = "abcdefgh";
	
	int x = move.at(1) - 48 - 1;
	int y = letters.find(move.at(0));
	
	
	if((move.length() < 0 || move.length() > 2) || ((x < 0 || x > 7) && (y < 0 || y > 7))) {
		cout << "Invalid move";
		return NULL;
	}
	
	int* coords = new int[2];
	
	coords[0] = x;
	coords[1] = y;
	
	return coords;
}

void makeMove(string from, string to, char board[][8]){
	int* fromCoords = new int[2];
	fromCoords = translateMove(from);
	int* toCoords = new int[2];
	toCoords = translateMove(to);
	
	if(fromCoords == NULL || toCoords == NULL) return;
	
	char piece = pieceToMove(from, board);
	
	cout << "Piece to move: |" << piece << "|" << endl;
	
	board[*fromCoords][*(fromCoords+1)] = ' ';
	board[*toCoords][*(toCoords+1)] = piece;
	
	delete[] fromCoords;
	delete[] toCoords;
}


char pieceToMove(string move, char board[][8]){
	int* coords = translateMove(move);
	
	return pieceToMove(coords, board);
}

char pieceToMove(int* coords, char board[][8]){
	return board[*coords][*(coords+1)];
}

void printCoords(int* coords){
	cout << "(" << *coords << ", " << *(coords+1) << ")" << endl;
}

void printCoords(string move){
	int* coords = translateMove(move);
	
	cout << move << " is "<< "(" << *coords << ", " << *(coords+1) << ")" << endl;
}

int main(int argc, char** argv) {
	char board[][8] = {
	{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
	{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
	{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
	};
	
	printBoard(board);
	
	makeMove("e2", "e4", board);
	
	printBoard(board);
	
	
	return 0;
}
