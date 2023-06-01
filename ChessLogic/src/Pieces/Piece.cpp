#include "../Board/board_declarations.h"
#include "piece_declarations.h"



void Piece::printPiece(){
	cout << this->boardChar << " " << this->color << " " << this->currentSquare << endl;
}

bool Piece::capturesOwnPiece(Coords toCoords, char board[][8]){
	return (isupper(board[toCoords.x][toCoords.y]) && this->color == "white") || (islower(board[toCoords.x][toCoords.y]) && this->color == "black");
}