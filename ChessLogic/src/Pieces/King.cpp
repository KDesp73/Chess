#include <algorithm>

#include "../Board/board.h"
#include "../Board/board_declarations.h"
#include "piece_declarations.h"

using namespace std;

bool King::move(string to, char board[][8]) {
    if (!isValidMove(to, board)) return false;

    King::hasMoved = true;

    // in case of castling //
    int* fromCoords = translateSquare(currentSquare);
    int* toCoords = translateSquare(to);

    int fromRow = fromCoords[0], fromCol = fromCoords[1];
    int toRow = toCoords[0], toCol = toCoords[1];

    int colDiff = abs(fromCol - toCol);

    if (colDiff == 2) {
        return King::castle(to, board);
    }
    // // //

    return Piece::move(to, board);
}

bool King::isValidMove(string to, char board[][8]) {
    int* fromCoords = translateSquare(currentSquare);
    int* toCoords = translateSquare(to);

    int fromRow = fromCoords[0], fromCol = fromCoords[1], toRow = toCoords[0],
        toCol = toCoords[1];

    int rowDiff = abs(fromRow - toRow);
    int colDiff = abs(fromCol - toCol);

    if (this->capturesOwnPiece(toCoords, board)) return false;

    // check if move is check
    if (isInCheck(to, board)) return false;

    // check if king wants to castle
    if (colDiff == 2 && canCastle(to, board)) {
        cout << "The king can castle" << endl;
        return true;
    }

    // Check if the move is valid (1 square in any direction)
    if (rowDiff <= 1 && colDiff <= 1) return true;

    return false;
}

bool King::canCastle(string to, char board[][8]) {
    int* fromCoords = translateSquare(currentSquare);
    int* toCoords = translateSquare(to);

    int fromRow = fromCoords[0], fromCol = fromCoords[1];
    int toRow = toCoords[0], toCol = toCoords[1];

    int direction = toCol - fromCol;

    if (hasMoved) return false;
    if (toRow - fromRow != 0) return false;
    if (abs(direction) != 2) return false;

    // is the space between the king and the rook empty?
    // is the king in check?
    // will the king be in check?
    // did the wanted rook move?

    return true;
}

Rook* getRookToCastle(int direction, string color, char board[][8]) {
    Piece* wantedRook;
    if (direction > 0 && color == "white") {
        wantedRook = pieceFromChar(0, 7, board);
    } else if (direction < 0 && color == "white") {
        wantedRook = pieceFromChar(0, 0, board);
    } else if (direction > 0 && color == "black") {
        wantedRook = pieceFromChar(7, 7, board);
    } else if (direction < 0 && color == "black") {
        wantedRook = pieceFromChar(7, 0, board);
    }

    cout << "Wanted rook: ";
    wantedRook->printPiece();
    cout << endl;

    return dynamic_cast<Rook*>(wantedRook);
}

bool King::castle(string to, char board[][8]) {
    if (!canCastle(to, board)) return false;

    int* fromCoords = translateSquare(currentSquare);
    int* toCoords = translateSquare(to);

    int fromRow = fromCoords[0], fromCol = fromCoords[1];
    int toRow = toCoords[0], toCol = toCoords[1];

    int direction = toCol - fromCol;

    Rook* wantedRook = getRookToCastle(direction, this->color, board);

    if (wantedRook == NULL) return false;
    cout << "here" << endl;

    return move(to, board);
}

bool King::isInCheck(char board[][8]) {
    return isInCheck(this->currentSquare, board);
}

bool King::isInCheck(string to, char board[][8]) {
    Board* b = new Board("white", exportFEN(board));

    if (this->color == "white") {
        for (Piece* p : b->bp->pieces) {
            if (p->isValidMove(to, board)) {
                delete p;
                return true;
            }
        }
    } else {
        for (Piece* p : b->wp->pieces) {
            if (p->isValidMove(to, board)) {
                delete p;
                return true;
            }
        }
    }

    delete b;
    return false;
}

bool King::isInCheckmate(char board[][8]) {
    return (getValidMoves(board).empty() && isInCheck(board));
}

vector<string> King::getValidMoves(char board[][8]) {
    char currentFile = currentSquare.at(0);
    int currentRank = currentSquare.at(1) - 48;

    // All 8 possible King moves + 2 castling moves
    vector<string> movesToCheck = {
        string(1, currentFile) + to_string(currentRank + 1),
        string(1, currentFile) + to_string(currentRank - 1),
        string(1, currentFile + 1) + to_string(currentRank + 1),
        string(1, currentFile + 1) + to_string(currentRank - 1),
        string(1, currentFile - 1) + to_string(currentRank + 1),
        string(1, currentFile - 1) + to_string(currentRank - 1),
        string(1, currentFile + 1) + to_string(currentRank),
        string(1, currentFile - 1) + to_string(currentRank),
        string(1, currentFile + 2) + to_string(currentRank),  // Castling
        string(1, currentFile - 2) + to_string(currentRank)   // Castling

    };

    // Filter invalid squares
    for (int i = 0; i < movesToCheck.size(); i++) {
        if (!isValidSquare(movesToCheck.at(i))) {
            movesToCheck.erase(movesToCheck.begin() + i);  // erase from vector
            i--;
        }
    }

    // Filter invalid moves
    for (int i = 0; i < movesToCheck.size(); i++) {
        if (!this->isValidMove(movesToCheck.at(i), board)) {
            movesToCheck.erase(movesToCheck.begin() + i);  // erase from vector
            i--;
        }
    }

    return movesToCheck;
}