#include <iostream>


#include "declarations.h"

void start(){
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
	
	WhitePieces wp;
	BlackPieces bp;
	
	scanBoard(wp.pieces, bp.pieces, emptyBoard);
	printBoard(emptyBoard);
	
	promt(wp, emptyBoard);
	
	printBoard(emptyBoard);
	
	//emptyBoard(emptyBoard);
	
	//scanBoard(wp.pieces, bp.pieces, emptyBoard);
	//printBoard(emptyBoard);
	
	
}

void promt(Pieces p, char board[][8]){
	string from, to;
	cout << "From: ";
	cin >> from;
	cout << "To: ";
	cin >> to;
	cout << endl;
	
	Piece pieceToMove = (*p.pieceInSquare(from, board));
	
	if(&pieceToMove == NULL) {
		cout << "Nothing in " << from << " square" << endl;
		return;
	} 
	if(pieceToMove.color != p.color) {
		cout << "You cannot move the enemy pieces" << endl;
		return;
	}
	
	pieceToMove.move(to, board);
	
	
	
}
