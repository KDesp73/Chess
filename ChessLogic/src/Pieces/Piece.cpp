#include "../Board/board_declarations.h"
#include "piece_declarations.h"



void Piece::printPiece(){
	cout << this->toString() << endl;
}

string Piece::toString(){
	return this->type + " " + this->color + " " + this->currentSquare;
}

bool Piece::capturesOwnPiece(Coords toCoords, char board[][8]){
	return (isupper(board[toCoords.x][toCoords.y]) && this->color == "white") || (islower(board[toCoords.x][toCoords.y]) && this->color == "black");
}

