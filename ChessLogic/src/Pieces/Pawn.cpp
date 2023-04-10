#include <cstdlib>
#include "../Board/board_declarations.h"

void Pawn::move(string to, char board[][8]){
	if(!isValidMove(to, board)) return;
	
	Piece::move(to, board);
}

bool Pawn::isValidMove(string to, char board[][8]){
	char file = currentSquare.at(0);
	int rank = currentSquare.at(1) - 48;
	
	cout << file << " " << rank << endl;
	
	char toFile = to.at(0);
	int toRank = to.at(1) - 48;
	
	cout << toFile << " " << toRank << endl;
	
	int* toCoords = translateSquare(to);
	
	if(currentSquare == to) return false;
	if(rank >= toRank) return false;
	if(file != toFile) return false; 
	if(board[*toCoords][*(toCoords+1)] != ' ') return false;
	if(rank == 2 || rank == 7){
		if(abs(rank-toRank) > 2) return false;
		else if((abs(rank-toRank) == 2) && (board[*toCoords-1][*(toCoords+1)] != ' ')) return false;
	} else {
		if(abs(rank-toRank) > 1) return false;
	}
	
	
	return true;
}

void Pawn::promote(char board[][8]){
	int promotionRank;
	if(color == "white")
		promotionRank = 8;
	else
		promotionRank = 1;

	int* currentCoords = translateSquare(this->currentSquare);
	if(currentCoords[0] != promotionRank-1) return;

	char promoteTo;
	do{
		cout << "Promote to (q, r, b, n): ";
		cin >> promoteTo;
		cout << endl;
	} while(promoteTo != 'q' && promoteTo != 'r' && promoteTo != 'b' && promoteTo != 'n');

	Piece* promoted;

	switch (promoteTo) {
	case 'q':
		promoted = new Queen(this->currentSquare, this->color);
		break;
	case 'r':
		promoted = new Rook(this->currentSquare, this->color);
		break;
	case 'b':
		promoted = new Bishop(this->currentSquare, this->color);
		break;
	case 'n':
		promoted = new Knight(this->currentSquare, this->color);
		break;
	default:
		return;
	}

	if(color == "white")
		board[currentCoords[0]][currentCoords[1]] = toupper(promoteTo);
	else
		board[currentCoords[0]][currentCoords[1]] = promoteTo;

	this->~Pawn();
}


