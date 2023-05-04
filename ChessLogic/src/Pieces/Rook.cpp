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
	char currentFile = currentSquare.at(0);
    int currentRank = currentSquare.at(1) - 48;

    vector<string> movesToCheck;

    
    // Check same rank left
    char tempFile = currentFile;
    while(tempFile > 'a'){
        tempFile--;
        movesToCheck.push_back(string(1, tempFile) + to_string(currentRank));
    }


    // Check same rank right
    tempFile = currentFile;
    while(tempFile < 'h'){
        tempFile++;
        movesToCheck.push_back(string(1, tempFile) + to_string(currentRank));
    }


    // Check same file up
    int tempRank = currentRank;
    while(tempRank < 8){
        tempRank++;
        movesToCheck.push_back(string(1, currentFile) + to_string(tempRank));
    }
    
    // Check same file down
    tempRank = currentRank;
    while(tempRank > 1){
        tempRank--;
        movesToCheck.push_back(string(1, currentFile) + to_string(tempRank));
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
