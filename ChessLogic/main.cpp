#include <iostream>
#include <bits/stdc++.h>

#include "declarations.h"
#include "piece_declarations.h"



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

	char emptyBoard[][8] = {
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	};
	
	Piece whitePieces[] = {
		new Rook("a1", "white"),
		new Knight("b1", "white"),
		new Bishop("c1", "white"),
		new Queen("d1", "white"),
		new King("e1", "white"),
		new Bishop("f1", "white"),
		new Knight("g1", "white"),
		new Rook("h1", "white"),
		new Pawn("a2", "white"),
		new Pawn("b2", "white"),
		new Pawn("c2", "white"),
		new Pawn("d2", "white"),
		new Pawn("e2", "white"),
		new Pawn("f2", "white"),
		new Pawn("g2", "white"),
		new Pawn("h2", "white")
	};
	
	Piece blackPieces[] = {
		new Rook("a8", "black"),
		new Knight("b8", "black"),
		new Bishop("c8", "black"),
		new Queen("d8", "black"),
		new King("e8", "black"),
		new Bishop("f8", "black"),
		new Knight("g8", "black"),
		new Rook("h8", "black"),
		new Pawn("a7", "black"),
		new Pawn("b7", "black"),
		new Pawn("c7", "black"),
		new Pawn("d7", "black"),
		new Pawn("e7", "black"),
		new Pawn("f7", "black"),
		new Pawn("g7", "black"),
		new Pawn("h7", "black")
	};
	
		
	for(int i=0; i<sizeof(whitePieces); i++){
		cout << whitePieces[i].printPiece();
	}
	
	
	return 0;
}
