#include "piece_declarations.h"
#include "../Board/board_declarations.h"



bool Queen::move(string to, char board[][8]){
	if(!isValidMove(to, board)) return false;
	
	return Piece::move(to, board);
}

bool Queen::isValidMove(string to, char board[][8]) {
	int* fromCoords = translateSquare(currentSquare);
	int* toCoords = translateSquare(to);

	int fromRow = fromCoords[0], fromCol = fromCoords[1], toRow = toCoords[0], toCol = toCoords[1];

	int rowDiff = abs(fromRow - toRow);
    int colDiff = abs(fromCol - toCol);

	if(this->capturesOwnPiece(toCoords, board)) return false;

    // Check if the move is valid for the bishop (diagonal movement)
    if (rowDiff == colDiff) {
        int rowStep = (toRow > fromRow) ? 1 : -1;
        int colStep = (toCol > fromCol) ? 1 : -1;
        int i = fromRow + rowStep;
        int j = fromCol + colStep;
        while (i != toRow && j != toCol) {
            if (board[i][j] != ' ') {
                return false;
            }
            i += rowStep;
            j += colStep;
        }
        return true;
    }

    // Check if the move is valid for the rook (horizontal/vertical movement)
    if (fromRow == toRow) {
        int colStep = (toCol > fromCol) ? 1 : -1;
        int j = fromCol + colStep;
        while (j != toCol) {
            if (board[fromRow][j] != ' ') {
                return false;
            }
            j += colStep;
        }
        return true;
    }
    if (fromCol == toCol) {
        int rowStep = (toRow > fromRow) ? 1 : -1;
        int i = fromRow + rowStep;
        while (i != toRow) {
            if (board[i][fromCol] != ' ') {
                return false;
            }
            i += rowStep;
        }
        return true;
    }

    return false;
}

vector<string> Queen::getValidMoves(char board[][8]){
	vector<string> ret;
	string letters = "abcdefgh";

	string moveToCheck;
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			moveToCheck = letters[i] + to_string((j+1));

			if(this->isValidMove(moveToCheck, board)){
				ret.push_back(moveToCheck);
			}

		}	
	}
	return ret;
}