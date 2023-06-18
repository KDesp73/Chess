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
};