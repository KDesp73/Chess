#include <iostream>
#include <bits/stdc++.h>

#include "declarations.h"
#include "piece_declarations.h"

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

void scanBoard(Piece* whitePieces, Piece* blackPieces, char board[][8]){
	for(int i=0; i < 16; i++){
		string square = whitePieces[i].currentSquare;
		
		int* coords = translateSquare(square);
		
		board[*coords][*(coords+1)] = whitePieces[i].boardChar;
	
		delete[] coords;
	}
	
	for(int i=0; i < 16; i++){
		string square = blackPieces[i].currentSquare;
		
		int* coords = translateSquare(square);
		
		board[*coords][*(coords+1)] = blackPieces[i].boardChar;
	
		delete[] coords;
	}	
}

int* translateSquare(string square){
	string letters = "abcdefgh";
	
	int x = square.at(1) - 48 - 1;
	int y = letters.find(square.at(0));
	
	
	if((square.length() < 0 || square.length() > 2) || ((x < 0 || x > 7) && (y < 0 || y > 7))) {
		cout << "Invalid move";
		return NULL;
	}
	
	int* coords = new int[2];
	
	coords[0] = x;
	coords[1] = y;
	
	return coords;
}


char pieceToMove(int* coords, char board[][8]){
	return board[*coords][*(coords+1)];
}

char pieceToMove(string square, char board[][8]){
	int* coords = translateSquare(square);
	
	return pieceToMove(coords, board);
}

void makeMove(string from, string to, char board[][8]){
	int* fromCoords = new int[2];
	fromCoords = translateSquare(from);
	int* toCoords = new int[2];
	toCoords = translateSquare(to);
	
	if(fromCoords == NULL || toCoords == NULL) return;
	
	char piece = pieceToMove(from, board);
	
	//cout << "Piece to move: |" << piece << "|" << endl;
	
	board[*fromCoords][*(fromCoords+1)] = ' ';
	board[*toCoords][*(toCoords+1)] = piece;
	
	delete[] fromCoords;
	delete[] toCoords;
}




void printCoords(int* coords){
	cout << "(" << *coords << ", " << *(coords+1) << ")" << endl;
}

void printCoords(string square){
	int* coords = translateSquare(square);
	
	cout << square << " is " << "(" << *coords << ", " << *(coords+1) << ")" << endl;
}
