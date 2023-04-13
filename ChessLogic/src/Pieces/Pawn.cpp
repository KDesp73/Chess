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
	
	int* toCoords = translateSquare(to);

	int direction;
    if (this->color == "white") {
        direction = 1;
    } else {
        direction = -1;
    }
	
	if(currentSquare == to) return false;
	if(rank >= toRank) return false;
	if(file != toFile) return false; 
	if(board[toCoords[0]][toCoords[1]+direction] != ' ') return false;
	if(rank == 2 || rank == 7){
		if(abs(rank-toRank) > 2) return false;
		else if((abs(rank-toRank) == 2) && (board[toCoords[0]-1][toCoords[1]] != ' ')) return false;
	} else {
		if(abs(rank-toRank) > 1) return false;
	}
	
	
	return true;
}
/*
bool Pawn::isValidMove(string to, char board[][8]){
	int* fromCoords = translateSquare(currentSquare);
	int* toCoords = translateSquare(to);

	int fromRow = fromCoords[0], fromCol = fromCoords[1], toRow = toCoords[0], toCol = toCoords[1];


	int direction;
    if (this->color == "white") {
        direction = -1;
    } else {
        direction = 1;
    }
    // Check if the pawn is moving forward one or two squares
    if (toCol == fromCol && toRow == fromRow + direction) {
        if (board[toRow][toCol] == ' ') {
            return true;
        }
    } else if (toCol == fromCol && toRow == fromRow + 2 * direction && fromRow == (this->color == "white" ? 6 : 1)) {
        if (board[toRow][toCol] == ' ' && board[fromRow + direction][toCol] == ' ') {
            return true;
        }
    }
    // Check if the pawn is capturing an opponent's piece
    if (abs(toCol - fromCol) == 1 && toRow == fromRow + direction) {
        if (board[toRow][toCol] != ' ' && ((this->color == "white" && !isupper(board[toRow][toCol])) || (this->color == "black" && isupper(board[toRow][toCol])))) {
            return true;
        }
    }
    return false;
}
*/

bool Pawn::isValidCapture(string to, char board[][8]){
	int direction;
    if (this->color == "white") {
        direction = 1;
    } else {
        direction = -1;
    }

	int* fromCoords = translateSquare(currentSquare);
	int* toCoords = translateSquare(to);

	int fromRow = fromCoords[0], fromCol = fromCoords[1], toRow = toCoords[0], toCol = toCoords[1];


    // Check if the pawn is capturing an opponent's piece
    if (abs(toCol - fromCol) == 1 && toRow == fromRow + direction) {
        if (board[toRow][toCol] != '.' && ((this->color == "white" && !isupper(board[toRow][toCol])) || (this->color == "black" && isupper(board[toRow][toCol])))) {
            return true;
        }
    }
    return false;
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


bool Pawn::isLastRank(){
	return false;
}