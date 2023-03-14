#include "piece_declarations.h"

void Pieces::printPieces(){
	for(int i=0; i< 16; i++){	
		pieces[i].printPiece();
	}
	cout << endl;
}
