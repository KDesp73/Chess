#include <cstdlib>

#include "../Board/board_utils.h"
#include "Pieces.h"

using namespace BoardUtils;

/*
bool Pawn::move(string to, char board[][8]) {
    if (!isValidMove(to, board)) return false;

    if (translateSquare(currentSquare).x == 7 ||
        translateSquare(currentSquare).x == 0) {
        cout << "Promote" << endl;
        this->promote(board);
    }

    bool valid = Piece::move(to, board);

    if (translateSquare(currentSquare).x == 7 ||
        translateSquare(currentSquare).x == 0) {
        cout << "Promote" << endl;
        this->promote(board);
    }

    return valid;
}*/

bool Pawn::isValidMove(string to, char board[][8]) {
    Coords fromCoords = translateSquare(currentSquare);
    Coords toCoords = translateSquare(to);

    int fromRow = fromCoords.x, fromCol = fromCoords.y, toRow = toCoords.x,
        toCol = toCoords.y;

    int direction;
    if (this->color == "white") {
        direction = 1;
    } else {
        direction = -1;
    }

    // Check if the pawn is moving forward one or two squares
    if (toCol == fromCol && toRow == fromRow + direction) {
        if (board[toRow][toCol] == ' ') {
            return true;
        }
    } else if (toCol == fromCol && toRow == fromRow + 2 * direction &&
               fromRow == (this->color == "white" ? 1 : 6)) {
        if (board[toRow][toCol] == ' ' &&
            board[fromRow + direction][toCol] == ' ') {
            return true;
        }
    }
    // Check if the pawn is capturing an opponent's piece
    bool isOpponentsPiece =
        ((this->color == "white" && !isupper(board[toRow][toCol])) ||
         (this->color == "black" && isupper(board[toRow][toCol])));
    if (abs(toCol - fromCol) == 1 && toRow == fromRow + direction) {
        if (board[toRow][toCol] != ' ' && isOpponentsPiece) {
            return true;
        }
    }
    return false;
}

bool Pawn::isValidCapture(string to, char board[][8]) {
    int direction;
    if (this->color == "white") {
        direction = 1;
    } else {
        direction = -1;
    }

    Coords fromCoords = translateSquare(currentSquare);
    Coords toCoords = translateSquare(to);

    int fromRow = fromCoords.x, fromCol = fromCoords.y, toRow = toCoords.x,
        toCol = toCoords.y;

    if (this->capturesOwnPiece(toCoords, board)) return false;

    // Check if the pawn is capturing an opponent's piece
    bool isOpponentsPiece =
        ((this->color == "white" && !isupper(board[toRow][toCol])) ||
         (this->color == "black" && isupper(board[toRow][toCol])));
    if (abs(toCol - fromCol) == 1 && toRow == fromRow + direction) {
        if (board[toRow][toCol] != ' ' && isOpponentsPiece) {
            return true;
        }
    }
    return false;
}

bool Pawn::canPromote(string to, char board[][8]){
    bool validMove = this->isValidMove(to, board);
    bool validCapture = this->isValidCapture(to, board);
    if(this->color == "white"){
        return (validMove || validCapture) && translateSquare(to).x == 7;
    } else {
        return (this->isValidMove(to, board) || this->isValidCapture(to, board)) && translateSquare(to).x == 0;
    } 
}

vector<string> Pawn::getValidMoves(char board[][8]) {
    char currentFile = currentSquare.at(0);
    int currentRank = currentSquare.at(1) - 48;

    vector<string> movesToCheck = {
        string(1, currentFile) + to_string(currentRank + 1),
        string(1, currentFile) + to_string(currentRank + 2)};
    vector<string> capturesToCheck = {
        string(1, currentFile + 1) + to_string(currentRank + 1),
        string(1, currentFile - 1) + to_string(currentRank + 1),
    };

    // Filter invalid moves
    for (int i = 0; i < movesToCheck.size(); i++) {
        if (!this->isValidMove(movesToCheck.at(i), board)) {
            movesToCheck.erase(movesToCheck.begin() + i);  // erase from vector
            i--;
        }
    }

    // Filter invalid captures
    for (int i = 0; i < capturesToCheck.size(); i++) {
        if (!this->isValidCapture(capturesToCheck.at(i), board)) {
            capturesToCheck.erase(capturesToCheck.begin() +
                                  i);  // erase from vector
            i--;
        }
    }

    // Manually concat the two vectors
    for(string capture : capturesToCheck){
		movesToCheck.push_back(capture);
	}

	return movesToCheck;
}