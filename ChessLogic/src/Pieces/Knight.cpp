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
    if ((rowDiff == 1 && colDiff == 2) || (rowDiff == 2 && colDiff == 1)) {
        // Moving in an L-shape
        return true;
    }
    return false;
}
