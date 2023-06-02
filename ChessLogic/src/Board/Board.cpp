#include "./board.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "./board_declarations.h"
#include "./board_utils.h"
#include "../text/text.h"

using namespace std;
using namespace BoardUtils;

void Board::printBoard() { Board::printBoard("white"); }

void Board::printBoard(string playingAs) {
    Text::clearScreen();
    if (playingAs == "white") {
        cout << "   ABCDEFGH" << endl << endl;
        for (int i = 7; i >= 0; i--) {
            cout << i + 1 << "  ";
            for (int j = 0; j < sizeof(board[i]); j++) {
                cout << board[i][j];
            }
            cout << "  " << i + 1 << endl;
        }
        cout << endl << "   ABCDEFGH" << endl << endl;
    } else if (playingAs == "black") {
        cout << "   HGFEDCBA" << endl << endl;
        for (int i = 0; i <= 7; i++) {
            cout << i + 1 << "  ";
            for (int j = 0; j < sizeof(board[i]); j++) {
                cout << board[i][j];
            }
            cout << "  " << i + 1 << endl;
        }
        cout << endl << "   HGFEDCBA" << endl << endl;
    } else {
        cout << "Incorrect argument" << endl;
    }
}

void Board::printBigBoard() { Board::printBigBoard("white"); }

void Board::printBigBoard(string playingAs) {
    Text::clearScreen();
    if (playingAs == "white") {
        cout << "     A   B   C   D   E   F   G   H " << endl;
        cout << "   +---+---+---+---+---+---+---+---+" << endl;
        for (int i = 7; i >= 0; i--) {
            cout << i + 1 << "  ";
            for (int j = 0; j < sizeof(board[i]); j++) {
                cout << "| " << board[i][j] << " ";
            }
            cout << "|  " << i + 1 << endl;
            cout << "   +---+---+---+---+---+---+---+---+" << endl;
        }
        cout << "     A   B   C   D   E   F   G   H " << endl;
    } else if (playingAs == "black") {
        cout << "     H   G   F   E   D   C   B   A " << endl;
        cout << "   +---+---+---+---+---+---+---+---+" << endl;
        for (int i = 0; i <= 7; i++) {
            cout << i + 1 << "  ";
            for (int j = 0; j < sizeof(board[i]); j++) {
                cout << "| " << board[i][j] << " ";
            }
            cout << "|  " << i + 1 << endl;
            cout << "   +---+---+---+---+---+---+---+---+" << endl;
        }
        cout << "     H   G   F   E   D   C   B   A " << endl;

    } else {
        cout << "Incorrect argument" << endl;
    }
}

void Board::scanBoard(vector<Piece *> whitePieces,
                      vector<Piece *> blackPieces) {
    string white_square, black_square;
    Coords white_coords, black_coords;

    for (int i = 0; i < 16; i++) {
        white_square = whitePieces.at(i)->currentSquare;
        black_square = blackPieces.at(i)->currentSquare;

        white_coords = translateSquare(white_square);
        black_coords = translateSquare(black_square);

        board[white_coords.x][white_coords.y] = whitePieces.at(i)->boardChar;
        board[black_coords.x][black_coords.y] = blackPieces.at(i)->boardChar;
    }
}

bool Board::movePiece(Move move, Board *board) {
    Piece *pieceToMove = NULL;
    int moveIndex, captureIndex;
    Piece *pieceToCapture = NULL;

    // Search white for pieces
    for (int i = 0; i < board->wp->pieces.size(); i++) {
        if (move.from == board->wp->pieces.at(i)->currentSquare && board->moveFor == "white") {
            pieceToMove = board->wp->pieces.at(i);
            moveIndex = i;
        } else if (move.to == board->wp->pieces.at(i)->currentSquare) {
            pieceToCapture = board->wp->pieces.at(i);
            captureIndex = i;
        }
    }

    // Search black for pieces
    for (int i = 0; i < board->bp->pieces.size(); i++) {
        if (move.from == board->bp->pieces.at(i)->currentSquare && board->moveFor == "black") {
            pieceToMove = board->bp->pieces.at(i);
            moveIndex = i;
        } else if (move.to == board->bp->pieces.at(i)->currentSquare) {
            pieceToCapture = board->bp->pieces.at(i);
            captureIndex = i;
        }
    }

    Pawn *pawn = dynamic_cast<Pawn *>(pieceToMove);
    Rook *rook = dynamic_cast<Rook *>(pieceToMove);
    Knight *knight = dynamic_cast<Knight *>(pieceToMove);
    Bishop *bishop = dynamic_cast<Bishop *>(pieceToMove);
    Queen *queen = dynamic_cast<Queen *>(pieceToMove);
    King *king = dynamic_cast<King *>(pieceToMove);

    if (
        !canMove(pawn, move, board) &&
        !canMove(rook, move, board) &&
        !canMove(knight, move, board) &&
        !canMove(bishop, move, board) &&
        !canMove(queen, move, board) &&
        !canMove(king, move, board)
    ) return false;

    // Special piece functionality
    if(pawn != NULL && pawn->canPromote(move.to, board->board)) {
        return Board::promotePawn(move.to, pawn, board);;
    }

    if(king != NULL && kingWantsToCastle(move) && king->canCastle(move.to, board->board)){
        return Board::castleKing(move.to, king, board);
    }

    // Capture the piece
    Board::removePiece(move.to, board);

    // Make the move
    bool moveMade = makeMove(pieceToMove->currentSquare, move.to, board->board);;
    if (moveMade) {
        if(translateSquare(pieceToMove->currentSquare).y == 0 && pieceToMove->type == "Rook") dynamic_cast<King *>(board->findPiece("King", pieceToMove->color))->a_rook_moved = true;
        if(translateSquare(pieceToMove->currentSquare).y == 7 && pieceToMove->type == "Rook") dynamic_cast<King *>(board->findPiece("King", pieceToMove->color))->h_rook_moved = true;

        pieceToMove->currentSquare = move.to;
        pieceToMove->hasMoved = true;
    }
    return moveMade;
}

void Board::moveFreely(Move move, Board *board){
    Piece *pieceToMove = NULL;
    int moveIndex, captureIndex;
    Piece *pieceToCapture = NULL;

    // Search white for pieces
    for (int i = 0; i < board->wp->pieces.size(); i++) {
        if (move.from == board->wp->pieces.at(i)->currentSquare && board->moveFor == "white") {
            pieceToMove = board->wp->pieces.at(i);
            moveIndex = i;
        } else if (move.to == board->wp->pieces.at(i)->currentSquare) {
            pieceToCapture = board->wp->pieces.at(i);
            captureIndex = i;
        }
    }

    // Search black for pieces
    for (int i = 0; i < board->bp->pieces.size(); i++) {
        if (move.from == board->bp->pieces.at(i)->currentSquare && board->moveFor == "black") {
            pieceToMove = board->bp->pieces.at(i);
            moveIndex = i;
        } else if (move.to == board->bp->pieces.at(i)->currentSquare) {
            pieceToCapture = board->bp->pieces.at(i);
            captureIndex = i;
        }
    }

    Pawn *pawn = dynamic_cast<Pawn *>(pieceToMove);
    Rook *rook = dynamic_cast<Rook *>(pieceToMove);
    Knight *knight = dynamic_cast<Knight *>(pieceToMove);
    Bishop *bishop = dynamic_cast<Bishop *>(pieceToMove);
    Queen *queen = dynamic_cast<Queen *>(pieceToMove);
    King *king = dynamic_cast<King *>(pieceToMove);

    // Special piece functionality
    if(pawn != NULL && pawn->canPromote(move.to, board->board)) {
        Board::promotePawn(move.to, pawn, board);;
    }

    // Capture the piece
    Board::removePiece(move.to, board);

    // Make the move
    bool moveMade = makeMove(pieceToMove->currentSquare, move.to, board->board);;
    if (moveMade) {
        cout << to_string(translateSquare(pieceToMove->currentSquare).y == 0 && pieceToMove->type == "rook") << endl;
        cout << to_string(translateSquare(pieceToMove->currentSquare).y == 7 && pieceToMove->type == "rook") << endl;
        if(translateSquare(pieceToMove->currentSquare).y == 0 && pieceToMove->type == "Rook") dynamic_cast<King *>(board->findPiece("King", pieceToMove->color))->a_rook_moved = true;
        if(translateSquare(pieceToMove->currentSquare).y == 7 && pieceToMove->type == "Rook") dynamic_cast<King *>(board->findPiece("King", pieceToMove->color))->h_rook_moved = true;

        pieceToMove->currentSquare = move.to;
        pieceToMove->hasMoved = true;
    }
}

bool Board::removePiece(string square, Board *board){
    Piece *pieceToRemove = NULL;
    int removeIndex;

    // Search white for pieces
    for (int i = 0; i < board->wp->pieces.size(); i++) {
        if (square == board->wp->pieces.at(i)->currentSquare && board->moveFor == "black") {
            pieceToRemove = board->wp->pieces.at(i);
            removeIndex = i;
        } 
    }

    // Search black for pieces
    for (int i = 0; i < board->bp->pieces.size(); i++) {
        if (square == board->bp->pieces.at(i)->currentSquare && board->moveFor == "white") {
            pieceToRemove = board->bp->pieces.at(i);
            removeIndex = i;
        } 
    }

    if(pieceToRemove != NULL){
        if(pieceToRemove->color == "white"){
            board->wp->pieces.erase(board->wp->pieces.begin() + removeIndex);
        } else {
            board->bp->pieces.erase(board->bp->pieces.begin() + removeIndex);
        }

        pieceToRemove->~Piece();
        Coords coords = translateSquare(square);
        board->board[coords.x][coords.y] = ' ';
        
        return true;
    }
    return false;
}

bool Board::removePieceFreely(string square, Board *board){
    Piece *pieceToRemove = NULL;
    int removeIndex;

    // Search white for pieces
    for (int i = 0; i < board->wp->pieces.size(); i++) {
        if (square == board->wp->pieces.at(i)->currentSquare) {
            pieceToRemove = board->wp->pieces.at(i);
            removeIndex = i;
        } 
    }

    // Search black for pieces
    for (int i = 0; i < board->bp->pieces.size(); i++) {
        if (square == board->bp->pieces.at(i)->currentSquare) {
            pieceToRemove = board->bp->pieces.at(i);
            removeIndex = i;
        } 
    }

    if(pieceToRemove != NULL){
        if(pieceToRemove->color == "white"){
            board->wp->pieces.erase(board->wp->pieces.begin() + removeIndex);
        } else {
            board->bp->pieces.erase(board->bp->pieces.begin() + removeIndex);
        }

        pieceToRemove->~Piece();
        Coords coords = translateSquare(square);
        board->board[coords.x][coords.y] = ' ';
        
        return true;
    }
    return false;
}


Piece* Board::findPiece(string type, string color){
    if(color == "white"){
        for (int i = 0; i < this->wp->pieces.size(); i++){
            if(type == wp->pieces.at(i)->type) return wp->pieces.at(i);
        }
    } else {
        for (int i = 0; i < this->bp->pieces.size(); i++){
            if(type == bp->pieces.at(i)->type) return bp->pieces.at(i);
        }
    }
    return NULL;
}

int Board::findPiece(Piece *piece){
    if(piece->color == "white"){
        for (int i = 0; i < this->wp->pieces.size(); i++){
            if(piece == wp->pieces.at(i)) return i;
        }
    } else {
        for (int i = 0; i < this->bp->pieces.size(); i++){
            if(piece == bp->pieces.at(i)) return i;
        }
    }
    return -1;
}

Piece* Board::findPiece(Coords coords){
    if(this->bp->pieceInSquare(translateSquare(coords), this->board) != NULL) return this->bp->pieceInSquare(translateSquare(coords), this->board);
    if(this->wp->pieceInSquare(translateSquare(coords), this->board) != NULL) return this->wp->pieceInSquare(translateSquare(coords), this->board);
    return NULL;
}


