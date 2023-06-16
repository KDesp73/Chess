#include "board_utils.h"
#include "../Pieces/Pieces.h"
#include "structs.h"

#include <bits/stdc++.h>
#include <iostream>

using namespace BoardUtils;

bool Board::movePiece(Move move, Board *board) {
    string current_fen = Board::exportFEN(board);
    int moveIndex, captureIndex;
    Piece *pieceToMove = nullptr;
    Piece *pieceToCapture = nullptr;
    Pieces *whitePieces = board->getPieces(Piece::WHITE);
    Pieces *blackPieces = board->getPieces(Piece::BLACK);

    pieceToMove = board->findPiece(move.from);
    pieceToCapture = board->findPiece(move.to);

    Pawn *pawn = dynamic_cast<Pawn *>(pieceToMove);
    Rook *rook = dynamic_cast<Rook *>(pieceToMove);
    Knight *knight = dynamic_cast<Knight *>(pieceToMove);
    Bishop *bishop = dynamic_cast<Bishop *>(pieceToMove);
    Queen *queen = dynamic_cast<Queen *>(pieceToMove);
    King *king = dynamic_cast<King *>(pieceToMove);


    char promoteTo = '-';

    if(pieceToMove->color != board->moveFor) return false;

    // Pawn Promotion
    if(pawn != NULL && pawn->canPromote(move.to, board->board)) {
        promoteTo = Board::promoteTo();
        if(BoardUtils::canMove(pawn, move, board, promoteTo) && promoteTo != '-'){
            board->setMove1Before(move); 
            board->pushBoardState(Board::exportFEN(board->board));

            string algebraic_notation = Board::moveToPGNMove(move, new Board(current_fen), promoteTo);
            board->pgn_moves.push_back(algebraic_notation);

            return Board::promotePawn(move.to, pawn, board, promoteTo);
        }
        return false;
    }

    // En passant
    if(pawn != NULL && pawn->canEnpassant(move.to, board->getMove1Before())){
        board->setMove1Before(move);

        board->pushBoardState(Board::exportFEN(board->board));

        string algebraic_notation = Board::moveToPGNMove(move, new Board(current_fen));
        board->pgn_moves.push_back(algebraic_notation);
        return Board::enpassantPawn(move.to, pawn, board);
    }

    // Castle
    if(king != NULL && kingWantsToCastle(move) != 0 && king->canCastle(move.to, board->board)){
        board->setMove1Before(move);

        board->pushBoardState(Board::exportFEN(board->board));

        string algebraic_notation = Board::moveToPGNMove(move, new Board(current_fen));
        board->pgn_moves.push_back(algebraic_notation);
        return Board::castleKing(move.to, king, board);
    }


    if (
        !canMove(pawn, move, board, promoteTo) &&
        !canMove(rook, move, board) &&
        !canMove(knight, move, board) &&
        !canMove(bishop, move, board) &&
        !canMove(queen, move, board) &&
        !canMove(king, move, board)
    ) return false;

    // Capture the piece
    if(!Board::removePiece(move.to, board)) board->increaceMovesSinceCapture();
    else board->resetMovesSinceCapture();

    // Make the move
    bool moveMade = makeMove(pieceToMove->currentSquare, move.to, board->board);
    if (moveMade) {
        board->setMove1Before(move);

        board->pushBoardState(Board::exportFEN(board->board));

        string algebraic_notation = Board::moveToPGNMove(move, new Board(current_fen));
        board->pushMove(algebraic_notation);

        if(translateSquare(pieceToMove->currentSquare).y == 0 && pieceToMove->type == "Rook") dynamic_cast<King *>(board->findPiece("King", pieceToMove->color))->a_rook_moved = true;
        if(translateSquare(pieceToMove->currentSquare).y == 7 && pieceToMove->type == "Rook") dynamic_cast<King *>(board->findPiece("King", pieceToMove->color))->h_rook_moved = true;

        pieceToMove->currentSquare = move.to;
        pieceToMove->hasMoved = true;
    }
    return moveMade;
}

void Board::moveFreely(Move move, Board *board, char promoteTo){
    string current_fen = Board::exportFEN(board);
    int moveIndex, captureIndex;
    Piece *pieceToMove = NULL;
    Piece *pieceToCapture = NULL;
    Pieces *whitePieces = board->getPieces(Piece::WHITE);
    Pieces *blackPieces = board->getPieces(Piece::BLACK);


    pieceToMove = board->findPiece(move.from);
    pieceToCapture = board->findPiece(move.to);


    Pawn *pawn = dynamic_cast<Pawn *>(pieceToMove);
    Rook *rook = dynamic_cast<Rook *>(pieceToMove);
    Knight *knight = dynamic_cast<Knight *>(pieceToMove);
    Bishop *bishop = dynamic_cast<Bishop *>(pieceToMove);
    Queen *queen = dynamic_cast<Queen *>(pieceToMove);
    King *king = dynamic_cast<King *>(pieceToMove);

    // Special piece functionality
    if(pawn != NULL && pawn->canPromote(move.to, board->board)) {
        Board::promotePawn(move.to, pawn, board, promoteTo);
    }

    // Capture the piece
    if(!Board::removePiece(move.to, board)) board->increaceMovesSinceCapture();
    else board->resetMovesSinceCapture();

    // Make the move
    bool moveMade = makeMove(move.from, move.to, board->board);
    if (moveMade) {
        board->setMove1Before(move);

        board->pushBoardState(Board::exportFEN(board->board));

        if(translateSquare(pieceToMove->currentSquare).y == 0 && pieceToMove->type == "Rook") dynamic_cast<King *>(board->findPiece("King", pieceToMove->color))->a_rook_moved = true;
        if(translateSquare(pieceToMove->currentSquare).y == 7 && pieceToMove->type == "Rook") dynamic_cast<King *>(board->findPiece("King", pieceToMove->color))->h_rook_moved = true;

        pieceToMove->currentSquare = move.to;
        pieceToMove->hasMoved = true;
    }
}

bool BoardUtils::canMove(Piece *piece, Move move, Board *board, char promoteTo) {
    if(piece == NULL || piece == nullptr) return false;

    int direction = (piece->color == Piece::WHITE) ? 1 : -1;
    King *king = dynamic_cast<King *>(piece);

    if(king != NULL && !BoardUtils::canKingCapturePiece(king, move, board)) return false;

    if(king == NULL && board->isPinned(move.to, piece)) return false;

    // If the King in check, see if the move resolves the check
    if(piece->type != Piece::KING){
        King *kingInCheck = dynamic_cast<King *>(board->findPiece(Piece::KING, piece->color));
        bool isKingInCheck = !kingInCheck->isInCheck(board->board).empty();
        if(isKingInCheck){
            Board *temp_board = new Board(Board::exportFEN(board));

            if(piece->type == Piece::PAWN){
                if(dynamic_cast<Pawn *>(piece)->isValidCapture(move.to, board->board)) return true;
                if(dynamic_cast<Pawn *>(piece)->canEnpassant(translateSquare(Coords{translateSquare(move.to).x + direction, translateSquare(move.to).y}), board->getMove1Before())) return true;
            }

            if(piece->isValidMove(move.to, temp_board->board)) Board::moveFreely(move, temp_board, promoteTo);

            King *kingInCheckAfterMove = dynamic_cast<King *>(temp_board->findPiece(Piece::KING, piece->color));
            bool isKingInCheckAfter = !kingInCheckAfterMove->isInCheck(temp_board->board).empty();
            return !isKingInCheckAfter;
        }
    }

    // Allow special pawn moves
    if(piece->type == Piece::PAWN){
        if(dynamic_cast<Pawn *>(piece)->isValidCapture(move.to, board->board)) return true;
        if(dynamic_cast<Pawn *>(piece)->canEnpassant(translateSquare(Coords{translateSquare(move.to).x + direction, translateSquare(move.to).y}), board->getMove1Before())) return true;
        if(dynamic_cast<Pawn *>(piece)->canPromote(move.to, board->board)) return true;
    }

    // Pseudo-validation
    return piece->isValidMove(move.to, board->board);
}

bool BoardUtils::canMove(string color, string square, Board *board) {
    Pieces *pieces = board->getPieces(color);
    for (int i = 0; i < pieces->pieces.size(); i++)    {
        if(BoardUtils::canMove(pieces->pieces.at(i), Move{pieces->pieces.at(i)->currentSquare, square}, board)) return true;
    }
    return false;
}