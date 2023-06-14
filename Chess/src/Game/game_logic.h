#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../chess_lib.h"
using namespace std;

namespace Game{
    Board start(string starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", string playing = "white", bool showMaterial = true, bool showMoves = true, string prompt_type = Board::SEPERATE);
};