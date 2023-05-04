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
	char currentFile = currentSquare.at(0);
    int currentRank = currentSquare.at(1) - 48;

    

	vector<string> movesToCheck = {
		string(1, currentFile+1) + to_string(currentRank+2),
		string(1, currentFile-1) + to_string(currentRank+2),
		string(1, currentFile+1) + to_string(currentRank-2),
		string(1, currentFile-1) + to_string(currentRank-2),
		string(1, currentFile+2) + to_string(currentRank+1),
		string(1, currentFile+2) + to_string(currentRank-1),
		string(1, currentFile-2) + to_string(currentRank+1),
		string(1, currentFile-2) + to_string(currentRank-1),
	};

	// Filter invalid squares
    for (int i = 0; i < movesToCheck.size(); i++) {
        if (!isValidSquare(movesToCheck.at(i))) {
            movesToCheck.erase(movesToCheck.begin() + i);  // erase from vector
            i--;
        }
    }

    // Filter invalid moves
    for (int i = 0; i < movesToCheck.size(); i++) {
        if(!this->isValidMove(movesToCheck.at(i), board)){
            movesToCheck.erase(movesToCheck.begin() + i);  // erase from vector
            i--;
        }
    }

    return movesToCheck;
}