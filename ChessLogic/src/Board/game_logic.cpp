#include <iostream>


#include "./board_declarations.h"
#include "board.h"
#include "./game_logic.h"
#include "../Pieces/piece_declarations.h" 


void start(string starting_fen){
	Board *board = new Board("white", starting_fen);
	board->printBigBoard();
	
	gameLoop(board);
}

void gameLoop(Board *board){
	string playing = "white";
	do{
		if(playing == "white"){
			cout << "White's turn" << endl;

			bool moveMade = turn(board->wp, board);
			if(moveMade)
				playing = "black";
		} else {
			cout << "Black's turn" << endl;
			bool moveMade = turn(board->bp, board);
			if(moveMade)
				playing = "white";
		}
	} while(!isMate(board->board) && !isDraw(board->board));
}

bool turn(Pieces *p, Board *board){
	string *move = prompt(p, board->board);
	if(move == NULL) return false;

	bool moveMade = makeGivenMove(move, p, board->board);
	if(moveMade)
		board->printBigBoard();

	return moveMade;
}

string* prompt(Pieces* p, char board[][8]){
	string from, to;
	cout << "From: ";
	cin >> from;
	cout << "To: ";
	cin >> to;
	cout << endl;

	if(!isValidSquare(from) || !isValidSquare(to)) return NULL;
	
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