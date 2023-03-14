#include "piece_declarations.h"

void WhitePieces::printPieces(){
	for(int i=0; i< 16; i++){	
		whitePieces[i].printPiece();
	}
	cout << endl;
}
