#include <cstdlib>

#include "../Board/board_declarations.h"

bool Pawn::move(string to, char board[][8]) {
    if (!isValidMove(to, board)) return false;

    if (translateSquare(currentSquare)[0] == 7 ||
        translateSquare(currentSquare)[0] == 0) {
        cout << "Promote" << endl;
        this->promote(board);
    }

    bool valid = Piece::move(to, board);

    if (translateSquare(currentSquare)[0] == 7 ||
        translateSquare(currentSquare)[0] == 0) {
        cout << "Promote" << endl;
        this->promote(board);
    }

    return valid;
}

bool Pawn::isValidMove(string to, char board[][8]) {
    int* fromCoords = translateSquare(currentSquare);
    int* toCoords = translateSquare(to);

    int fromRow = fromCoords[0], fromCol = fromCoords[1], toRow = toCoords[0],
        toCol = toCoords[1];

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

    int* fromCoords = translateSquare(currentSquare);
    int* toCoords = translateSquare(to);

    int fromRow = fromCoords[0], fromCol = fromCoords[1], toRow = toCoords[0],
        toCol = toCoords[1];

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

void Pawn::promote(char board[][8]) {
    int promotionRank;
    if (color == "white")
        promotionRank = 8;
    else
        promotionRank = 1;

    int* currentCoords = translateSquare(this->currentSquare);
    if (currentCoords[0] != promotionRank - 1) return;

    char promoteTo;
    do {
        cout << "Promote to (q, r, b, n): ";
        cin >> promoteTo;
        cout << endl;
    } while (promoteTo != 'q' && promoteTo != 'r' && promoteTo != 'b' &&
             promoteTo != 'n');

    Piece* promoted;

    switch (promoteTo) {
        case 'q':
            promoted = new Queen(this->currentSquare, this->color);
            break;
        case 'r':
            promoted = new Rook(this->currentSquare, this->color);
            break;
        case 'b':
            promoted = new Bishop(this->currentSquare, this->color);
            break;
        case 'n':
            promoted = new Knight(this->currentSquare, this->color);
            break;
        default:
            Pawn::promote(board);
            return;
    }

    if (color == "white")
        board[currentCoords[0]][currentCoords[1]] = toupper(promoteTo);
    else
        board[currentCoords[0]][currentCoords[1]] = promoteTo;

    this->~Pawn();
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