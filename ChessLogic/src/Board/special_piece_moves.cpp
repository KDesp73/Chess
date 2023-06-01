#include "board.h"
#include "board_declarations.h"

bool Board::promotePawn(string square, Pawn *pawn, Board *board){
    int promotionRank, direction;
    if (pawn->color == "white") {
        promotionRank = 7;
        direction = 1;
    } else{
        promotionRank = 0;
        direction = -1;

    }

    Coords currentCoords = translateSquare(pawn->currentSquare);
    if (currentCoords.x != promotionRank - direction) return false;

    char promoteTo;
    do {
        cout << "Promote to (q, r, b, n): ";
        cin >> promoteTo;
        cout << endl;
    } while (promoteTo != 'q' && promoteTo != 'r' && promoteTo != 'b' &&
             promoteTo != 'n');

    Piece* promoted;

    Board::removePieceFreely(pawn->currentSquare, board);

    switch (promoteTo) {
        case 'q':
            promoted = new Queen(square, pawn->color);
            break;
        case 'r':
            promoted = new Rook(square, pawn->color);
            break;
        case 'b':
            promoted = new Bishop(square, pawn->color);
            break;
        case 'n':
            promoted = new Knight(square, pawn->color);
            break;
        default:
            return false;
    }

    if (pawn->color == "white"){
        board->wp->pieces.push_back(promoted);
        board->board[translateSquare(square).x][translateSquare(square).y] = toupper(promoteTo);
    }
    else {
        board->bp->pieces.push_back(promoted);
        board->board[translateSquare(square).x][translateSquare(square).y] = promoteTo;
    }

    return true;
}