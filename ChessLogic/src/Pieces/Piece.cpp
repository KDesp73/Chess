#include "../Board/board_declarations.h"
#include "piece_declarations.h"


bool Piece::move(string to, char board[][8]){
	bool moveMade = makeMove(currentSquare, to, board);
	if(moveMade)
		currentSquare = to;

	return moveMade;
}

void Piece::printPiece(){
	cout << this->boardChar << " " << this->color << " " << this->currentSquare << endl;
}