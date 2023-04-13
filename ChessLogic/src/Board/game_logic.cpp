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

	gameLoop(wp, bp, board);
}

void gameLoop(Pieces *wp, Pieces *bp, char board[][8]){
	string playing = "white";
	do{
		//check for draw and mate
		if(playing == "white"){
			cout << "White's turn" << endl;
			turn(wp, board);
			playing = "black";
		} else {
			cout << "Black's turn" << endl;
			turn(bp, board);
			playing = "white";
		}
	} while(!isMate(board) && !isDraw(board));
}

void turn(Pieces *p, char board[][8]){
	string *move = prompt(p, board);
	makeGivenMove(move, p, board);
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

void makeGivenMove(string *move, Pieces *p, char board[][8]){
	Piece* pieceToMove = p->pieceInSquare(move[0], board);

	if(&pieceToMove == NULL) {
		cout << "Nothing in " << move[0] << " square" << endl;
		return;
	} 
	if(pieceToMove->color != p->color) {
		cout << "You cannot move the enemy pieces" << endl;
		return;
	}
	
	pieceToMove->move(move[1], board);
}

bool isMate(char board[][8]){
	return false;
}

bool isDraw(char board[][8]){
	return false;
}