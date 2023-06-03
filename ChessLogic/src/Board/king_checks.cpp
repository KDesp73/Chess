#include "board.h"
#include "board_declarations.h"
#include "board_utils.h"

bool Board::isInCheckmate(King *king) {
    vector<Piece *> piecesThatCheckTheKing = king->isInCheck(this->board);

    if (piecesThatCheckTheKing.empty()) return false;

    if (!king->getValidMoves(this->board).empty()) return false;

    if (piecesThatCheckTheKing.size() > 1) return true;

    // Check if piece that checks the king can be captured
    if(BoardUtils::canMove(king->color, piecesThatCheckTheKing.at(0)->currentSquare, this)) {
        return false;
    }

    // Check if check can be blocked
    Pawn *pawn = dynamic_cast<Pawn *>(piecesThatCheckTheKing.at(0));
    Rook *rook = dynamic_cast<Rook *>(piecesThatCheckTheKing.at(0));
    Knight *knight = dynamic_cast<Knight *>(piecesThatCheckTheKing.at(0));
    Bishop *bishop = dynamic_cast<Bishop *>(piecesThatCheckTheKing.at(0));
    Queen *queen = dynamic_cast<Queen *>(piecesThatCheckTheKing.at(0));

    if (knight != NULL) return true;
    if (pawn != NULL) return true;

    if (rook != NULL) {
        Coords rookCoords = translateSquare(rook->currentSquare);
        Coords kingCoords = translateSquare(king->currentSquare);

        int rookRow = rookCoords.x, rookCol = rookCoords.y;
        int kingRow = kingCoords.x, kingCol = kingCoords.y;

        string letters = "abcdefgh";

        if (rookRow == kingRow) {
            for (int i = 1; i <= abs(rookCol - kingCol); i++) {
                string squareToCheck = letters[i] + to_string(rookRow + 1);
                if (BoardUtils::canMove(king->color, squareToCheck, this))
                    return true;
            }
        } else if (rookCol == kingCol) {
            for (int i = 1; i <= abs(rookRow - kingRow); i++) {
                string squareToCheck = letters[rookCol - 1] + to_string(i + 1);
                if (BoardUtils::canMove(king->color, squareToCheck, this))
                    return true;
            }
        }
    }

    if (bishop != NULL){
        Coords bishopCoords = translateSquare(bishop->currentSquare);
        Coords kingCoords = translateSquare(king->currentSquare);

        int bishopRow = bishopCoords.x, bishopCol = bishopCoords.y;
        int kingRow = kingCoords.x, kingCol = kingCoords.y;

        int rowDiff = bishopRow - kingRow;
        int colDiff = bishopCol - kingCol;

        string letters = "abcdefgh";

        if(rowDiff > 0 && colDiff > 0){
            for (int i = 1; i <= abs(rowDiff); i++){
                string squareToCheck = letters[bishopCoords.y - i] + to_string(bishopCoords.x + 1 - i);
                if (BoardUtils::canMove(king->color, squareToCheck, this))
                    return true;
            }
        } else if(rowDiff < 0 && colDiff > 0){
            for (int i = 1; i <= abs(rowDiff); i++){
                string squareToCheck = letters[bishopCoords.y - i] + to_string(bishopCoords.x + 1 + i);
                if (BoardUtils::canMove(king->color, squareToCheck, this))
                    return true;
            }
        } else if(rowDiff > 0 && colDiff < 0){
            for (int i = 1; i <= abs(rowDiff); i++){
                string squareToCheck = letters[bishopCoords.y + i] + to_string(bishopCoords.x + 1 - i);
                if (BoardUtils::canMove(king->color, squareToCheck, this))
                    return true;
            }
        } else if(rowDiff < 0 && colDiff < 0){
            for (int i = 1; i <= abs(rowDiff); i++){
                string squareToCheck = letters[bishopCoords.y + i] + to_string(bishopCoords.x + 1 + i);
                if (BoardUtils::canMove(king->color, squareToCheck, this))
                    return true;
            }
        }
    }

    if(queen != NULL){ 
        Coords queenCoords = translateSquare(queen->currentSquare);
        Coords kingCoords = translateSquare(king->currentSquare);

        int queenRow = queenCoords.x, queenCol = queenCoords.y;
        int kingRow = kingCoords.x, kingCol = kingCoords.y;

        int rowDiff = queenRow - kingRow;
        int colDiff = queenCol - kingCol;

        string letters = "abcdefgh";

        // Rook check
        if (queenRow == kingRow) {
            int direction = (colDiff < 0) ? 1 : -1;
            for (int i = 1; i < abs(queenCol - kingCol); i++) {
                string squareToCheck = letters[queenCol + i*direction] + to_string(queenRow + 1);
                if (BoardUtils::canMove(king->color, squareToCheck, this))
                    return true;
            }
        } else if (queenCol == kingCol) {
            int direction = (rowDiff < 0) ? 1 : -1;
            for (int i = 1; i < abs(queenRow - kingRow); i++) {
                string squareToCheck = letters[queenCol - 1] + to_string(queenRow - 1 + i*direction);
                if (BoardUtils::canMove(king->color, squareToCheck, this))
                    return true;
            }
        } else {
            // Bishop check
            if(abs(colDiff) != abs(rowDiff)) return false;
            if(rowDiff > 0 && colDiff > 0){
                for (int i = 1; i <= abs(rowDiff); i++){
                    string squareToCheck = letters[queenCoords.y - i] + to_string(queenCoords.x + 1 - i);
                    if (BoardUtils::canMove(king->color, squareToCheck, this))
                    return true;
                }
            } else if(rowDiff < 0 && colDiff > 0){
                for (int i = 1; i <= abs(rowDiff); i++){
                    string squareToCheck = letters[queenCoords.y - i] + to_string(queenCoords.x + 1 + i);
                    if (BoardUtils::canMove(king->color, squareToCheck, this))
                    return true;
                }
            } else if(rowDiff > 0 && colDiff < 0){
                for (int i = 1; i <= abs(rowDiff); i++){
                    string squareToCheck = letters[queenCoords.y + i] + to_string(queenCoords.x + 1 - i);
                    if (BoardUtils::canMove(king->color, squareToCheck, this))
                    return true;
                }
            } else if(rowDiff < 0 && colDiff < 0){
                for (int i = 1; i <= abs(rowDiff); i++){
                    string squareToCheck = letters[queenCoords.y + i] + to_string(queenCoords.x + 1 + i);
                    if (BoardUtils::canMove(king->color, squareToCheck, this))
                    return true;
                }
            }
        }
    }

    return true;
}

bool Board::isInStalemate(King *king) { return false; }

