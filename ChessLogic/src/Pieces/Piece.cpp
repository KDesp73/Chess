#include "../Board/board_declarations.h"
#include "piece_declarations.h"


void Piece::move(string to, char board[][8]){
	makeMove(currentSquare, to, board);
	
	currentSquare = to;
}

void Piece::printPiece(){
	cout << this->boardChar << " " << this->color << " " << this->currentSquare << endl;
}