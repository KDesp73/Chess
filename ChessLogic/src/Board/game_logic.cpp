#include <iostream>


#include "./board_declarations.h"
#include "./game_logic.h"
#include "./notation.h"
#include "../Pieces/piece_declarations.h" 


void start(string starting_fen){
	char board[][8] = {
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
	string *move;

	importFEN(starting_fen, board);
	wp->loadPieces(board);
	bp->loadPieces(board);

	printBoard(board);

	move = prompt(wp, board);
	makeGivenMove(move[0], move[1], wp, board);
	free(move);
	
	printBoard(board);

	move = prompt(bp, board);
	makeGivenMove(move[0], move[1], bp, board);
	free(move);
	
	printBoard(board);


}

string* prompt(Pieces* p, char board[][8]){
	string from, to;
	cout << "From: ";
	cin >> from;
	cout << "To: ";
	cin >> to;
	cout << endl;
	
	return new string[2]{from, to};
}

void makeGivenMove(string from, string to, Pieces *p, char board[][8]){
	Piece* pieceToMove = p->pieceInSquare(from, board);
	
	if(&pieceToMove == NULL) {
		cout << "Nothing in " << from << " square" << endl;
		return;
	} 
	if(pieceToMove->color != p->color) {
		cout << "You cannot move the enemy pieces" << endl;
		return;
	}
	
	pieceToMove->move(to, board);
}
