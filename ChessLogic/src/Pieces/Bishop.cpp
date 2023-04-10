#include "piece_declarations.h"
#include "../Board/board_declarations.h"



void Bishop::move(string to, char board[][8]){
	if(!isValidMove(to, board)) return;
	
	Piece::move(to, board);

}

bool Bishop::isValidMove(string to, char board[][8]) {
	int* fromCoords = translateSquare(currentSquare);
	int* toCoords = translateSquare(to);

	int fromRow = fromCoords[0], fromCol = fromCoords[1], toRow = toCoords[0], toCol = toCoords[1];


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
