#include "piece_declarations.h"

void Pieces::printPieces(){
	for(int i=0; i< 16; i++){	
		pieces[i].printPiece();
	}
	cout << endl;
}

Piece* Pieces::pieceInSquare(string square, char board[][8]){
	for(int i=0; i < 16; i++){
		if(pieces[i].currentSquare == square) return &pieces[i];
	}
	return NULL;
}
