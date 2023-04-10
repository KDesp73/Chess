#include "piece_declarations.h"
#include "../Board/board_declarations.h"
#include <cstdlib>


void Rook::move(string to, char board[][8]){
	if(!isValidMove(to, board)) return;
	
	Piece::move(to, board);

}

bool Rook::isValidMove(string to, char board[][8]){
	int* fromCoords = translateSquare(currentSquare);
	int* toCoords = translateSquare(to);

	int fromRow = fromCoords[0], fromCol = fromCoords[1], toRow = toCoords[0], toCol = toCoords[1];

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