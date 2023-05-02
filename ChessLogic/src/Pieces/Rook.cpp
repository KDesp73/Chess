#include <cstdlib>

#include "../Board/board_declarations.h"
#include "piece_declarations.h"

bool Rook::move(string to, char board[][8]) {
    if (!isValidMove(to, board)) return false;

    Rook::hasMoved = true;

    return Piece::move(to, board);
}

bool Rook::isValidMove(string to, char board[][8]) {
    int* fromCoords = translateSquare(currentSquare);
    int* toCoords = translateSquare(to);

    int fromRow = fromCoords[0], fromCol = fromCoords[1], toRow = toCoords[0],
        toCol = toCoords[1];

	if(this->capturesOwnPiece(toCoords, board)) return false;

    if (fromRow == toRow) {
        // Moving horizontally
        int step = (toCol > fromCol) ? 1 : -1;
        for (int i = fromCol + step; i != toCol; i += step) {
            if (board[fromRow][i] != ' ') {
                return false;
            }
        }
        return true;
    } else if (fromCol == toCol) {
        // Moving vertically
        int step = (toRow > fromRow) ? 1 : -1;
        for (int i = fromRow + step; i != toRow; i += step) {
            if (board[i][fromCol] != ' ') {
                return false;
            }
        }
        return true;
    }
    return false;
}

vector<string> Rook::getValidMoves(char board[][8]){
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
