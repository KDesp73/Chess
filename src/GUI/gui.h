#pragma once

#include <iostream>
#include "SDL.h"

#include "Rendering/rendering.h"
#include "../chess_lib.h"

class GUI{
    public:
        static int size;
        static void init(int size, Board *board);
        static void loadPosition(Board *board, SDL_Renderer *renderer);
        static string getBoardCoordinates(int x, int y, string playingAs);
        static Coords getBoardCoordinates(string square, string playingAs);
        static void makeMove(Move move, Board *board, SDL_Renderer *renderer);
        static void runPGN(string pgn, Board *board, int size);
};