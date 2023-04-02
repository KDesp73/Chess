#include "board_declarations.h"
#include "piece_declarations.h"


void Piece::move(string to, char board[][8]){
	makeMove(currentSquare, to, board);
	
	currentSquare = to;
}

void Piece::printPiece(){
	cout << boardChar << " " << color << " " << currentSquare << endl;
}
