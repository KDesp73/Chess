#include "board.h"
#include "board_utils.h"

#include <iostream>
#include <limits>

using namespace BoardUtils;

char Board::promoteTo(){
    char promoteTo = '-';
    do {
        printf("Promote to (q, r, b, n): ");
        cin >> promoteTo;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        printf("\n");
    } while (promoteTo != 'q' && promoteTo != 'r' && promoteTo != 'b' && promoteTo != 'n');

    return promoteTo;
}

bool Board::promotePawn(string square, Pawn *pawn, Board *board, char promoteTo){
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

    Piece* promoted;
    string color = pawn->color;
    Board::removePieceFreely(pawn->currentSquare, board);

    switch (promoteTo) {
        case 'q':
            promoted = new Queen(square, color);
            break;
        case 'r':
            promoted = new Rook(square, color);
            break;
        case 'b':
            promoted = new Bishop(square, color);
            break;
        case 'n':
            promoted = new Knight(square, color);
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

bool Board::castleKing(string square, King *king, Board *board){
    Coords fromCoords = translateSquare(king->currentSquare);
    Coords toCoords = translateSquare(square);

    int fromRow = fromCoords.x, fromCol = fromCoords.y;
    int toRow = toCoords.x, toCol = toCoords.y;

    int direction = toCol - fromCol;
    direction = (direction > 0) ? 1 : -1;

    Rook* wantedRook = BoardUtils::getRookToCastle(direction, king->color, board);

    if (wantedRook == NULL) return false;
    wantedRook->printPiece();

    // Castle
    Board::moveFreely(Move{king->currentSquare, square}, board);
    string targetRookSquare = translateSquare(Coords{toCoords.x, toCoords.y - direction});
    Board::moveFreely(Move{wantedRook->currentSquare, targetRookSquare}, board);

    return true;
}

bool Board::enpassantPawn(string square, Pawn *pawn, Board *board){
    char toFile = square.at(0);
    int toRank = square.at(1) - 48;

    int direction = (pawn->color == Piece::WHITE) ? 1 : -1;    

    Board::moveFreely(Move{pawn->currentSquare, square}, board);
    string squareToRemove = string(1, toFile) + to_string(toRank - direction);
    return Board::removePieceFreely(squareToRemove, board);
}