#include "board.h"
#include "board_utils.h"

using namespace BoardUtils;

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

bool Board::castleKing(string square, King *king, Board *board){
    Coords fromCoords = translateSquare(king->currentSquare);
    Coords toCoords = translateSquare(square);

    int fromRow = fromCoords.x, fromCol = fromCoords.y;
    int toRow = toCoords.x, toCol = toCoords.y;

    int direction = toCol - fromCol;
    direction = (direction > 0) ? 1 : -1;

    Rook* wantedRook = board->getRookToCastle(direction, king->color);

    if (wantedRook == NULL) return false;
    wantedRook->printPiece();

    // Castle
    Board::moveFreely(Move{king->currentSquare, square}, board);
    string targetRookSquare = translateSquare(Coords{toCoords.x, toCoords.y - direction});
    Board::moveFreely(Move{wantedRook->currentSquare, targetRookSquare}, board);

    return true;
}

Rook* Board::getRookToCastle(int direction, string color) {
    Piece* wantedRook;
    if (direction > 0 && color == "white") {
        wantedRook = this->findPiece(Coords{0, 7});
    } else if (direction < 0 && color == "white") {
        wantedRook = this->findPiece(Coords{0, 0});
    } else if (direction > 0 && color == "black") {
        wantedRook = this->findPiece(Coords{7, 7});
    } else if (direction < 0 && color == "black") {
        wantedRook = this->findPiece(Coords{7, 0});
    } else {
        cout << "Something went wrong" << endl;
    }

    return dynamic_cast<Rook*>(wantedRook);
}

bool Board::enpassantPawn(string square, Pawn *pawn, Board *board){
    char toFile = square.at(0);
    int toRank = square.at(1) - 48;

    int direction = (pawn->color == Piece::WHITE) ? 1 : -1;    

    Board::moveFreely(Move{pawn->currentSquare, square}, board);
    string squareToRemove = string(1, toFile) + to_string(toRank - direction);
    return Board::removePieceFreely(squareToRemove, board);
}