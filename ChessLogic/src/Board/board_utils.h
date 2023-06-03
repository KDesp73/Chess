#pragma once

#include <vector>
#include <string>

using namespace std;

#include "board_declarations.h"
#include "structs.h"

namespace BoardUtils{
    bool canMove(Piece *piece, Move move, Board *board);
    bool canMove(string color, string square, Board *board);
    bool contains(vector<string> moves, string move);
    bool kingWantsToCastle(Move move);
    int calcDirection(King *king, string square);
    bool canKingCapturePiece(King *king, Move move, Board *board);
}