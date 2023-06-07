#include <iostream>

#include "game_logic.h"
#include "../Pieces/Pieces.h"
#include "../Board/board.h"
#include "../Board/board_utils.h"


namespace GameUtils {
	Move prompt(Pieces* p, char board[][8]);
	bool turn(Pieces *p, Board *board);
	bool isMate(char board[][8]);
	bool isDraw(char board[][8]);
	void gameLoop(Board *board);
};




void Game::start(string starting_fen){
	Board *mainBoard = new Board("white", starting_fen);
	mainBoard = new Board("white", starting_fen);
	mainBoard->printBigBoard();
	
	GameUtils::gameLoop(mainBoard);
	delete mainBoard;
}

void GameUtils::gameLoop(Board *board){
	string playing = "white";
	do{
		board->moveFor = playing;
		if(playing == "white"){
			cout << "White's turn" << endl;

			bool moveMade = GameUtils::turn(board->getPieces(Piece::WHITE), board);
			if(moveMade)
				playing = "black";
		} else {
			cout << "Black's turn" << endl;
			bool moveMade = GameUtils::turn(board->getPieces(Piece::BLACK), board);
			if(moveMade)
				playing = "white";
		}
	} while(!GameUtils::isMate(board->board) && !GameUtils::isDraw(board->board));
}

bool GameUtils::turn(Pieces *p, Board *board){
	Move move = GameUtils::prompt(p, board->board);
	if(sizeof(move) == 0) {
		return false;
	}
	bool moveMade = Board::movePiece(move, board);
	if(moveMade)
		board->printBigBoard();

	return moveMade;
}

Move GameUtils::prompt(Pieces* p, char board[][8]){
	string from, to;
	cout << "From: ";
	cin >> from;
	cout << "To: ";
	cin >> to;
	cout << endl;

	if(!BoardUtils::isValidSquare(from) || !BoardUtils::isValidSquare(to)) {
		cout << "Invalid squares" << endl;
		return {};
	}
	
	return Move{from, to};
}

bool GameUtils::isMate(char board[][8]){
	return false;
}

bool GameUtils::isDraw(char board[][8]){
	return false;
}