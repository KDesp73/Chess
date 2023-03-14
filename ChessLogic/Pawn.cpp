
#include "declarations.h"

void Pawn::move(string to, char board[][8]){
	if(!isValidMove(to, board)) return;
	
	Piece::move(to, board);
}

bool Pawn::isValidMove(string to, char board[][8]){
	cout << "isValidMove"<<endl;
	char file = currentSquare.at(0);
	int rank = currentSquare.at(1) - 48;
	
	cout << file << " " << rank << endl;
	
	char toFile = to.at(0);
	int toRank = to.at(1) - 48;
	
	cout << toFile << " " << toRank << endl;
	
	int* toCoords = translateSquare(to);
	
	if(rank >= toRank) return false;
	if(file != toFile) return false; 
	if(board[*toCoords][*(toCoords+1)] != ' ') return false;
	
	
	return true;
}


