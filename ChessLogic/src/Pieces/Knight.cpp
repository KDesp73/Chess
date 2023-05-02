#include "piece_declarations.h"
#include "../Board/board_declarations.h"



bool Knight::move(string to, char board[][8]){
	if(!isValidMove(to, board)) return false;
	
	return Piece::move(to, board);
}

bool Knight::isValidMove(string to, char board[][8]) {
	int* fromCoords = translateSquare(currentSquare);
	int* toCoords = translateSquare(to);

	int fromRow = fromCoords[0], fromCol = fromCoords[1], toRow = toCoords[0], toCol = toCoords[1];
	
	int rowDiff = abs(fromRow - toRow);
    int colDiff = abs(fromCol - toCol);

	if(this->capturesOwnPiece(toCoords, board)) return false;

    if ((rowDiff == 1 && colDiff == 2) || (rowDiff == 2 && colDiff == 1)) {
        // Moving in an L-shape
        return true;
    }
    return false;
}

vector<string> Knight::getValidMoves(char board[][8]){
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