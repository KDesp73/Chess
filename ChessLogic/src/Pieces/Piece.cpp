#include "../Board/board_declarations.h"
#include "piece_declarations.h"


bool Piece::move(string to, char board[][8]){
	bool moveMade = makeMove(currentSquare, to, board);
	if(moveMade)
		currentSquare = to;

	return moveMade;
}

void Piece::moveFreely(string to, char board[][8]){
	bool moveMade = makeMove(currentSquare, to, board);
	if(moveMade)
		currentSquare = to;
}

void Piece::printPiece(){
	cout << this->boardChar << " " << this->color << " " << this->currentSquare << endl;
}

bool Piece::capturesOwnPiece(int *toCoords, char board[][8]){
	return (isupper(board[toCoords[0]][toCoords[1]]) && this->color == "white") || (islower(board[toCoords[0]][toCoords[1]]) && this->color == "black");
}