#include "piece_declarations.h"
#include "declarations.h"



void Knight::move(string to, char board[][8]){
	if(!isValidMove(to, board)) return;
	
	Piece::move(to, board);

}

bool Knight::isValidMove(string to, char board[][8]) {
	char file = currentSquare.at(0);
	int rank = currentSquare.at(1) - 48;
	
	cout << file << " " << rank << endl;
	
	char toFile = to.at(0);
	int toRank = to.at(1) - 48;
	
	cout << toFile << " " << toRank << endl;
	
	int* toCoords = translateSquare(to);
	
	// checks
	
	return true;
}
