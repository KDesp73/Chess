#pragma once

#include <vector>
#include <string>

using namespace std;

#include "structs.h"
#include "../Pieces/Pieces.h"
#include "board.h"

namespace BoardUtils{
    bool canMove(Move move, Board *board);
    bool canMove(string color, string square, Board *board);
    bool contains(vector<string> moves, string move);
    bool canKingCapturePiece(King *king, Move move, Board *board);
    bool canRookBeBlocked(Rook *rook, King *king, Board *board);
    bool canBishopBeBlocked(Bishop *bishop, King *king, Board *board);
    bool canQueenBeBlocked(Queen *queen, King *king, Board *board);
    bool canPieceBeBlocked(Piece *piece, King *king, Board *board);
    bool makeMove(string from, string to, char board[][8]); // The primitive one
    bool isValidSquare(string square);

    int kingWantsToCastle(Move move);
    int calcDirection(King *king, string square);
    
    void printCoords(Coords coords);
    void printCoords(string square);
    void emptyBoard(char board[][8]);
    
    char pieceToMove(Coords coords, char board[][8]);
    char pieceToMove(string square, char board[][8]);
    
    Coords translateSquare(string square);
    string translateSquare(Coords coords);
    vector<Piece*> squareIsAttacked(string square, Pieces *p, char board[][8]);
    Rook* getRookToCastle(int direction, string color, Board *board);
    string offsetSquare(string square, int offset_v, int offset_h);
}