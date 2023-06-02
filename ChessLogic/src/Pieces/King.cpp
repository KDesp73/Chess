#include <algorithm>

#include "../Board/board.h"
#include "../Board/board_declarations.h"
#include "piece_declarations.h"

using namespace std;

bool King::isValidMove(string to, char board[][8]) {
    Coords fromCoords = translateSquare(currentSquare);
    Coords toCoords = translateSquare(to);

    int fromRow = fromCoords.x, fromCol = fromCoords.y, toRow = toCoords.x,
        toCol = toCoords.y;

    int rowDiff = abs(fromRow - toRow);
    int colDiff = abs(fromCol - toCol);

    if (this->capturesOwnPiece(toCoords, board)) return false;

    // check if move is check
    if (isInCheck(to, board)) return false;

    // check if king wants to castle
    if (colDiff == 2 && canCastle(to, board)){
        cout << "The king can castle" << endl;
        return true;
    }

    // Check if the move is valid (1 square in any direction)
    if (rowDiff <= 1 && colDiff <= 1) return true;

    return false;
}


bool King::canCastle(string to, char board[][8]) {
    Coords fromCoords = translateSquare(currentSquare);
    Coords toCoords = translateSquare(to);

    int fromRow = fromCoords.x, fromCol = fromCoords.y;
    int toRow = toCoords.x, toCol = toCoords.y;

    int direction = toCol - fromCol;
    direction = (direction > 0) ? 1 : -1;

    // did the King move
    if (hasMoved) return false;
    
    // don't go up or down
    if (abs(toRow - fromRow) != 0) return false;
    
    // is only two steps
    if (abs(toCol - fromCol) != 2) return false;

    // is the space between the king and the rook empty?
    if(board[fromRow][fromCol + (direction)] != ' ') return false;
    if(board[fromRow][fromCol + (direction*2)] != ' ') return false;

    // is the king in check?
    if(this->isInCheck(board)) return false;
    

    // will the king be in check?
    if(this->isInCheck(translateSquare(Coords{fromRow, fromCol + (direction)}) , board)) return false;
    if(this->isInCheck(translateSquare(Coords{fromRow, fromCol + (direction * 2)}) , board)) return false;
    

    // // did the wanted rook move?
    if(direction > 0 && this->h_rook_moved) return false;
    if(direction < 0 && this->a_rook_moved) return false;

    return true;
}



bool King::isInCheck(char board[][8]) {
    return isInCheck(this->currentSquare, board);
}

bool King::isInCheck(string to, char board[][8]) {
    Board* b = new Board("white", Board::exportFEN(board));
    Board::removePiece(this->currentSquare, b);

    if (this->color == "white") {
        for (Piece* p : b->bp->pieces) {
            if(p->type == "King") continue;
            if (p->isValidMove(to, b->board)) {
                delete p;
                return true;
            }
        }
    } else {
        for (Piece* p : b->wp->pieces) {
            if(p->type == "King") continue;
            if (p->isValidMove(to, b->board)) {
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