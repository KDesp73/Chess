#include "piece_declarations.h"
#include "../Board/board_declarations.h"



bool Bishop::move(string to, char board[][8]){
	if(!isValidMove(to, board)) return false;
	
	return Piece::move(to, board);
}

bool Bishop::isValidMove(string to, char board[][8]) {
	int* fromCoords = translateSquare(currentSquare);
	int* toCoords = translateSquare(to);

	int fromRow = fromCoords[0], fromCol = fromCoords[1], toRow = toCoords[0], toCol = toCoords[1];

	if(this->capturesOwnPiece(toCoords, board)) return false;

	if (abs(fromRow - toRow) != abs(fromCol - toCol)) {
        // Moving diagonally
        return false;
    }
    int rowStep = (toRow > fromRow) ? 1 : -1;
    int colStep = (toCol > fromCol) ? 1 : -1;
    for (int i = fromRow + rowStep, j = fromCol + colStep; i != toRow && j != toCol; i += rowStep, j += colStep) {
        if (board[i][j] != ' ') {
            return false;
        }
    }
    return true;
}

vector<string> Bishop::getValidMoves(char board[][8]){
	char currentFile = currentSquare.at(0);
    int currentRank = currentSquare.at(1) - 48;

    vector<string> movesToCheck;

	// Check up and right
	char tempFile = currentFile;
	int tempRank = currentRank;
	while(tempFile < 'h' && tempRank < 8){
		tempFile++;
		tempRank++;
		movesToCheck.push_back(string(1, tempFile) + to_string(tempRank));
	}

	// Check up and left
	tempFile = currentFile;
	tempRank = currentRank;
	while(tempFile > 'a' && tempRank < 8){
		tempFile--;
		tempRank++;
		movesToCheck.push_back(string(1, tempFile) + to_string(tempRank));
	}

	// Check down and right
	tempFile = currentFile;
	tempRank = currentRank;
	while(tempFile < 'h' && tempRank > 1){
		tempFile++;
		tempRank--;
		movesToCheck.push_back(string(1, tempFile) + to_string(tempRank));
	}

	// Check down and left
	tempFile = currentFile;
	tempRank = currentRank;
	while(tempFile > 'a' && tempRank > 1){
		tempFile--;
		tempRank--;
		movesToCheck.push_back(string(1, tempFile) + to_string(tempRank));
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