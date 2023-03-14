#include "piece_declarations.h"

void BlackPieces::printPieces(){
	for(int i=0; i<16; i++){	
		blackPieces[i].printPiece();
	}
	cout << endl;
}
