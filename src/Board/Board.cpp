#include "./board.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "./board_utils.h"
#include "../../Ansi-Text-Manipulation-Library/AnsiTextLibrary/src/ansi_lib.hpp"

using namespace std;
using namespace BoardUtils;
using namespace AnsiTextLib;

const string Board::ONELINE = "oneline";
const string Board::SEPERATE = "seperate";

Pieces* Board::getPieces(string color){
    if(color == Piece::WHITE) return wp;
    if(color == Piece::BLACK) return bp;

    return nullptr;
}

void Board::printBoard() {
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

    cout << endl;

    if(showMaterial)
        cout << "Material Advantage: " << this->getPieces(Piece::WHITE)->calculateMaterial() - this->getPieces(Piece::BLACK)->calculateMaterial() << endl << endl;

}


void Board::printBigBoard() {
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
            for (int j = sizeof(board[i])-1; j >= 0 ; j--) {
                cout << "| " << board[i][j] << " ";
            }
            cout << "|  " << i + 1 << endl;
            cout << "   +---+---+---+---+---+---+---+---+" << endl;
        }
        cout << "     H   G   F   E   D   C   B   A " << endl;

    } else {
        cout << "Incorrect argument" << endl;
    }

    cout << endl;

    if(showMoves)
        cout << exportPGN() << endl;

    if(showMaterial)
        cout << "Material Advantage: " << this->getPieces(Piece::WHITE)->calculateMaterial() - this->getPieces(Piece::BLACK)->calculateMaterial() << endl << endl;
}

void Board::scanBoard(vector<Piece *> whitePieces, vector<Piece *> blackPieces) {
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

bool Board::removePiece(string square, Board *board){
    int removeIndex;
    Piece *pieceToRemove = NULL;
    Pieces *whitePieces = board->getPieces(Piece::WHITE);
    Pieces *blackPieces = board->getPieces(Piece::BLACK);

    // Search white for pieces
    for (int i = 0; i < whitePieces->pieces.size(); i++) {
        if (square == whitePieces->pieces.at(i)->currentSquare && board->moveFor == "black") {
            pieceToRemove = whitePieces->pieces.at(i);
            removeIndex = i;
        } 
    }

    // Search black for pieces
    for (int i = 0; i < blackPieces->pieces.size(); i++) {
        if (square == blackPieces->pieces.at(i)->currentSquare && board->moveFor == "white") {
            pieceToRemove = blackPieces->pieces.at(i);
            removeIndex = i;
        } 
    }

    if(pieceToRemove != NULL){
        if(pieceToRemove->color == "white"){
            whitePieces->pieces.erase(whitePieces->pieces.begin() + removeIndex);
        } else {
            blackPieces->pieces.erase(blackPieces->pieces.begin() + removeIndex);
        }

        pieceToRemove->~Piece();
        Coords coords = translateSquare(square);
        board->board[coords.x][coords.y] = ' ';
        
        return true;
    }
    return false;
}

bool Board::removePieceFreely(string square, Board *board){
    int removeIndex;
    Piece *pieceToRemove = NULL;
    Pieces *whitePieces = board->getPieces(Piece::WHITE);
    Pieces *blackPieces = board->getPieces(Piece::BLACK);

    // Search white for pieces
    for (int i = 0; i < whitePieces->pieces.size(); i++) {
        if (square == whitePieces->pieces.at(i)->currentSquare) {
            pieceToRemove = whitePieces->pieces.at(i);
            removeIndex = i;
        } 
    }

    // Search black for pieces
    for (int i = 0; i < blackPieces->pieces.size(); i++) {
        if (square == blackPieces->pieces.at(i)->currentSquare) {
            pieceToRemove = blackPieces->pieces.at(i);
            removeIndex = i;
        } 
    }

    if(pieceToRemove != NULL){
        if(pieceToRemove->color == "white"){
            whitePieces->pieces.erase(whitePieces->pieces.begin() + removeIndex);
        } else {
            blackPieces->pieces.erase(blackPieces->pieces.begin() + removeIndex);
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

Piece* Board::findPiece(string square){
    return this->findPiece(translateSquare(square));
}

bool Board::isProtected(Piece *piece) {
    if (piece == NULL) return false;
    char temp_board[8][8];
    memcpy(temp_board, this->board, 8 * 8 * sizeof(char));
    temp_board[translateSquare(piece->currentSquare).x]
              [translateSquare(piece->currentSquare).y] = ' ';

    King *opponentsKing = dynamic_cast<King *>(this->findPiece(Piece::KING, (piece->color == Piece::WHITE) ? Piece::BLACK : Piece::WHITE));

    if(opponentsKing != NULL){
        temp_board[translateSquare(opponentsKing->currentSquare).x]
                  [translateSquare(opponentsKing->currentSquare).y] = ' ';
    }

    Board b{temp_board};
    
    for(Piece *p : this->getPieces(piece->color)->pieces){
        if(this->isPinned(piece->currentSquare, piece)) continue;;
        if(!p->isValidMove(piece->currentSquare, temp_board)) continue;

        if(piece->type == Piece::PAWN){
            if(dynamic_cast<Pawn *>(piece)->isValidCapture(piece->currentSquare, this->board)) return true;
        }

        return true;
    }
    
    return false;
}

bool Board::isPinned(string to, Piece *piece){
    Pieces *pieces = this->getPieces(piece->color);
    King *king = dynamic_cast<King *>(this->findPiece(Piece::KING, piece->color));

    if(piece->type == Piece::KING) return false;

    vector<Piece *> piecesThatCheckTheKingBefore = king->isInCheck(this->board);

    // if removing the piece causes the king to be in check then it's pinned
    char temp_board[8][8];
    std::memcpy(temp_board, this->board, 8 * 8 * sizeof(char));
    
    BoardUtils::makeMove(piece->currentSquare, to, temp_board);

    vector<Piece *> piecesThatCheckTheKing = king->isInCheck(temp_board);
    return (piecesThatCheckTheKingBefore.size() < piecesThatCheckTheKing.size());
}

vector<string> Board::getValidMoves(Piece *piece, Board *board){
    Pawn *pawn = dynamic_cast<Pawn *>(piece);
    Rook *rook = dynamic_cast<Rook *>(piece);
    Knight *knight = dynamic_cast<Knight *>(piece);
    Bishop *bishop = dynamic_cast<Bishop *>(piece);
    Queen *queen = dynamic_cast<Queen *>(piece);
    King *king = dynamic_cast<King *>(piece);

    if(pawn != NULL){
        char currentFile = pawn->currentSquare.at(0);
        int currentRank = pawn->currentSquare.at(1) - 48;
        
        int direction = (piece->color == Piece::WHITE) ? 1 : -1;

        vector<string> movesToCheck = {
            string(1, currentFile) + to_string(currentRank + 1 * direction),
            string(1, currentFile) + to_string(currentRank + 2 * direction)};
        vector<string> capturesToCheck = {
            string(1, currentFile + 1) + to_string(currentRank + 1 * direction),
            string(1, currentFile - 1) + to_string(currentRank + 1 * direction),
        };


        // Filter invalid moves
        for (int i = 0; i < movesToCheck.size(); i++) {
            if (!BoardUtils::canMove(pawn, Move{pawn->currentSquare, movesToCheck.at(i)}, board)) {
                movesToCheck.erase(movesToCheck.begin() + i);  // erase from vector
                i--;
            }
        }

        return movesToCheck;
    }

    if(knight != NULL){
        char currentFile = knight->currentSquare.at(0);
        int currentRank = knight->currentSquare.at(1) - 48;

        

        vector<string> movesToCheck = {
            string(1, currentFile+1) + to_string(currentRank+2),
            string(1, currentFile-1) + to_string(currentRank+2),
            string(1, currentFile+1) + to_string(currentRank-2),
            string(1, currentFile-1) + to_string(currentRank-2),
            string(1, currentFile+2) + to_string(currentRank+1),
            string(1, currentFile+2) + to_string(currentRank-1),
            string(1, currentFile-2) + to_string(currentRank+1),
            string(1, currentFile-2) + to_string(currentRank-1),
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
            if(!BoardUtils::canMove(knight, Move{knight->currentSquare, movesToCheck.at(i)}, board)){
                movesToCheck.erase(movesToCheck.begin() + i);  // erase from vector
                i--;
            }
        }

        return movesToCheck;
    }

    if(bishop != NULL){
        char currentFile = bishop->currentSquare.at(0);
        int currentRank = bishop->currentSquare.at(1) - 48;

        vector<string> movesToCheck;

        // Check up and right
        char tempFile = currentFile;
        int tempRank = currentRank;
        while(tempFile < 'h' && tempRank < 8){
            tempFile++;
            tempRank++;
            movesToCheck.push_back(string(1, tempFile) + to_string(tempRank));
        }

        // Check up and left
        tempFile = currentFile;
        tempRank = currentRank;
        while(tempFile > 'a' && tempRank < 8){
            tempFile--;
            tempRank++;
            movesToCheck.push_back(string(1, tempFile) + to_string(tempRank));
        }

        // Check down and right
        tempFile = currentFile;
        tempRank = currentRank;
        while(tempFile < 'h' && tempRank > 1){
            tempFile++;
            tempRank--;
            movesToCheck.push_back(string(1, tempFile) + to_string(tempRank));
        }

        // Check down and left
        tempFile = currentFile;
        tempRank = currentRank;
        while(tempFile > 'a' && tempRank > 1){
            tempFile--;
            tempRank--;
            movesToCheck.push_back(string(1, tempFile) + to_string(tempRank));
        }

        // Filter invalid moves
        for (int i = 0; i < movesToCheck.size(); i++) {
            if(!BoardUtils::canMove(bishop, Move{bishop->currentSquare, movesToCheck.at(i)}, board)){
                movesToCheck.erase(movesToCheck.begin() + i);  // erase from vector
                i--;
            }
        }

        return movesToCheck;
    }

    if(rook != NULL){
        char currentFile = rook->currentSquare.at(0);
        int currentRank = rook->currentSquare.at(1) - 48;

        vector<string> movesToCheck;

        
        // Check same rank left
        char tempFile = currentFile;
        while(tempFile > 'a'){
            tempFile--;
            movesToCheck.push_back(string(1, tempFile) + to_string(currentRank));
        }


        // Check same rank right
        tempFile = currentFile;
        while(tempFile < 'h'){
            tempFile++;
            movesToCheck.push_back(string(1, tempFile) + to_string(currentRank));
        }


        // Check same file up
        int tempRank = currentRank;
        while(tempRank < 8){
            tempRank++;
            movesToCheck.push_back(string(1, currentFile) + to_string(tempRank));
        }
        
        // Check same file down
        tempRank = currentRank;
        while(tempRank > 1){
            tempRank--;
            movesToCheck.push_back(string(1, currentFile) + to_string(tempRank));
        }

        // Filter invalid moves
        for (int i = 0; i < movesToCheck.size(); i++) {
            if(!BoardUtils::canMove(rook, Move{rook->currentSquare, movesToCheck.at(i)}, board)){
                movesToCheck.erase(movesToCheck.begin() + i);  // erase from vector
                i--;
            }
        }

        return movesToCheck;
    }

    if(queen != NULL){
        char currentFile = queen->currentSquare.at(0);
        int currentRank = queen->currentSquare.at(1) - 48;

        vector<string> movesToCheck;
        char tempFile = currentFile;
        int tempRank = currentRank;

        // Check same rank left
        while(tempFile > 'a'){
            tempFile--;
            movesToCheck.push_back(string(1, tempFile) + to_string(currentRank));
        }

        // Check same rank right
        tempFile = currentFile;
        while(tempFile < 'h'){
            tempFile++;
            movesToCheck.push_back(string(1, tempFile) + to_string(currentRank));
        }


        // Check same file up
        tempRank = currentRank;
        while(tempRank < 8){
            tempRank++;
            movesToCheck.push_back(string(1, currentFile) + to_string(tempRank));
        }
        
        // Check same file down
        tempRank = currentRank;
        while(tempRank > 1){
            tempRank--;
            movesToCheck.push_back(string(1, currentFile) + to_string(tempRank));
        }

        // Check up and right
        tempFile = currentFile;
        tempRank = currentRank;
        while(tempFile < 'h' && tempRank < 8){
            tempFile++;
            tempRank++;
            movesToCheck.push_back(string(1, tempFile) + to_string(tempRank));
        }

        // Check up and left
        tempFile = currentFile;
        tempRank = currentRank;
        while(tempFile > 'a' && tempRank < 8){
            tempFile--;
            tempRank++;
            movesToCheck.push_back(string(1, tempFile) + to_string(tempRank));
        }

        // Check down and right
        tempFile = currentFile;
        tempRank = currentRank;
        while(tempFile < 'h' && tempRank > 1){
            tempFile++;
            tempRank--;
            movesToCheck.push_back(string(1, tempFile) + to_string(tempRank));
        }

        // Check down and left
        tempFile = currentFile;
        tempRank = currentRank;
        while(tempFile > 'a' && tempRank > 1){
            tempFile--;
            tempRank--;
            movesToCheck.push_back(string(1, tempFile) + to_string(tempRank));
        }

        // Filter invalid moves
        for (int i = 0; i < movesToCheck.size(); i++) {
            if(!BoardUtils::canMove(queen, Move{queen->currentSquare, movesToCheck.at(i)}, board)){
                movesToCheck.erase(movesToCheck.begin() + i);  // erase from vector
                i--;
            }
        }

        return movesToCheck;
    }

    if(king != NULL){
        char currentFile = king->currentSquare.at(0);
        int currentRank = king->currentSquare.at(1) - 48;

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
        };

        // For castling
        if(king->color == Piece::WHITE && king->currentSquare == "e1" || king->color == Piece::BLACK && king->currentSquare == "e8"){
            movesToCheck.push_back(string(1, currentFile + 2) + to_string(currentRank));
            movesToCheck.push_back(string(1, currentFile - 2) + to_string(currentRank));
        }

        // Filter invalid squares
        for (int i = 0; i < movesToCheck.size(); i++) {
            if (!isValidSquare(movesToCheck.at(i))) {
                movesToCheck.erase(movesToCheck.begin() + i);  // erase from vector
                i--;
            }
        }

        // Filter invalid moves
        for (int i = 0; i < movesToCheck.size(); i++) {
            if (!BoardUtils::canMove(king, Move{king->currentSquare, movesToCheck.at(i)}, board)) {
                movesToCheck.erase(movesToCheck.begin() + i);  // erase from vector
                i--;
            }
        }

        return movesToCheck;
    }

    return vector<string>{};
}

void Board::copyBoard(char src[8][8], char dest[8][8]){
    memcpy(dest, src, 8*8*sizeof(char));
}

void Board::copyMove(Move *src, Move *dest){
    dest->from = src->from;
    dest->to = src->to;
}

bool Board::isThreeFoldRepetition(){
    for (const auto& pair : past_board_states) {
        if (pair.second == 3) {
            return true;            
        }
    }
    return false;
}

void Board::pushBoardState(string fen){
    auto it = past_board_states.find(fen);
    if (it != past_board_states.end()) {
        past_board_states[fen]++; 
    } else {
        past_board_states.insert({fen, 1});
    }
}

int Board::quantityOfPiece(string type, string color){
    Pieces *pieces = (color == Piece::WHITE) ? wp : bp;

    int count = 0;

    for (int i = 0; i < pieces->pieces.size(); i++){
        if(pieces->pieces.at(i)->type == type) count++;
    }
    return count;
}

bool Board::isDrawDueToInsufficientMaterial(){
    // If there are pawns on the board its not a draw
    if(this->findPiece(Piece::PAWN, Piece::WHITE) != NULL && this->findPiece(Piece::PAWN, Piece::BLACK) != NULL) return false;

    
    // King vs King
    if(
        this->getPieces(Piece::WHITE)->pieces.size() == 1 &&
        this->getPieces(Piece::BLACK)->pieces.size() == 1 &&
        quantityOfPiece(Piece::KING, Piece::WHITE) == 1 &&
        quantityOfPiece(Piece::KING, Piece::BLACK) == 1
    ) return true;

    // King vs King and Knight
    if(
        this->getPieces(Piece::WHITE)->pieces.size() == 1 &&
        this->getPieces(Piece::BLACK)->pieces.size() == 2 &&
        quantityOfPiece(Piece::KING, Piece::WHITE) == 1 &&
        quantityOfPiece(Piece::KING, Piece::BLACK) == 1 &&
        quantityOfPiece(Piece::KNIGHT, Piece::BLACK) == 1
    ) return true;
    
    // King and Knight vs King
    if(
        this->getPieces(Piece::WHITE)->pieces.size() == 2 &&
        this->getPieces(Piece::BLACK)->pieces.size() == 1 &&
        quantityOfPiece(Piece::KING, Piece::WHITE) == 1 &&
        quantityOfPiece(Piece::KING, Piece::BLACK) == 1 &&
        quantityOfPiece(Piece::KNIGHT, Piece::WHITE) == 1
    ) return true;

    // King vs King and Bishop
    if(
        this->getPieces(Piece::WHITE)->pieces.size() == 1 &&
        this->getPieces(Piece::BLACK)->pieces.size() == 2 &&
        quantityOfPiece(Piece::KING, Piece::WHITE) == 1 &&
        quantityOfPiece(Piece::KING, Piece::BLACK) == 1 &&
        quantityOfPiece(Piece::BISHOP, Piece::BLACK) == 1
    ) return true;
    
    // King and Bishop vs King
    if(
        this->getPieces(Piece::WHITE)->pieces.size() == 2 &&
        this->getPieces(Piece::BLACK)->pieces.size() == 1 &&
        quantityOfPiece(Piece::KING, Piece::WHITE) == 1 &&
        quantityOfPiece(Piece::KING, Piece::BLACK) == 1 &&
        quantityOfPiece(Piece::BISHOP, Piece::WHITE) == 1
    ) return true;

    // King vs King and 2 knights
    if(
        this->getPieces(Piece::WHITE)->pieces.size() == 1 &&
        this->getPieces(Piece::BLACK)->pieces.size() == 3 &&
        quantityOfPiece(Piece::KING, Piece::WHITE) == 1 &&
        quantityOfPiece(Piece::KING, Piece::BLACK) == 1 &&
        quantityOfPiece(Piece::KNIGHT, Piece::BLACK) == 2
    ) return true;
    
    // King and 2 knights vs King
    if(
        this->getPieces(Piece::WHITE)->pieces.size() == 3 &&
        this->getPieces(Piece::BLACK)->pieces.size() == 1 &&
        quantityOfPiece(Piece::KING, Piece::WHITE) == 1 &&
        quantityOfPiece(Piece::KING, Piece::BLACK) == 1 &&
        quantityOfPiece(Piece::KNIGHT, Piece::WHITE) == 2
    ) return true;

    return false;
}

void Board::increaceMovesSinceCapture(){
    moves_since_capture++;
}

void Board::resetMovesSinceCapture(){
    moves_since_capture = 0;
}

bool Board::isFiftyMoveRule(){
    return (moves_since_capture == 50 * 2);
}

void Board::setOutcome(string outcome){
    this->outcome = outcome;
}

void Board::setKingsCastlingRights(King *king){
    if(king == NULL) return;
    
    if(king->color == Piece::WHITE){
        if(castling_rights.find('K') == string::npos) 
            king->h_rook_moved = true;
        if(castling_rights.find('Q') == string::npos) 
            king->a_rook_moved = true;
    } else if(king->color == Piece::BLACK){
        if(castling_rights.find('k') == string::npos) 
            king->h_rook_moved = true;
        if(castling_rights.find('q') == string::npos) 
            king->a_rook_moved = true;
    }
}

void Board::pushMove(string move){
    pgn_moves.push_back(move);
}

void Board::setMove1Before(Move move){
    this->move_1_before = move;
}

Move Board::getMove1Before(){
    return this->move_1_before;
}