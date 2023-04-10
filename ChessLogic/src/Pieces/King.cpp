#include "piece_declarations.h"
#include "../Board/board_declarations.h"



void King::move(string to, char board[][8]){
	if(!isValidMove(to, board)) return;
	
	Piece::move(to, board);

}

bool King::isValidMove(string to, char board[][8]) {
	int* fromCoords = translateSquare(currentSquare);
	int* toCoords = translateSquare(to);

	int fromRow = fromCoords[0], fromCol = fromCoords[1], toRow = toCoords[0], toCol = toCoords[1];

	int rowDiff = abs(fromRow - toRow);
    int colDiff = abs(fromCol - toCol);

    // Check if the move is valid (1 square in any direction)
    if (rowDiff <= 1 && colDiff <= 1) {
        return true;
    }

    return false;
}
