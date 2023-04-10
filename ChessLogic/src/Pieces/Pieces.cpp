#include "piece_declarations.h"
#include "../Board/board_declarations.h"

#include <cctype>

void Pieces::printPieces(){
	for(int i=0; i< pieces.size(); i++){	
		pieces.at(i)->printPiece();
	}
	cout << endl;
}

Piece* Pieces::pieceInSquare(string square, char board[][8]){
	for(int i=0; i < pieces.size(); i++){
		if(pieces.at(i)->currentSquare == square) return pieces.at(i);
	}
	return NULL;
}

int Pieces::calculateMaterial(){
	if(pieces.size() == 0) return -1;

	int material = 0;
	for (int i = 0; i < pieces.size(); i++){
		material += pieces.at(i)->value;
	}

	return material;
}

Piece* returnPieceFromSquare(int x, int y, char board[][8]){
	string currentSquare;
	switch(board[x][y]){
		case 'p':
			return new Pawn(translateSquare(new int[2]{x, y}), "black");
			break;
		case 'P':
			return new Pawn(translateSquare(new int[2]{x, y}), "white");
			break;
		case 'r':
			return new Rook(translateSquare(new int[2]{x, y}), "black");
			break;
		case 'R':
			return new Rook(translateSquare(new int[2]{x, y}), "white");
			break;
		case 'n':
			return new Knight(translateSquare(new int[2]{x, y}), "black");
			break;
		case 'N':
			return new Knight(translateSquare(new int[2]{x, y}), "white");
			break;
		case 'b':
			return new Bishop(translateSquare(new int[2]{x, y}), "black");
			break;
		case 'B':
			return new Bishop(translateSquare(new int[2]{x, y}), "white");
			break;
		case 'q':
			return new Queen(translateSquare(new int[2]{x, y}), "black");
			break;
		case 'Q':
			return new Queen(translateSquare(new int[2]{x, y}), "white");
			break;
		case 'k':
			return new King(translateSquare(new int[2]{x, y}), "black");
			break;
		case 'K':
			return new King(translateSquare(new int[2]{x, y}), "white");
			break;
		default:
		return NULL;
			break;
	}

	return NULL;
}

void WhitePieces::loadPieces(char board[][8]){
	for (int i = 0; i < pieces.size(); i++) {
		for (int j = 0; i < pieces.size(); j++) {
			if(board[i][j] != ' ' && isupper(board[i][j]))
				this->pieces.push_back(returnPieceFromSquare(i, j, board));
		}
		
	}
	
}

void BlackPieces::loadPieces(char board[][8]){
	for (int i = 0; i < pieces.size(); i++) {
		for (int j = 0; i < pieces.size(); j++) {
			if(board[i][j] != ' ' && !isupper(board[i][j]))
				this->pieces.push_back(returnPieceFromSquare(i, j, board));
		}
		
	}
	
}