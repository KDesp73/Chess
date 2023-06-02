#include "board_utils.h"
#include "board_declarations.h"


bool BoardUtils::canMove(Piece *piece, Move move, Board *board) {
    if(!BoardUtils::canKingCapturePiece(piece, move, board)) return false;

    return piece != NULL && piece->isValidMove(move.to, board->board);
}

bool BoardUtils::canMove(string color, Move move, Board *board) {
    Pieces *pieces = (color == "white") ? board->wp : board->bp;
    for (int i = 0; i < pieces->pieces.size(); i++)    {
        if(BoardUtils::canMove(pieces->pieces.at(i), move, board)) return true;
    }
    return false;
}

bool BoardUtils::contains(vector<string> moves, string move){
    for (int i = 0; i < moves.size(); i++){
        if(moves.at(i) == move) return true;
    }
    return false;
}

bool BoardUtils::kingWantsToCastle(Move move){
    Coords fromCoords = translateSquare(move.from);
    Coords toCoords = translateSquare(move.to);

    int fromRow = fromCoords.x, fromCol = fromCoords.y;
    int toRow = toCoords.x, toCol = toCoords.y;

    return abs(fromCol - toCol) == 2;
}

int BoardUtils::calcDirection(King *king, string square){
    Coords fromCoords = translateSquare(king->currentSquare);
    Coords toCoords = translateSquare(square);

    int fromRow = fromCoords.x, fromCol = fromCoords.y;
    int toRow = toCoords.x, toCol = toCoords.y;

    int direction = toCol - fromCol;
    direction = (direction > 0) ? 1 : -1;

    return direction;
}

bool BoardUtils::canKingCapturePiece(Piece *piece, Move move, Board *board){
    King *king = dynamic_cast<King *>(piece);
    Piece *pieceToCapture = NULL;
    if(king != NULL){
        // Search white for pieces
        for (int i = 0; i < board->wp->pieces.size(); i++) {
            if (move.to == board->wp->pieces.at(i)->currentSquare) {
                pieceToCapture = board->wp->pieces.at(i);
            }
        }

        // Search black for pieces
        if(pieceToCapture == NULL){
            for (int i = 0; i < board->bp->pieces.size(); i++) {
                if (move.to == board->bp->pieces.at(i)->currentSquare) {
                    pieceToCapture = board->bp->pieces.at(i);
            }
        }
        }

        if(pieceToCapture != NULL && Board::isProtected(pieceToCapture, board)) return false;
        return true;
    }

    return false;
}