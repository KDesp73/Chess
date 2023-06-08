#include <iostream>

#include "game_logic.h"
#include "../Pieces/Pieces.h"
#include "../Board/board.h"
#include "../Board/board_utils.h"


namespace GameUtils {
	Move prompt(Pieces* p, char board[][8]);
	bool turn(Pieces *p, Board *board);
	bool isMate(Board *board);
	bool isDraw(Board *board);
	void gameLoop(Board *board, string playing);
};




void Game::start(string starting_fen, string playing, bool showMaterial){
	Board mainBoard (starting_fen, playing, showMaterial);
	mainBoard.printBigBoard();
	
	GameUtils::gameLoop(&mainBoard, playing);
}

void GameUtils::gameLoop(Board *board, string playing){
	if(isMate(board)) return;

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
	} while(!GameUtils::isMate(board) && !GameUtils::isDraw(board));
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

bool GameUtils::isMate(Board *board){
	if(board->isInCheckmate(dynamic_cast<King *>(board->findPiece(Piece::KING, Piece::WHITE)))){
		cout << endl << "White is in checkmate" << endl << "Black Wins!" << endl;
		return true;
	} else if(board->isInCheckmate(dynamic_cast<King *>(board->findPiece(Piece::KING, Piece::BLACK)))){
		cout << endl << "Black is in checkmate" << endl << "White Wins!" << endl;
		return true;
	}

	return false;
}

bool GameUtils::isDraw(Board *board){
	if(board->isInStalemate(dynamic_cast<King *>(board->findPiece(Piece::KING, Piece::WHITE)))){
		cout << endl << "White is in stalemate" << endl << "It's a draw" << endl;
		return true;
	} else if(board->isInStalemate(dynamic_cast<King *>(board->findPiece(Piece::KING, Piece::BLACK)))){
		cout << endl << "Black is in stalemate" << endl << "It's a draw" << endl;
		return true;
	}

	return false;
}