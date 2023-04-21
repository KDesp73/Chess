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

	importFEN(starting_fen, board);
	wp->loadPieces(board);
	bp->loadPieces(board);

	printBigBoard(board);
	
	gameLoop(wp, bp, board);
}

void gameLoop(Pieces *wp, Pieces *bp, char board[][8]){
	string playing = "white";
	do{
		if(playing == "white"){
			cout << "White's turn" << endl;

			bool moveMade = turn(wp, board);
			if(moveMade)
				playing = "black";
		} else {
			cout << "Black's turn" << endl;
			bool moveMade = turn(bp, board);
			if(moveMade)
				playing = "white";
		}
	} while(!isMate(board) && !isDraw(board));
}

bool turn(Pieces *p, char board[][8]){
	string *move = prompt(p, board);
	bool moveMade = makeGivenMove(move, p, board);
	if(moveMade)
		printBigBoard(board);

	return moveMade;
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

bool makeGivenMove(string *move, Pieces *p, char board[][8]){
	Piece* pieceToMove = p->pieceInSquare(move[0], board);

	//Move checks
	if(pieceToMove == NULL) {
		cout << "Nothing in " << move[0] << " square" << endl;
		return false;
	} 
	if(pieceToMove->color != p->color) {
		cout << "You cannot move the enemy pieces" << endl;
		return false;
	}
	
	return pieceToMove->move(move[1], board);
}

bool isMate(char board[][8]){
	return false;
}

bool isDraw(char board[][8]){
	return false;
}