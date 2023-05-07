#include "../Board/board_declarations.h"
#include "piece_declarations.h"


bool Piece::move(string to, char board[][8]){
	bool moveMade = makeMove(currentSquare, to, board);
	if(moveMade)
		currentSquare = to;

	return moveMade;
}
/*
bool Piece::move(string to, Board board){
	bool moveMade = makeMove(currentSquare, to, board.board);
	if(moveMade)
		currentSquare = to;

	int* toCoords = translateSquare(to);
	if(board.board[toCoords[0]][toCoords[1]] != ' '){
		if(this->color == "white"){
			// board.wp->pieces.erase(board.wp->pieces.begin(), board.wp->pieces.)
			board.bp->pieceInSquare(to, board.board)->~Piece();
		} else {
			board.wp->pieceInSquare(to, board.board)->~Piece();
		}
	}

	return moveMade;
}*/

void Piece::moveFreely(string to, char board[][8]){
	bool moveMade = makeMove(currentSquare, to, board);
	if(moveMade)
		currentSquare = to;
}

void Piece::printPiece(){
	cout << this->boardChar << " " << this->color << " " << this->currentSquare << endl;
}

bool Piece::capturesOwnPiece(Coords toCoords, char board[][8]){
	return (isupper(board[toCoords.x][toCoords.y]) && this->color == "white") || (islower(board[toCoords.x][toCoords.y]) && this->color == "black");
}