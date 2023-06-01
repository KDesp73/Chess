#include <iostream>

#include "game_logic.h"

static Board *mainBoard;

void Game::start(string starting_fen){
	// Board *board = new Board("white", starting_fen);
	mainBoard = new Board("white", starting_fen);
	mainBoard->printBigBoard();
	
	Game::gameLoop(mainBoard);
	delete mainBoard;
}

void Game::gameLoop(Board *board){
	string playing = "white";
	do{
		board->moveFor = playing;
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

		// cout << "WhitePieces: " << endl;
		// board->wp->printPieces();
		// cout << endl << "BlackPieces: " << endl;
		// board->bp->printPieces();
	} while(!isMate(board->board) && !isDraw(board->board));
}

bool Game::turn(Pieces *p, Board *board){
	Move move = Game::prompt(p, board->board);
	if(sizeof(move) == 0) {
		return false;
	}
	bool moveMade = Board::movePiece(move, board);
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

	if(!isValidSquare(from) || !isValidSquare(to)) {
		cout << "Invalid squares" << endl;
		return {};
	}
	
	return Move{from, to};
}

bool Game::isMate(char board[][8]){
	return false;
}

bool Game::isDraw(char board[][8]){
	return false;
}