#include <iostream>


#include "./board_declarations.h"
#include "../Pieces/piece_declarations.h" 


void start(){
	char board[][8] = {
		{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
		{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
		{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
	};

	char empty_board[][8] = {
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
	};
	
	Pieces* wp = new WhitePieces();
	Pieces* bp = new BlackPieces();
	
	
	printBoard(empty_board);
	//scanBoard(wp->pieces, bp->pieces, empty_board);
	printBoard(empty_board);
	
	promt(wp, empty_board);
	
	printBoard(empty_board);
	

	emptyBoard( empty_board );
	
	scanBoard(wp->pieces, bp->pieces, empty_board);
	printBoard(empty_board);
	
	
}

void promt(Pieces* p, char board[][8]){
	string from, to;
	cout << "From: ";
	cin >> from;
	cout << "To: ";
	cin >> to;
	cout << endl;
	
	Piece pieceToMove = *(p->pieceInSquare(from, board));
	
	if(&pieceToMove == NULL) {
		cout << "Nothing in " << from << " square" << endl;
		return;
	} 
	if(pieceToMove.color != p->color) {
		cout << "You cannot move the enemy pieces" << endl;
		return;
	}
	
	pieceToMove.move(to, board);
}
