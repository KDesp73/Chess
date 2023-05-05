#include <iostream>


#include "../Board/board_declarations.h"
#include "../Board/board.h"
#include "./game_logic.h"
#include "../Pieces/piece_declarations.h" 


void Game::start(string starting_fen){
	Board *board = new Board("white", starting_fen);
	board->printBigBoard();
	
	Game::gameLoop(board);
}

void Game::gameLoop(Board *board){
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

bool Game::turn(Pieces *p, Board *board){
	Move move = Game::prompt(p, board->board);
	if(sizeof(move) == 0) return false;

	bool moveMade = Game::makeGivenMove(move, p, board->board);
	if(moveMade)
		board->printBigBoard();

	return moveMade;
}

Move Game::prompt(Pieces* p, char board[][8]){
	string from, to;
	cout << "From: ";
	cin >> from;
	cout << "To: ";
	cin >> to;
	cout << endl;

	if(!isValidSquare(from) || !isValidSquare(to)) return {};
	
	return Move{from, to};
}

bool Game::makeGivenMove(Move move, Pieces *p, char board[][8]){
	Piece* pieceToMove = p->pieceInSquare(move.from, board);

	//Move checks
	if(pieceToMove == NULL) {
		cout << "Nothing in " << move.from << " square" << endl;
		return false;
	} 
	if(pieceToMove->color != p->color) {
		cout << "You cannot move the enemy pieces" << endl;
		return false;
	}
	
	return pieceToMove->move(move.to, board);
}

bool Game::isMate(char board[][8]){
	return false;
}

bool Game::isDraw(char board[][8]){
	return false;
}