#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../Pieces/piece_declarations.h"
#include "../Board/board.h"
#include "../Board/board_declarations.h"

//game_logic.cpp

namespace Game{

void start(string starting_fen);

Move prompt(Pieces* p, char board[][8]);

bool makeGivenMove(Move move, Pieces *p, char board[][8]);
bool makeGivenMove(Move move, Pieces *p, Board *board);

bool turn(Pieces *p, Board *board);

bool isMate(char board[][8]);
bool isDraw(char board[][8]);

void gameLoop(Board *board);
}