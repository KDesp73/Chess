#pragma once

namespace BoardUtils{
    bool canMove(Piece *piece, Move move, Board *board);
    bool contains(vector<string> moves, string move);
    bool kingWantsToCastle(Move move);
    int calcDirection(King *king, string square);
}